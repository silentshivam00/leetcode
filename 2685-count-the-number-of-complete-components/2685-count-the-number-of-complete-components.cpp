class Solution {
public:
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<bool> visited(n, false);
        int count = 0;

        for (int i = 0; i < n; i++) {
            if (visited[i]) continue;

            // BFS/DFS to find all nodes in this component
            vector<int> component;
            queue<int> q;
            q.push(i);
            visited[i] = true;

            while (!q.empty()) {
                int u = q.front(); q.pop();
                component.push_back(u);
                for (int v : adj[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }

            int numNodes = component.size();
            long long numEdges = 0;
            for (int u : component) {
                numEdges += adj[u].size();
            }
            numEdges /= 2; // each edge counted twice

            long long requiredEdges = (long long)numNodes * (numNodes - 1) / 2;

            if (numEdges == requiredEdges) {
                count++;
            }
        }

        return count;
    }
};