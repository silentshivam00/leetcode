class Solution {
public:


    int smallestNumber(int n, int t) {

        while(true){
            int ans = 1;
            int num = n;
            while(num!=0){
                int digit = num%10;
                ans = ans*digit;
                num = num/10;
            }

            if(ans%t == 0) return n;

            n++;
        }
        return -1;
        
    }
};