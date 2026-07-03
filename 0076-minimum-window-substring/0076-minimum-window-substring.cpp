class Solution {
public:
    string minWindow(string s, string t) {
        int len1 = s.length();
        int len2 = t.length();

        if(len1 < len2) return "";

        unordered_map<char , int> sMap;
        unordered_map<char , int> tMap;

        for(auto i : t){
            tMap[i]++;
        }
        //in dono variable ke basis pe mai exact string find kr skta hoon using substr method
        int ansLen = INT_MAX;
        int ansIndex = -1;

        int st = 0;
        int e = 0;
        //count tracks total matched character in window
        int count = 0;

        //variable-size window wala logic lagate h
        while(e < len1){
            char ch = s[e];

            //update krna h sMap ko , kyunki sMap "s" wali 
            //string ki window me kaun kaun se character h unko track krne ke liye banaya gya h
            sMap[ch]++;

            //possibility h ki ye ch "t" ke andar ho ya na ho
            //agar ye ch "t" wali string me bhi h
            //to isko matched character ke andar count krna padega
            if(sMap[ch] <= tMap[ch]){
                count++;
            }

            //ab ye bhi ho skta h ki count exactly len2 ke eqaul ho jaye
            if(count == len2){
                //mujhe ek aisi window mil gyi h jisme ans present
                //minimize kro

                while(sMap[s[st]] > tMap[s[st]]){
                    sMap[s[st]]--;
                    st++;
                }
                //ans store
                int windowkiLen = e-st+1;
                if(windowkiLen < ansLen){
                    ansLen = windowkiLen;
                    ansIndex = st;
                }
            }
            //yaha pe aa gye mtlb ek valid ans nhi mila h , expand kro
            e++;
        }
        
        if(ansIndex == -1) return "";
        else{
            return s.substr(ansIndex , ansLen);
        }
    }
};