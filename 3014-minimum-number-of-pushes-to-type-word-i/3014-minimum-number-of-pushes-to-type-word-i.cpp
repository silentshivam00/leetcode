class Solution {
public:
    int minimumPushes(string word) {
        int n = word.size();
        int total = 0;
        for (int i = 0; i < n; i++) {
            total += (i / 8) + 1;
        }
        return total;
    }
};