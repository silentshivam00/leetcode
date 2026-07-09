class Solution {
public:

    int solveUsingRE(int s , int e){
        //Base case
        if(s >= e) return 0;

        int ans = INT_MAX;
        for(int i=s; i<e; i++){
            ans = min(ans , i + max(solveUsingRE(s , i-1) , solveUsingRE(i+1 , e)));
        }
        return ans;
    }

    int solveUsingMem(int s , int e , vector<vector<int>> &dp){
        //Base case
        if(s >= e) return 0;

        //step 3->
        if(dp[s][e] != -1) return dp[s][e];

        int ans = INT_MAX;
        for(int i=s; i<e; i++){
            ans = min(ans , i + max(solveUsingMem(s , i-1 , dp) , solveUsingMem(i+1 , e , dp)));
        }
        dp[s][e] = ans;
        return dp[s][e];
    }

    int solveUsingTab(int n){

        //step1-> create dp
        vector<vector<int>> dp(n+2 , vector<int>(n+2 , 0));

        //step 2-> analyze base case

        //step3->reverse kro loop chalao
        //s->[1 to n]
        //e->[n to s]
        for(int s=n; s>=1; s--){
            for(int e=s; e<=n; e++){
                if(s >= e) continue;
                else{
                    int ans = INT_MAX;
                    for(int i=s; i<e; i++){
                        ans = min(ans , i + max(dp[s][i-1] , dp[i+1][e]));
                    }
                    dp[s][e] = ans;
                }
            }
        }
        return dp[1][n];

    }


    int getMoneyAmount(int n) {

        // return solveUsingRE(1 , n);

        //step1-> create 2d DP array
        // vector<vector<int>> dp(n+1 , vector<int>(n+1 , -1));
        // return solveUsingMem(1 , n , dp);

        return solveUsingTab(n);

    }
};