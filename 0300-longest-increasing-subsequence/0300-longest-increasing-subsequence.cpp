class Solution {
public:

    int solveRE(vector<int> &nums , int curr , int prev){
        //base case
        if(curr >= nums.size()) return 0;

        int inc = 0;
        if(prev == -1 || nums[curr] > nums[prev]){
            //include
            inc = 1 + solveRE(nums , curr+1 , curr);
        }
        //exclude
        int exc = 0 + solveRE(nums , curr+1 , prev);

        int finalans = max(inc , exc);
        return finalans;
    }

    // apply 2d DP
    //top down method
    int solveMem(vector<int> &nums , int curr , int prev , vector<vector<int>> &dp){
        //base case
        if(curr >= nums.size()) return 0;

        //step 3-> check if ans already exist or not
        if(dp[curr][prev+1] != -1) return dp[curr][prev+1];

        int inc = 0;
        if(prev == -1 || nums[curr] > nums[prev]){
            //include
            inc = 1 + solveMem(nums , curr+1 , curr , dp);
        }
        //exclude
        int exc = 0 + solveMem(nums , curr+1 , prev , dp);

        //step 2 -> ans ko dp me store kro aur return kro
        dp[curr][prev+1] = max(inc , exc);
        return dp[curr][prev+1];
    }

    // bottom up approach
    int solveTab(vector<int> &nums){
        
        int n = nums.size();
        //step 1-> create 2d DP
        vector<vector<int>> dp(n+1 , vector<int>(n+1 , 0));
        //As the dp begins with 0 so step 2 is covered

        //step 3-> reverse kro loop chalao
        //In recursion solution
        // curr => 0 to n
        // prev => -1 to curr 

        for(int curr = n-1; curr>=0; curr--){
            for(int prev = curr-1; prev>=-1; prev--){

                int inc = 0;
                if(prev == -1 || nums[curr] > nums[prev]){
                    //include
                    inc = 1 + dp[curr+1][curr+1];
                }
                //exclude
                int exc = 0 + dp[curr+1][prev+1];

                //step 2 -> ans ko dp me store kro aur return kro
                dp[curr][prev+1] = max(inc , exc);

            }
        }

        return dp[0][-1+1]; // dp[0][0]
    }

    int solveTabSO(vector<int> &nums){
        
        int n = nums.size();

        vector<int>prevRow(n+1,0);
        vector<int>currRow(n+1,0);

        //step 3-> reverse kro loop chalao
        //In recursion solution
        // curr => 0 to n
        // prev => -1 to curr 

        for(int curr = n-1; curr>=0; curr--){
            for(int prev = curr-1; prev>=-1; prev--){
                int inc = 0;
                if(prev == -1 || nums[curr] > nums[prev]){
                    //include
                    inc = 1 + prevRow[curr+1];
                }
                //exclude
                int exc = 0 + prevRow[prev+1];

                //step 2 -> ans ko dp me store kro aur return kro
                currRow[prev+1] = max(inc , exc);
            }
            //update
            prevRow = currRow;
        }

        return prevRow[0]; // dp[0][0]
    }

    int lengthOfLIS(vector<int>& nums) {
        int curr = 0;
        int prev = -1;
        int n = nums.size();
        // return solveRE(nums , curr , prev);

        //step-1 -> create 2D dp array
        //OBSERVATION-> prev ki value hamesha curr se kam hogi
        // vector<vector<int>> dp(n+1 , vector<int>(n+1 , -1));
        // return solveMem(nums , curr , prev , dp);

        return solveTab(nums);

    }
};