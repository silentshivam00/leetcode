class Solution {
public:
    string removeDuplicates(string s, int k) {

        vector<pair<char, int>> st;

        for (char ch : s) {

            if (!st.empty() && st.back().first == ch) {

                st.back().second++;

                if (st.back().second == k) {
                    st.pop_back();
                }

            } else {
                st.push_back({ch, 1});
            }
        }

        string ans = "";

        for (int i = 0; i < st.size(); i++) {

            char ch = st[i].first;
            int count = st[i].second;

            for (int j = 0; j < count; j++) {
                ans += ch;
            }
        }

        return ans;
    }
};