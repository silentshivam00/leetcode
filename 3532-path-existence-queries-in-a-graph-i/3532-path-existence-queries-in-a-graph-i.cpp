class Solution {
public:
    vector<int> parent;

    int find(int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    void unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx != ry) parent[rx] = ry;
    }

    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;

        for (int i = 0; i < n - 1; i++) {
            if (nums[i + 1] - nums[i] <= maxDiff) {
                unite(i, i + 1);
            }
        }

        vector<bool> answer;
        answer.reserve(queries.size());
        for (auto& q : queries) {
            int u = q[0], v = q[1];
            answer.push_back(find(u) == find(v));
        }
        return answer;
    }
};