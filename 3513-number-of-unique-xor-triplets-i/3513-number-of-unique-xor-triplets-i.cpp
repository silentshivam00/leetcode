class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 1;
        if (n == 2) return 2;

        long long x = 1;
        while (x <= n) x <<= 1;
        return (int)x;
    }
};
