class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        const int MOD = 1e9 + 7;
        vector<vector<long long>> dp(n, vector<long long>(n, -1));
        vector<vector<long long>> cnt(n, vector<long long>(n, 0));

        board[0][0] = '0';
        board[n-1][n-1] = '0';

        dp[n-1][n-1] = 0;
        cnt[n-1][n-1] = 1;

        for (int i = n-1; i >= 0; i--) {
            for (int j = n-1; j >= 0; j--) {
                if (i == n-1 && j == n-1) continue;
                if (board[i][j] == 'X') continue;

                long long best = -1, ways = 0;
                int di[] = {1, 0, 1};
                int dj[] = {0, 1, 1};

                for (int k = 0; k < 3; k++) {
                    int ni = i + di[k], nj = j + dj[k];
                    if (ni >= n || nj >= n) continue;
                    if (dp[ni][nj] == -1) continue; // unreachable

                    long long cand = dp[ni][nj] + (board[i][j] - '0');
                    if (cand > best) {
                        best = cand;
                        ways = cnt[ni][nj];
                    } else if (cand == best) {
                        ways = (ways + cnt[ni][nj]) % MOD;
                    }
                }

                dp[i][j] = best;
                cnt[i][j] = ways;
            }
        }

        if (dp[0][0] == -1) return {0, 0};
        return {(int)dp[0][0], (int)cnt[0][0]};
    }
};