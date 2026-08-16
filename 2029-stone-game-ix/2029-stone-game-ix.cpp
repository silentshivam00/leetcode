class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int cnt[3] = {0};

        for (int x : stones) {
            cnt[x % 3]++;
        }

        if (cnt[0] % 2 == 0) {
            // Need at least one remainder-1 and one remainder-2 stone
            return cnt[1] > 0 && cnt[2] > 0;
        }

        // Odd number of remainder-0 stones
        return abs(cnt[1] - cnt[2]) > 2;
    }
};