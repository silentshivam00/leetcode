class Solution {
public:
    int reverseBits(int n) {
        string s;
        while(n){
            int bit = n%2;
            n /= 2;
            s.push_back(bit + '0');
        }

        while(s.length() != 32){
            s.push_back(0 + '0');
        }

        int ans =0;
        for(auto ch : s){
            ans = ans*2 + (ch-'0');
        }

        return ans;
    }
};