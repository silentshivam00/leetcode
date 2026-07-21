class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ans;
        unordered_map<int , int> m;

        vector<int> used(nums2.size() , false);

        for(int i=0; i<nums1.size(); i++){
            for(int j=0; j<nums2.size(); j++){
                if(nums1[i] == nums2[j] && !used[j]){
                    ans.push_back(nums1[i]);
                    used[j] = true;
                    break;
                }
            }
        }
        return ans;
    }
};