class Solution {
public:
    int n;
    vector<int> suffix;
    vector<vector<int>> dp;

    int solve(int i, int M) {

        // All piles are taken
        if (i >= n)
            return 0;

        // Can take all remaining piles
        if (i + 2 * M >= n)
            return suffix[i];

        if (dp[i][M] != -1)
            return dp[i][M];

        int ans = 0;

        // Take X piles, where 1 <= X <= 2*M
        for (int X = 1; X <= 2 * M; X++) {

            // Stones opponent can get after our move
            int opponent = solve(i + X, max(M, X));

            // Total stones remaining from i
            int total = suffix[i];

            // We take everything remaining except opponent's best
            ans = max(ans, total - opponent);
        }

        return dp[i][M] = ans;
    }

    int stoneGameII(vector<int>& piles) {

        n = piles.size();

        // suffix[i] = sum of piles[i ... n-1]
        suffix.resize(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        dp.assign(n, vector<int>(n + 1, -1));

        return solve(0, 1);
    }
};