class Solution {
public:
    vector<int> digits;
    int L;
    map<tuple<int,int,int,int>, pair<long long,long long>> memo;

    pair<long long,long long> dp(int pos, int prev_digit, int trend, bool started, bool tight) {
        if (pos == L) return {1, 0};

        if (!tight) {
            auto key = make_tuple(pos, prev_digit, trend, (int)started);
            auto it = memo.find(key);
            if (it != memo.end()) return it->second;
        }

        int limit = tight ? digits[pos] : 9;
        long long totalCount = 0, totalWav = 0;

        for (int d = 0; d <= limit; d++) {
            bool newTight = tight && (d == limit);

            if (!started && d == 0) {
                auto [cnt, wav] = dp(pos+1, 0, 0, false, newTight);
                totalCount += cnt; totalWav += wav;
                continue;
            }

            if (!started) {
                auto [cnt, wav] = dp(pos+1, d, 0, true, newTight);
                totalCount += cnt; totalWav += wav;
            } else {
                long long add = 0;
                if (trend == 1 && d < prev_digit) add = 1; // prev_digit was a peak
                else if (trend == 2 && d > prev_digit) add = 1; // prev_digit was a valley

                int newTrend = (d > prev_digit) ? 1 : (d < prev_digit) ? 2 : 3;

                auto [cnt, wav] = dp(pos+1, d, newTrend, true, newTight);
                totalCount += cnt;
                totalWav += wav + add * cnt;
            }
        }

        if (!tight) memo[make_tuple(pos, prev_digit, trend, (int)started)] = {totalCount, totalWav};
        return {totalCount, totalWav};
    }

    long long f(long long N) {
        if (N <= 0) return 0;
        string s = to_string(N);
        digits.clear();
        for (char c : s) digits.push_back(c - '0');
        L = digits.size();
        memo.clear();
        return dp(0, 0, 0, false, true).second;
    }

    long long totalWaviness(long long num1, long long num2) {
        return f(num2) - f(num1 - 1);
    }
};