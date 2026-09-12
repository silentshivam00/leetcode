class Solution {
public:
    struct State {
        long long score;
        vector<int> indices;
    };

    vector<vector<int>> intervals;
    vector<vector<int>> nextIdx;
    vector<vector<State>> dp;
    vector<vector<bool>> vis;

    // Returns true if a is lexicographically smaller than b
    bool smaller(vector<int>& a, vector<int>& b) {
        return lexicographical_compare(
            a.begin(), a.end(),
            b.begin(), b.end()
        );
    }

    // Compare two states:
    // 1. Higher score is better
    // 2. If score is same, lexicographically smaller indices are better
    State better(State a, State b) {
        if (a.score != b.score)
            return (a.score > b.score ? a : b);

        if (smaller(a.indices, b.indices))
            return a;

        return b;
    }

    State solve(int i, int k) {
        // We can select at most k intervals
        if (i >= intervals.size() || k == 0) {
            return {0, {}};
        }

        if (vis[i][k])
            return dp[i][k];

        vis[i][k] = true;

        // Option 1: Don't take current interval
        State skip = solve(i + 1, k);

        // Option 2: Take current interval
        int nxt = nextIdx[i][0];

        State take = solve(nxt, k - 1);

        take.score += intervals[i][2];
        take.indices.push_back(intervals[i][3]);

        // Important: answer must be sorted by original indices
        sort(take.indices.begin(), take.indices.end());

        dp[i][k] = better(take, skip);

        return dp[i][k];
    }

    vector<int> maximumWeight(vector<vector<int>>& input) {
        int n = input.size();

        /*
            Store:
            [left, right, weight, original_index]
        */
        intervals.clear();

        for (int i = 0; i < n; i++) {
            intervals.push_back({
                input[i][0],
                input[i][1],
                input[i][2],
                i
            });
        }

        // Sort by left endpoint
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 if (a[0] != b[0])
                     return a[0] < b[0];

                 return a[1] < b[1];
             });

        // Store all left endpoints
        vector<int> starts(n);

        for (int i = 0; i < n; i++)
            starts[i] = intervals[i][0];

        /*
            nextIdx[i] = first interval j such that

                intervals[j].left > intervals[i].right

            We need STRICTLY greater because intervals sharing
            a boundary are considered overlapping.
        */
        nextIdx.assign(n, vector<int>(1));

        for (int i = 0; i < n; i++) {
            int r = intervals[i][1];

            int j = upper_bound(
                starts.begin(),
                starts.end(),
                r
            ) - starts.begin();

            nextIdx[i][0] = j;
        }

        /*
            dp[i][k]

            i = current interval
            k = maximum number of intervals we can still choose
        */
        dp.assign(n, vector<State>(5));
        vis.assign(n, vector<bool>(5, false));

        return solve(0, 4).indices;
    }
};