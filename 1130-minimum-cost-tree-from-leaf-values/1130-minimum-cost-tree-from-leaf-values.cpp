class Solution {
public:

    int solveUsingRE(vector<int>& arr , map<pair<int ,int> , int> &maxi , int s , int e){
        //Base case
        if( s>= e) return 0;

        int ans = INT_MAX;
        for(int i=s; i<e; i++){
            int leftKaMax = maxi[{s , i}];
            int rightKaMax = maxi[{i+1 , e}];
            int NonLeafNode = leftKaMax*rightKaMax;

            ans = min(ans , NonLeafNode + solveUsingRE(arr , maxi , s, i) + solveUsingRE(arr , maxi , i+1 , e));
        }
        return ans;
    }

    //top down
    int solveUsingMem(vector<int>& arr , map<pair<int ,int> , int> &maxi , int s , int e , vector<vector<int>> &dp){
        //Base case
        if( s>= e) return 0;

        //step3
        if(dp[s][e] != -1) return dp[s][e];

        int ans = INT_MAX;
        for(int i=s; i<e; i++){
            int leftKaMax = maxi[{s , i}];
            int rightKaMax = maxi[{i+1 , e}];
            int NonLeafNode = leftKaMax*rightKaMax;

            ans = min(ans , NonLeafNode + solveUsingMem(arr , maxi , s, i , dp) + solveUsingMem(arr , maxi , i+1 , e , dp));
        }
        dp[s][e] = ans;
        return dp[s][e];
    }

    //bottom up
    int solveUsingTab(vector<int>& arr , map<pair<int ,int> , int> &maxi){
        int n = arr.size();
        //step 1 and 2
        vector<vector<int>> dp(n+1 , vector<int>(n+1 , 0));

        //step 3
        for(int s = n-1; s>=0; s--){
            for(int e = s; e<=n-1; e++){
                if(s >= e) continue;
                else{
                    int ans = INT_MAX;
                    for(int i=s; i<e; i++){
                        int leftKaMax = maxi[{s , i}];
                        int rightKaMax = maxi[{i+1 , e}];
                        int NonLeafNode = leftKaMax*rightKaMax;

                        ans = min(ans , NonLeafNode + dp[s][i] + dp[i+1][e]);
                    }
                    dp[s][e] = ans;
                }
            }
        }
        return dp[0][n-1];
    }

    int mctFromLeafValues(vector<int>& arr) {
        int n = arr.size();

        map<pair<int ,int> , int> maxi;

        for(int i=0; i<n; i++){
            for(int j=i; j<n; j++){
                if(i == j){
                    maxi[{i,j}] = arr[i];
                }
                else{
                    maxi[{i,j}] = max(maxi[{i,j-1}] , arr[j]);
                }
            }
        }

        int s = 0;
        int e = n-1;
        // return solveUsingRE(arr , maxi , s , e);

        //step1
        vector<vector<int>> dp(n+1 , vector<int>(n+1 , -1));
        return solveUsingMem(arr , maxi , s , e , dp);

    }
};