class Solution {
public:
    string numStr;
    int K;

    long long memo[20][11][2];
    bool visited[20][11][2];

    long long dp(int pos, int prevDigit, bool tight , bool started){
        if(pos == (int)numStr.size()){
            return started ? 1:0;
        }
        if(!tight && visited[pos][prevDigit+1][started]){
            return memo[pos][prevDigit+1][started];
        }

        int limit = tight ? (numStr[pos] - '0') : 9;
        long long result = 0;

        for(int d=0;d<=limit; d++){
            bool newStarted = started || (d!=0);
            if(!newStarted){
                result += dp(pos+1 , -1 , tight && (d == limit) , false);
            }
            else{
                if(started && abs(d-prevDigit) > K) continue;
                result += dp(pos+1 , d , tight && (d == limit) ,true);
            }
        }

        if(!tight){
            visited[pos][prevDigit +1][started] = true;
            memo[pos][prevDigit+1][started] = result;
        }

        return result;
    }

    long long countGood(long long n){
        if(n<0) return 0;
        numStr = to_string(n);
        memset(visited , false , sizeof(visited));
        return dp(0 , -1 , true , false);
    }

    
    long long goodIntegers(long long l, long long r, int k) {
        K = k;
        return countGood(r) - countGood(l-1);
    }
};