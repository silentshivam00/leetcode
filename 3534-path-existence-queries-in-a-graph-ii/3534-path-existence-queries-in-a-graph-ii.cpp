class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<int> idx(n);
        for (int i = 0; i < n; i++) idx[i] = i;
        sort(idx.begin(), idx.end(), [&](int a, int b) {
            return nums[a] < nums[b];
        });

        vector<int> sortedPos(n);
        for (int i = 0; i < n; i++) sortedPos[idx[i]] = i;

        vector<int> sortedNums(n);
        for (int i = 0; i < n; i++) sortedNums[i] = nums[idx[i]];

        // reach[i] = farthest index j such that sortedNums[j] - sortedNums[i] <= maxDiff
        vector<int> reach(n);
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (j < i) j = i;
            while (j + 1 < n && sortedNums[j + 1] - sortedNums[i] <= maxDiff) j++;
            reach[i] = j;
        }

        // connectivity components: break whenever consecutive gap > maxDiff
        vector<int> comp(n);
        int c = 0;
        comp[0] = 0;
        for (int i = 1; i < n; i++) {
            if (sortedNums[i] - sortedNums[i - 1] > maxDiff) c++;
            comp[i] = c;
        }

        // binary lifting on reach()
        int LOG = 1;
        while ((1 << LOG) < n) LOG++;

        vector<vector<int>> up(LOG + 1, vector<int>(n));
        for (int i = 0; i < n; i++) up[0][i] = reach[i];
        for (int k = 1; k <= LOG; k++) {
            for (int i = 0; i < n; i++) {
                up[k][i] = up[k - 1][up[k - 1][i]];
            }
        }

        auto minJumps = [&](int pu, int pv) -> int {
            // assumes pu < pv and same component
            int cur = pu, steps = 0;
            for (int k = LOG; k >= 0; k--) {
                if (up[k][cur] < pv) {
                    cur = up[k][cur];
                    steps += (1 << k);
                }
            }
            // now up[0][cur] must be >= pv
            return steps + 1;
        };

        vector<int> answer;
        answer.reserve(queries.size());

        for (auto& q : queries) {
            int u = q[0], v = q[1];
            int pu = sortedPos[u], pv = sortedPos[v];
            if (pu == pv) {
                answer.push_back(0);
                continue;
            }
            if (pu > pv) swap(pu, pv);
            if (comp[pu] != comp[pv]) {
                answer.push_back(-1);
                continue;
            }
            answer.push_back(minJumps(pu, pv));
        }

        return answer;
    }
};