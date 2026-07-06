class Solution {
public:
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] != b[0]) return a[0] < b[0];
            return a[1] > b[1]; // if same start, longer interval first
        });

        int count = 0;
        int maxEnd = 0;

        for (auto& interval : intervals) {
            int end = interval[1];
            if (end > maxEnd) {
                count++;
                maxEnd = end;
            }
            // else: this interval is covered by a previous one, skip it
        }

        return count;
    }
};