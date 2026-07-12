class Solution {
public:
    vector<int> arrayRankTransform(vector<int>& arr) {
        vector<int> sorted_arr = arr;
        sort(sorted_arr.begin(), sorted_arr.end());
        sorted_arr.erase(unique(sorted_arr.begin(), sorted_arr.end()), sorted_arr.end());

        unordered_map<int, int> rank;
        for (int i = 0; i < sorted_arr.size(); i++) {
            rank[sorted_arr[i]] = i + 1;
        }

        vector<int> result;
        result.reserve(arr.size());
        for (int x : arr) {
            result.push_back(rank[x]);
        }

        return result;
    }
};