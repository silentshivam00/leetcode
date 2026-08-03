class Solution {
public:
    string stoneGameIII(vector<int>& stoneValue) {
        int n = stoneValue.size();
        vector<int> dp(n + 1, 0);
        // dp[i] = best score difference (current player's score - opponent's) achievable from stones[i..n-1]

        for (int i = n - 1; i >= 0; i--) {
            int take = 0;
            int best = INT_MIN;
            for (int k = 1; k <= 3 && i + k - 1 < n; k++) {
                take += stoneValue[i + k - 1];
                best = max(best, take - dp[i + k]);
            }
            dp[i] = best;
        }

        if (dp[0] > 0) return "Alice";
        else if (dp[0] < 0) return "Bob";
        else return "Tie";
    }
};