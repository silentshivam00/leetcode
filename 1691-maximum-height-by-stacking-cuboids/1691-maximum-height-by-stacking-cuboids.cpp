class Solution {
public:

    bool isSafePlacing(vector<int> &c1 , vector<int> &c2){
        if(c1[0] <= c2[0] && c1[1] <= c2[1] && c1[2] <= c2[2]){
            return true;
        }
        else{
            return false;
        }
    }

    int solveUsingRE(vector<vector<int>>& cuboids , int curr , int prev){
        //base case
        if(curr >= cuboids.size()){
            return 0;
        }

        int inc = 0;
        if(prev == -1 || isSafePlacing(cuboids[prev] , cuboids[curr])){
            inc = cuboids[curr][2] + solveUsingRE(cuboids , curr+1 , curr);
        }
        int exc = 0 + solveUsingRE(cuboids , curr+1 , prev);
        int finalAns = max(inc , exc);
        return finalAns;
    }
    //2D DP Apply

    //Top down Approach
    int solveUsingMem(vector<vector<int>>& cuboids , int curr , int prev , vector<vector<int>> &dp){
        //base case
        if(curr >= cuboids.size()){
            return 0;
        }

        //step3->check wheather the ans already exist
        if(dp[curr][prev+1] != -1) return dp[curr][prev+1];

        int inc = 0;
        if(prev == -1 || isSafePlacing(cuboids[prev] , cuboids[curr])){
            inc = cuboids[curr][2] + solveUsingMem(cuboids , curr+1 , curr , dp);
        }
        int exc = 0 + solveUsingMem(cuboids , curr+1 , prev , dp);
        dp[curr][prev+1] = max(inc , exc);
        return dp[curr][prev+1];
    } 

    //Bottom up approach
    int solveUsingTab(vector<vector<int>>& cuboids){
        int n = cuboids.size();
        //step 1-> create 2d DP
        vector<vector<int>> dp(n+1 , vector<int>(n+1 , 0));
        //step 2-> analyze base case
        //already done in step 1

        //step 3-> reverkro aur loop chalao
        //curr ->[0 to n]
        //prev ->[-1 to curr]
        for(int curr = n-1; curr>=0; curr--){
            for(int prev = curr-1; prev>=-1; prev--){
                int inc = 0;
                if(prev == -1 || isSafePlacing(cuboids[prev] , cuboids[curr])){
                    inc = cuboids[curr][2] + dp[curr+1][curr+1];
                }
                int exc = 0 + dp[curr+1][prev+1];
                dp[curr][prev+1] = max(inc , exc);
            }
        }
        return dp[0][0];
    } 

    int solveUsingTabSO(vector<vector<int>>& cuboids){
        int n = cuboids.size();
        vector<int>prevRow(n+1 , 0);
        vector<int>currRow(n+1 , 0);
        //step 3-> reverkro aur loop chalao
        //curr ->[0 to n]
        //prev ->[-1 to curr]
        for(int curr = n-1; curr>=0; curr--){
            for(int prev = curr-1; prev>=-1; prev--){
                int inc = 0;
                if(prev == -1 || isSafePlacing(cuboids[prev] , cuboids[curr])){
                    inc = cuboids[curr][2] + prevRow[curr+1];
                }
                int exc = 0 + prevRow[prev+1];
                currRow[prev+1] = max(inc , exc);
            }
            //shifting
            prevRow = currRow;
        }
        return prevRow[0];
    }           

    int solveUsingTabSO2(vector<vector<int>>& cuboids){
        int n = cuboids.size();
        // vector<int>prevRow(n+1 , 0);
        vector<int>currRow(n+1 , 0);
        //step 3-> reverkro aur loop chalao
        //curr ->[0 to n]
        //prev ->[-1 to curr]
        for(int curr = n-1; curr>=0; curr--){
            for(int prev = -1; prev<=curr-1; prev++){
                int inc = 0;
                if(prev == -1 || isSafePlacing(cuboids[prev] , cuboids[curr])){
                    inc = cuboids[curr][2] + currRow[curr+1];
                }
                int exc = 0 + currRow[prev+1];
                currRow[prev+1] = max(inc , exc);
            }
            //shifting
            // prevRow = currRow;
        }
        return currRow[0];
    }  

    int maxHeight(vector<vector<int>>& cuboids) {
        
        for(auto &cuboid : cuboids){
            sort(cuboid.begin() , cuboid.end());
        }
        sort(cuboids.begin() , cuboids.end());
        int n = cuboids.size();

        int prev = -1;
        int curr = 0;
        // return solveUsingRE(cuboids , curr , prev);

        //step 1-> create 2d dp array
        // vector<vector<int>> dp(n+1 , vector<int>(n+1 , -1));
        // return solveUsingMem(cuboids , curr , prev , dp);

        // return solveUsingTab(cuboids , curr , prev);

        // return solveUsingTabSO(cuboids);

        return solveUsingTabSO2(cuboids);

    }
};