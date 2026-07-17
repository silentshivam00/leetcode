class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        int maxVal = *max_element(nums.begin(), nums.end());
        vector<long long> cntVal(maxVal + 1, 0);
        for (int x : nums) cntVal[x]++;

        // cntMultiple[g] = number of elements in nums divisible by g
        vector<long long> cntMultiple(maxVal + 1, 0);
        for (int g = 1; g <= maxVal; g++) {
            for (int mult = g; mult <= maxVal; mult += g) {
                cntMultiple[g] += cntVal[mult];
            }
        }

        // pairsMultiple[g] = number of pairs whose gcd is a multiple of g
        vector<long long> pairsMultiple(maxVal + 1, 0);
        for (int g = 1; g <= maxVal; g++) {
            long long c = cntMultiple[g];
            pairsMultiple[g] = c * (c - 1) / 2;
        }

        // exact[g] = number of pairs with gcd exactly g (via inclusion-exclusion, high to low)
        vector<long long> exact(maxVal + 2, 0);
        for (int g = maxVal; g >= 1; g--) {
            long long total = pairsMultiple[g];
            for (int mult = 2 * g; mult <= maxVal; mult += g) {
                total -= exact[mult];
            }
            exact[g] = total;
        }

        // prefix sum of exact[g], g = 1..maxVal
        vector<long long> prefix(maxVal + 1, 0);
        for (int g = 1; g <= maxVal; g++) {
            prefix[g] = prefix[g - 1] + exact[g];
        }

        vector<int> answer;
        answer.reserve(queries.size());
        for (long long q : queries) {
            long long target = q + 1;
            int lo = 1, hi = maxVal, res = maxVal;
            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (prefix[mid] >= target) {
                    res = mid;
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
            answer.push_back(res);
        }

        return answer;
    }
};