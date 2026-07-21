class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int i = nums.size()-1;
        int j = nums.size()-1;

        while(i >= 0){
            if(nums[i] == 0){
                for(int k=i; k<j; k++){
                    nums[k] = nums[k+1];
                }
                nums[j] = 0;
                j--;
            }
            i--;
        }
    }
};