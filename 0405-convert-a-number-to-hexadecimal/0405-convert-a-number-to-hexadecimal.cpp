class Solution {
public:
    string toHex(int num) {
        if (num == 0) return "0";

        string hex = "0123456789abcdef";
        string ans = "";

        unsigned int n = num;   // Handle negative numbers using 2's complement

        while (n != 0) {
            ans = hex[n & 15] + ans;   // Last 4 bits
            n >>= 4;                   // Right shift by 4 bits
        }

        return ans;
    }
};