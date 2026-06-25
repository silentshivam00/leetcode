class Solution {
public:
    int countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        // prefix[i] = sum of transformed values for nums[0..i-1], prefix[0] = 0
        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + (nums[i] == target ? 1 : -1);
        }

        // We need, for each j, count of i < j with prefix[i] < prefix[j]
        // Use a Fenwick Tree (BIT) over shifted prefix values.

        // Shift range: prefix values range from -n to n -> shift by n to make non-negative
        int offset = n + 1;
        int size = 2 * n + 3;
        vector<int> bit(size + 1, 0);

        auto update = [&](int pos) {
            for (++pos; pos <= size; pos += pos & (-pos))
                bit[pos]++;
        };
        auto query = [&](int pos) -> int {
            // count of elements with index <= pos (1-indexed internally)
            int res = 0;
            for (++pos; pos > 0; pos -= pos & (-pos))
                res += bit[pos];
            return res;
        };

        long long count = 0;
        // process prefix[0] first (insert), then for each subsequent prefix[j], query before inserting
        update(prefix[0] + offset);

        for (int j = 1; j <= n; j++) {
            int val = prefix[j] + offset;
            // count of inserted values strictly less than val => query(val - 1)
            count += query(val - 1);
            update(val);
        }

        return (int)count;
    }
};