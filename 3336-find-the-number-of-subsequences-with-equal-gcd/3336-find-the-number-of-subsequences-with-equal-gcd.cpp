class Solution {
public:
    int subsequencePairCount(vector<int>& nums) {
        const int MOD = 1e9 + 7;
        int maxVal = 200;
        int n = nums.size();

        // dp[g1][g2] = number of ways to pick two disjoint subsequences (from processed prefix)
        // with gcd(seq1) = g1, gcd(seq2) = g2. g = 0 means that subsequence is still empty.
        vector<vector<long long>> dp(maxVal + 1, vector<long long>(maxVal + 1, 0));
        dp[0][0] = 1;

        for (int num : nums) {
            vector<vector<long long>> newDp = dp; // skip option

            for (int g1 = 0; g1 <= maxVal; g1++) {
                for (int g2 = 0; g2 <= maxVal; g2++) {
                    long long cnt = dp[g1][g2];
                    if (cnt == 0) continue;

                    // add num to seq1
                    int newG1 = (g1 == 0) ? num : __gcd(g1, num);
                    newDp[newG1][g2] = (newDp[newG1][g2] + cnt) % MOD;

                    // add num to seq2
                    int newG2 = (g2 == 0) ? num : __gcd(g2, num);
                    newDp[g1][newG2] = (newDp[g1][newG2] + cnt) % MOD;
                }
            }

            dp = move(newDp);
        }

        long long answer = 0;
        for (int g = 1; g <= maxVal; g++) {
            answer = (answer + dp[g][g]) % MOD;
        }

        return (int)answer;
    }
};