class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration,
                           vector<int>& waterStartTime, vector<int>& waterDuration) {
        int n = landStartTime.size(), m = waterStartTime.size();

        int minLandFinish  = INT_MAX;
        int minWaterFinish = INT_MAX;

        for (int i = 0; i < n; i++)
            minLandFinish = min(minLandFinish, landStartTime[i] + landDuration[i]);

        for (int j = 0; j < m; j++)
            minWaterFinish = min(minWaterFinish, waterStartTime[j] + waterDuration[j]);

        int ans = INT_MAX;

        // Option 1: best land ride → each water ride j
        for (int j = 0; j < m; j++) {
            int startWater = max(minLandFinish, waterStartTime[j]);
            ans = min(ans, startWater + waterDuration[j]);
        }

        // Option 2: best water ride → each land ride i
        for (int i = 0; i < n; i++) {
            int startLand = max(minWaterFinish, landStartTime[i]);
            ans = min(ans, startLand + landDuration[i]);
        }

        return ans;
    }
};