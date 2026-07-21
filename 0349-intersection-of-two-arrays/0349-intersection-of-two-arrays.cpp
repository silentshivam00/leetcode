class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ans;
        unordered_map<int , int> m;

        for(int i=0; i<nums1.size(); i++){
            for(int j=0; j<nums2.size(); j++){
                if(nums1[i] == nums2[j]){
                    if(m[nums1[i]] == 1) break;
                    else{
                        ans.push_back(nums1[i]);
                        m[nums1[i]]++;
                    }
                }
            }
        }
        return ans;
    }
};