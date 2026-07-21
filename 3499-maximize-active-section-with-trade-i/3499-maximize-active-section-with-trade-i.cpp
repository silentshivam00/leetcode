class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int n = s.size();
        vector<pair<char,int>> blocks;
        int i = 0;
        while (i < n) {
            int j = i;
            while (j < n && s[j] == s[i]) j++;
            blocks.push_back({s[i], j - i});
            i = j;
        }

        int ones = 0;
        for (char c : s) if (c == '1') ones++;

        int maxGain = 0;
        int B = blocks.size();
        for (int k = 1; k < B - 1; k++) {
            if (blocks[k].first == '1') {
                int gain = blocks[k-1].second + blocks[k+1].second;
                maxGain = max(maxGain, gain);
            }
        }

        return ones + maxGain;
    }
};