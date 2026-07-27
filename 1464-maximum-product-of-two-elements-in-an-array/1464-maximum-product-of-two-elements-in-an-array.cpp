class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int first = INT_MIN, second = INT_MIN;

        for (int x : nums) {
            if (x > first) {
                second = first;
                first = x;
            } else if (x > second) {
                second = x;
            }
        }

        return (first - 1) * (second - 1);
    }
};