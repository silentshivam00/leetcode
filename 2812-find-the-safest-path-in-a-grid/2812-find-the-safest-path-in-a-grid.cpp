class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> dist(n, vector<int>(n, -1));
        queue<pair<int,int>> q;

        // Phase 1: multi-source BFS from all thieves
        for (int r = 0; r < n; r++)
            for (int c = 0; c < n; c++)
                if (grid[r][c] == 1) {
                    dist[r][c] = 0;
                    q.push({r, c});
                }

        int dirs[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
        while (!q.empty()) {
            auto [r, c] = q.front(); q.pop();
            for (auto& d : dirs) {
                int nr = r + d[0], nc = c + d[1];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        // Edge case: start or end is a thief cell
        if (dist[0][0] == 0 || dist[n-1][n-1] == 0) return 0;

        // Phase 2: binary search on safeness factor k
        // Check if path exists using only cells with dist >= k
        auto canReach = [&](int k) -> bool {
            if (dist[0][0] < k || dist[n-1][n-1] < k) return false;
            vector<vector<bool>> visited(n, vector<bool>(n, false));
            queue<pair<int,int>> bq;
            bq.push({0, 0});
            visited[0][0] = true;
            while (!bq.empty()) {
                auto [r, c] = bq.front(); bq.pop();
                if (r == n-1 && c == n-1) return true;
                for (auto& d : dirs) {
                    int nr = r + d[0], nc = c + d[1];
                    if (nr >= 0 && nr < n && nc >= 0 && nc < n
                        && !visited[nr][nc] && dist[nr][nc] >= k) {
                        visited[nr][nc] = true;
                        bq.push({nr, nc});
                    }
                }
            }
            return false;
        };

        int lo = 0, hi = n + n - 2; // max possible Manhattan distance in n×n grid
        while (lo < hi) {
            int mid = lo + (hi - lo + 1) / 2;
            if (canReach(mid)) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }
};