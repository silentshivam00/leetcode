class Solution {
public:
    bool isPerfectSquare(int num) {
        long long s = 0;
        long long e = num;

        while(s <= e){
            long long mid = s+(e-s)/2;

            long long sqr = mid*mid;

            if(sqr > num) e = mid-1;
            else if(sqr < num) s = mid+1;
            else return true;
        }
        return false;
    }
};