class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> count;
        for (int x : nums) count[(long long)x]++;

        int ans = 1;

        // Special case: value 1 (1^2 = 1 forever)
        auto it1 = count.find(1);
        if (it1 != count.end()) {
            int c = it1->second;
            ans = max(ans, (c % 2 == 1) ? c : c - 1);
        }

        for (auto& [val, cnt] : count) {
            if (val == 1) continue;

            // Build the chain of values that actually exist: val, val^2, val^4, ...
            vector<long long> chain;
            chain.push_back(val);
            long long x = val;
            while (true) {
                if (x > 1500000000LL) break; // overflow guard; nums[i] <= 1e9
                long long nx = x * x;
                if (count.count(nx)) {
                    chain.push_back(nx);
                    x = nx;
                } else break;
            }

            // Largest p such that chain[0..p-1] all have count >= 2
            int bestP = 0;
            for (int i = 1; i < (int)chain.size(); i++) {
                if (count[chain[i-1]] >= 2) bestP = i;
                else break;
            }

            ans = max(ans, 2 * bestP + 1);
        }

        return ans;
    }
};