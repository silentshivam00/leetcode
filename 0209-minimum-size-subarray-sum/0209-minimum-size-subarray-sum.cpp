class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int s = 0;
        int e = 0;
        int len = INT_MAX;
        int sum = 0;

        while(e < nums.size()){
            sum += nums[e];

            while(sum >= target){
                //iska mtlb ans aa chuka h 
                //sbse phle ans kop store krlo
                len = min(len , e-s+1);

                //minimise krna h mtlb s ko aage bdao 
                //lekin usse phle sum ko kam kro
                sum = sum - nums[s];
                s++;
            }
            //yaha per aa gye 
            //iska mtlb sum target se kam ho gya
            //ab window ko expand kro
            e++;
        }

        if(len == INT_MAX) return 0;
        else return len;
    }
};