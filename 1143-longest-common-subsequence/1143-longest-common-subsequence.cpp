class Solution {
public:

    int solveUsingRE(string text1 , string text2 , int i , int j){
        //base case
        if(i >= text1.length() || j >= text2.length()) return 0;

        int ans = 0;
        if(text1[i] == text2[j]){
            //match
            ans = 1 + solveUsingRE(text1 , text2 , i+1 ,j+1);
        }
        else{
            //no match
            ans = 0 + max(solveUsingRE(text1 , text2 , i+1 , j) , solveUsingRE(text1 ,text2 , i ,j+1));
        }

        return ans;
    }
    //2D dp apply
    //Top down Approach
    int solveUsingMemo(string &text1 , string &text2 , int i , int j , vector<vector<int>> &dp){
        //base case
        if(i >= text1.length() || j >= text2.length()) return 0;

        //step 3->check if Ans exist or not
        if(dp[i][j] != -1) return dp[i][j];

        int ans = 0;
        if(text1[i] == text2[j]){
            //match
            ans = 1 + solveUsingMemo(text1 , text2 , i+1 ,j+1 , dp);
        }
        else{
            //no match
            ans = 0 + max(solveUsingMemo(text1 , text2 , i+1 , j , dp) , solveUsingMemo(text1 ,text2 , i , j+1 , dp));
        }
        dp[i][j] = ans;
        return dp[i][j];
    }

    //Bottom up Approach
    int solveUsingTab(string &text1 , string &text2 , int i , int j){
        int n1 = text1.length();
        int n2 = text2.length();

        //step1 -> create 2D dp
        vector<vector<int>> dp(n1+1 , vector<int>(n2+1 , 0));

        //step 2-> Analyze base case and update DP
        //Already done in step 1

        //step 3-> reverse kro aur loop chalao
        //i ->[0 to n1]
        //j ->[0 to n2]
        for(int i = n1-1; i>=0; i--){
            for(int j = n2-1; j>=0; j--){
                int ans = 0;
                if(text1[i] == text2[j]){
                    //match
                    ans = 1 + dp[i+1][j+1];
                }
                else{
                    //no match
                    ans = 0 + max(dp[i+1][j] , dp[i][j+1]);
                }
                dp[i][j] = ans;                
            }
        }

        return dp[0][0];
    }

    int longestCommonSubsequence(string text1, string text2) {
        int i = 0;
        int j = 0;

        // return solveUsingRE(text1 , text2 , i , j);
        // int n1 = text1.length();
        // int n2 = text2.length();

        //step1->create 2d Dp
        // vector<vector<int>> dp(n1+1 , vector<int>(n2+1 , -1));
        // return solveUsingMemo(text1 , text2 , i , j , dp);

        return solveUsingTab(text1 , text2 , i , j);

    }
};