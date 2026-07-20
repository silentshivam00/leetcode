class Solution {
public:
    int hammingWeight(int n) {
        int count = 0;
        while(n){
            int bit = n%2;
            if(bit == 1) count++;
            n /= 2;
        }
        return count;
    }
};