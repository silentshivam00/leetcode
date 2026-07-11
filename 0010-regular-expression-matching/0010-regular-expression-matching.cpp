class Solution {
public:

    bool solveUsingRE(string &s , string &p , int i , int j){
        //Base case
        if(i >= s.length() && j >= p.length()) return true;

        if(j >= p.length()) return false;

        bool currMatch = (i < s.length()) && (p[j] == '.' || s[i] == p[j]);

        if(j+1 < p.length() && p[j+1] == '*'){
            bool replaceWtihempty = solveUsingRE(s,p,i,j+2);
            bool replaceWithPreceding = (currMatch && solveUsingRE(s,p,i+1,j));
            return replaceWtihempty || replaceWithPreceding;
        }
        else if(currMatch){
            return solveUsingRE(s,p,i+1,j+1);
        }
        else{
            // no match
            return false;
        }

    }

    bool solveUsingMem(string &s , string &p , int i , int j, vector<vector<int>> &dp){
        //Base case
        if(i >= s.length() && j >= p.length()) return true;

        if(j >= p.length()) return false;

        //step 3
        if(dp[i][j] != -1) return dp[i][j];

        bool currMatch = (i < s.length()) && (p[j] == '.' || s[i] == p[j]);
        bool ans;
        if(j+1 < p.length() && p[j+1] == '*'){
            bool replaceWtihempty = solveUsingMem(s,p,i,j+2,dp);
            bool replaceWithPreceding = (currMatch && solveUsingMem(s,p,i+1,j,dp));
            ans = replaceWtihempty || replaceWithPreceding;
        }
        else if(currMatch){
            ans = solveUsingMem(s,p,i+1,j+1,dp);
        }
        else{
            // no match
            ans = false;
        }

        dp[i][j] = ans;
        return dp[i][j];

    }


    bool solveUsingTab(string &s , string &p , int m , int n){

        //step 1
        vector<vector<int>> dp(m+1 , vector<int>(n+1 , 0));
        //step 2
        dp[m][n] = true;

        //step 3
        for(int i = m; i>=0; i--){
            for(int j = n-1; j>=0; j--){
                bool currMatch = (i < s.length()) && (p[j] == '.' || s[i] == p[j]);
                bool ans;
                if(j+1 < p.length() && p[j+1] == '*'){
                    bool replaceWtihempty = dp[i][j+2];
                    bool replaceWithPreceding = (currMatch && dp[i+1][j]);
                    ans = replaceWtihempty || replaceWithPreceding;
                }
                else if(currMatch){
                    ans = dp[i+1][j+1];
                }
                else{
                    // no match
                    ans = false;
                }

                dp[i][j] = ans;
            }
        }
        return dp[0][0];
    }

    bool isMatch(string s, string p) {
        
        // return solveUsingRE(s , p , 0 ,0);

        int m = s.length();
        int n = p.length();

        //step 1
        // vector<vector<int>> dp(m+1 , vector<int>(n+1 , -1));
        // return solveUsingMem(s , p , 0 ,0 ,dp);

        return solveUsingTab(s , p , m ,n);

    }
};