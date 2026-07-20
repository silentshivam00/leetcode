class Solution {
public:
    bool isPowerOfTwo(int n) {
        if(n <= 0) return false;
        int count = 0;
        while(n){
            int bit = n%2;
            if(bit == 1) count++;
            n /= 2;
        }
        if(count > 1) return false;
        else return true;
    }
};