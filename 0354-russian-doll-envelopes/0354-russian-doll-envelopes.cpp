class Solution {
public:

    bool isSafePlacing(vector<int> &c1 , vector<int> &c2){
        if(c1[0] < c2[0] && c1[1] < c2[1]){
            return true;
        }
        else{
            return false;
        }
    }

    int solveUsingRE(vector<vector<int>>& envelopes , int curr , int prev){
        //base case
        if(curr >= envelopes.size()){
            return 0;
        }

        int inc = 0;
        if(prev == -1 || isSafePlacing(envelopes[prev] , envelopes[curr])){
            inc = 1 + solveUsingRE(envelopes , curr+1 , curr);
        }
        int exc = 0 + solveUsingRE(envelopes , curr+1 , prev);
        int finalAns = max(inc , exc);
        return finalAns;
    }
    //2D DP Apply

    //Top down Approach
    int solveUsingMem(vector<vector<int>>& envelopes , int curr , int prev , vector<vector<int>> &dp){
        //base case
        if(curr >= envelopes.size()){
            return 0;
        }

        //step3->check wheather the ans already exist
        if(dp[curr][prev+1] != -1) return dp[curr][prev+1];

        int inc = 0;
        if(prev == -1 || isSafePlacing(envelopes[prev] , envelopes[curr])){
            inc = 1 + solveUsingMem(envelopes , curr+1 , curr , dp);
        }
        int exc = 0 + solveUsingMem(envelopes , curr+1 , prev , dp);
        dp[curr][prev+1] = max(inc , exc);
        return dp[curr][prev+1];
    } 

    //most optimal solution T.C-> O(nlogn)
    int BinarySearchLIS(vector<vector<int>>& arr){
        sort(arr.begin(), arr.end(),[](vector<int>& a, vector<int>& b){
            if(a[0] == b[0])
                return a[1] > b[1];
            return a[0] < b[0];
        });

        if(arr.size() == 0) return 0;

        vector<int>ans;
        ans.push_back(arr[0][1]);

        for(int i=1; i<arr.size(); i++){
            if(arr[i][1] > ans.back()){
                //include
                ans.push_back(arr[i][1]);
            }
            else{
                //overwrite
                //find index of just bada elemnt of this elemnt
                int index = lower_bound(ans.begin() , ans.end() , arr[i][1]) - ans.begin();
                //lower_bound(start , end , value);
                //lower bound-> gives iterator of just greater or equal to that value
                //replace/overwrite
                ans[index] = arr[i][1];
            }
        }
        return ans.size();
    }

    int maxEnvelopes(vector<vector<int>>& envelopes) {

        // sort(envelopes.begin(), envelopes.end(),
        // [](vector<int>& a, vector<int>& b){
        //     if(a[0] == b[0])
        //         return a[1] > b[1];
        //     return a[0] < b[0];
        // });

        // int n = envelopes.size();
        // int prev = -1;
        // int curr = 0;
        // return solveUsingRE(envelopes , curr , prev);

        //step 1-> create 2d dp array
        // vector<vector<int>> dp(n+1 , vector<int>(n+1 , -1));
        // return solveUsingMem(envelopes , curr , prev , dp);

        return BinarySearchLIS(envelopes);

    }
};