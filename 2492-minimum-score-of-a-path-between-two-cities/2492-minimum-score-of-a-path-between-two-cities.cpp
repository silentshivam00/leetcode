class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        // Build adjacency list
        vector<vector<pair<int,int>>> adj(n + 1);
        for (auto& r : roads) {
            adj[r[0]].push_back({r[1], r[2]});
            adj[r[1]].push_back({r[0], r[2]});
        }

        // BFS/DFS from city 1, find min edge weight in its component
        vector<bool> visited(n + 1, false);
        queue<int> q;
        q.push(1);
        visited[1] = true;
        int ans = INT_MAX;

        while (!q.empty()) {
            int node = q.front(); q.pop();
            for (auto& [neighbor, dist] : adj[node]) {
                ans = min(ans, dist);          // check every edge in component
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        return ans;
    }
};