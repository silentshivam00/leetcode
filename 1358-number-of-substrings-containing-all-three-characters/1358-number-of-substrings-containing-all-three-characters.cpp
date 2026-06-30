class Solution {
public:
    int numberOfSubstrings(string s) {
        int count[3] = {0, 0, 0};
        int left = 0;
        long long result = 0;

        for (int right = 0; right < (int)s.size(); right++) {
            count[s[right] - 'a']++;

            // shrink window from left while it still contains all 3 characters
            while (count[0] > 0 && count[1] > 0 && count[2] > 0) {
                count[s[left] - 'a']--;
                left++;
            }

            // after the loop, [left-1, right] is the smallest valid window ending at 'right'
            // so all windows starting at 0, 1, ..., left-1 and ending at 'right' are valid
            result += left;
        }

        return (int)result;
    }
};