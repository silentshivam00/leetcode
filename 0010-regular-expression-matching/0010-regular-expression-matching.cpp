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

    bool isMatch(string s, string p) {
        
        return solveUsingRE(s , p , 0 ,0);
    }
};