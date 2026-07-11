class Solution {
public:

    bool solveUsingRE(string &s , string &p , int i , int j){
        //Base case
        if(i == s.length() && j == p.length()) return true;

        if(j == p.length()) return false;

        if(i == s.length()){
            for(int k=j; k<p.length(); k++){
                if(p[k] != '*') //sare character '* h , to hum unhe empty se replace kr skte h
                    return false;
                else return true;
            }
        }

        //main Logic
        //matching or not match
        if(p[j] == '?' || s[i] == p[j]){
            return solveUsingRE(s,p,i+1,j+1);
        }
        else if(p[j] == '*'){
            //'*' empty string bhi ban skta h ya kuch aur bhi character ban skta h
            return solveUsingRE(s,p,i+1,j) || solveUsingRE(s,p,i,j+1);
        }
        else{
            //no matching
            return false;
        }
    }


    bool solveUsingMem(string &s , string &p , int i , int j ,vector<vector<int>> &dp){
        //Base case
        if(i == s.length() && j == p.length()) return true;

        if(j == p.length()) return false;

        if(i == s.length()){
            for(int k=j; k<p.length(); k++){
                if(p[k] != '*') //sare character '* h , to hum unhe empty se replace kr skte h
                    return false;
            }
            return true;
        }

        if(dp[i][j] != -1) return dp[i][j];

        //main Logic
        //matching or not match
        bool ans;
        if(p[j] == '?' || s[i] == p[j]){
            ans = solveUsingMem(s,p,i+1,j+1,dp);
        }
        else if(p[j] == '*'){
            //'*' empty string bhi ban skta h ya kuch aur bhi character ban skta h
            ans = solveUsingMem(s,p,i+1,j , dp) || solveUsingMem(s,p,i,j+1 , dp);
        }
        else{
            //no matching
            ans = false;
        }

        dp[i][j] = ans;
        return dp[i][j];
    }    

    bool isMatch(string s, string p) {
        int m = s.length();
        int n = p.length();

        // return solveUsingRE(s , p , 0 , 0);

        //step 1
        vector<vector<int>> dp(m+1 , vector<int>(n+1 , -1));
        return solveUsingMem(s , p , 0 , 0 , dp);

    }
};