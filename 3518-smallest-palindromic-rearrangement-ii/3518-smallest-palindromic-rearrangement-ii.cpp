class Solution {
public:
    string smallestPalindrome(string s, long long k) {
        int n = s.size();
        vector<long long> cnt(26, 0);
        for (char c : s) cnt[c - 'a']++;

        int half = n / 2;
        bool odd = (n % 2 == 1);
        int oddChar = -1;
        vector<long long> half_cnt(26, 0);
        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2 == 1) oddChar = i;
            half_cnt[i] = cnt[i] / 2;
        }

        // total distinct permutations of half string, capped at k (cap ~ 2e6 to avoid overflow)
        const long long CAP = 2000000LL;

        // factorial capped
        vector<long long> fact(half + 1, 1);
        for (int i = 1; i <= half; i++) {
            fact[i] = fact[i-1] * i;
            if (fact[i] > CAP) fact[i] = CAP;
        }

        auto countPerm = [&](vector<long long>& c, int total) -> long long {
            if (total == 0) return 1;
            long long res = fact[total];
            for (int i = 0; i < 26; i++) {
                if (c[i] > 1) {
                    long long f = fact[(int)min(c[i], (long long)half)];
                    if (res > CAP) res = CAP;
                    // integer division after capping isn't exact, so do it more carefully below
                }
            }
            return res;
        };

        // proper multinomial count with capping done via big integer style (use double check or long double)
        // We'll implement using long double for safety since n up to 1e4, k up to 1e6
        auto countPermExact = [&](vector<long long>& c, int total) -> long long {
            // compute total! / (c[0]! * c[1]! * ... ) but cap at some large number > 1e6
            // use logarithms to avoid overflow, then if count seems > k range, treat as large
            double logRes = lgamma(total + 1);
            for (int i = 0; i < 26; i++) {
                logRes -= lgamma(c[i] + 1);
            }
            if (logRes > 20) return (long long)2e9; // definitely more than k (k <= 1e6)
            long long res = (long long)round(exp(logRes));
            return res;
        };

        string half_str(half, ' ');
        for (int pos = 0; pos < half; pos++) {
            for (int ch = 0; ch < 26; ch++) {
                if (half_cnt[ch] == 0) continue;
                half_cnt[ch]--;
                long long ways = countPermExact(half_cnt, half - pos - 1);
                if (ways >= k) {
                    half_str[pos] = 'a' + ch;
                    break;
                } else {
                    k -= ways;
                    half_cnt[ch]++;
                }
            }
            if (half_str[pos] == ' ') return ""; // shouldn't happen if k valid
        }

        // check remaining k
        if (k > 1) return "";

        string result = half_str;
        if (odd) result += (char)('a' + oddChar);
        string rev = half_str;
        reverse(rev.begin(), rev.end());
        result += rev;

        return result;
    }
};