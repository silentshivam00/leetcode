class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int , int> visited;

        for(auto i : nums){
            visited[i]++;
        }

        for(auto i : nums){
            if(visited[i] > 1) return true;
        }
        return false;
    }
};