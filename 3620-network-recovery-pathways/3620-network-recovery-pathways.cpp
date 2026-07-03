class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = (int)online.size();

        // 1. Keep only edges whose endpoints are both online
        //    (online[0] and online[n-1] are guaranteed true, so this
        //     correctly encodes "all intermediate nodes online")
        struct Edge { int u, v, c; };
        vector<Edge> filtered;
        filtered.reserve(edges.size());
        for (auto &e : edges) {
            int u = e[0], v = e[1], c = e[2];
            if (online[u] && online[v]) filtered.push_back({u, v, c});
        }
        if (filtered.empty()) return -1;

        // 2. Build adjacency list + compute ONE topological order
        //    for the whole filtered graph (reused across all thresholds)
        vector<vector<pair<int,int>>> adj(n);
        vector<int> indeg(n, 0);
        for (auto &e : filtered) {
            adj[e.u].push_back({e.v, e.c});
            indeg[e.v]++;
        }

        vector<int> indeg2 = indeg;
        queue<int> q;
        for (int i = 0; i < n; i++) if (indeg2[i] == 0) q.push(i);

        vector<int> topo;
        topo.reserve(n);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            topo.push_back(u);
            for (auto &pr : adj[u]) {
                if (--indeg2[pr.first] == 0) q.push(pr.first);
            }
        }
        // topo is valid for any edge subset of this DAG

        // 3. Candidate answers = distinct edge costs
        vector<int> costs;
        costs.reserve(filtered.size());
        for (auto &e : filtered) costs.push_back(e.c);
        sort(costs.begin(), costs.end());
        costs.erase(unique(costs.begin(), costs.end()), costs.end());

        const long long INF = LLONG_MAX / 2;

        auto feasible = [&](int X) -> bool {
            vector<long long> dist(n, INF);
            dist[0] = 0;
            for (int u : topo) {
                if (dist[u] >= INF) continue;
                long long du = dist[u];
                for (auto &pr : adj[u]) {
                    int v = pr.first, c = pr.second;
                    if (c >= X) {
                        long long nd = du + (long long)c;
                        if (nd < dist[v]) dist[v] = nd;
                    }
                }
            }
            return dist[n - 1] <= k;
        };

        // 4. Binary search for the largest feasible threshold X
        int lo = 0, hi = (int)costs.size() - 1;
        int ans = -1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (feasible(costs[mid])) {
                ans = costs[mid];
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        return ans;
    }
};