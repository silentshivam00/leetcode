class Solution {
public:

    long long int final(long long int dividend ,long long int divisor){
        long long int s = 0;
        long long int e = dividend;
        long long ans = 0;

        while(s<=e){
            long long mid = s+((e-s)>>1);

            long long int prod = mid*divisor;
            if(prod > dividend){
                e = mid-1;
            }
            else{
                ans = mid;
                s = mid+1;
            }
        }
        return ans;
    }

    int divide(int dividend,int divisor) {

        if(dividend == INT_MIN && divisor == -1) return INT_MAX;

        long long int ans = final(abs((long long)dividend) , abs((long long)divisor));
        if(dividend<0 && divisor>0 || dividend>0 && divisor<0){
            ans = 0-ans;
        }
        return ans;
    }
};