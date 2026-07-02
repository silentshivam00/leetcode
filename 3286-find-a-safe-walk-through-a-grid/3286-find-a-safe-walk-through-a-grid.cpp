class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size(), n = grid[0].size();

        // best[i][j] = max health we've arrived at (i,j) with so far
        vector<vector<int>> best(m, vector<int>(n, 0));

        queue<tuple<int,int,int>> q;
        int startHealth = health - grid[0][0];
        if (startHealth <= 0) return false;

        best[0][0] = startHealth;
        q.push({0, 0, startHealth});

        int dirs[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

        while (!q.empty()) {
            auto [r, c, h] = q.front(); q.pop();

            if (r == m-1 && c == n-1) return true;

            for (auto& d : dirs) {
                int nr = r + d[0], nc = c + d[1];
                if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;

                int nh = h - grid[nr][nc];
                if (nh <= 0) continue;         // dead
                if (nh <= best[nr][nc]) continue; // already reached with >= health

                best[nr][nc] = nh;
                q.push({nr, nc, nh});
            }
        }

        return false;
    }
};