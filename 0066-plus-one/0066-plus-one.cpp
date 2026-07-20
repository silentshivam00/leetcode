class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();
        vector<int> ans;
        int carry = 1;

        for(int i=n-1; i>=0; i--){
            int sum = digits[i] + carry;
            carry = sum/10;
            sum %= 10;
            ans.push_back(sum);
        }

        if(carry) ans.push_back(carry);
        reverse(ans.begin() , ans.end());
        return ans;
    }
};