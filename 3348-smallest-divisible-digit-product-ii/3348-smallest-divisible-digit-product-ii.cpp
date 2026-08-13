class Solution {
public:
    string smallestNumber(string num, long long t) {
        int req2 = 0, req3 = 0, req5 = 0, req7 = 0;
        long long tt = t;
        while (tt % 2 == 0) { req2++; tt /= 2; }
        while (tt % 3 == 0) { req3++; tt /= 3; }
        while (tt % 5 == 0) { req5++; tt /= 5; }
        while (tt % 7 == 0) { req7++; tt /= 7; }
        if (tt != 1) return "-1";

        int n = num.size();

        auto getFactors = [](int d, int &c2, int &c3, int &c5, int &c7) {
            c2=c3=c5=c7=0;
            while (d % 2 == 0) { c2++; d/=2; }
            while (d % 3 == 0) { c3++; d/=3; }
            while (d % 5 == 0) { c5++; d/=5; }
            while (d % 7 == 0) { c7++; d/=7; }
        };

        int f2[10], f3[10], f5[10], f7[10];
        for (int d = 1; d <= 9; d++) getFactors(d, f2[d], f3[d], f5[d], f7[d]);

        int MAXR2 = req2 + 1, MAXR3 = req3 + 1, MAXR5 = req5 + 1, MAXR7 = req7 + 1;
        MAXR2 = max(MAXR2, 1); MAXR3 = max(MAXR3, 1);
        MAXR5 = max(MAXR5, 1); MAXR7 = max(MAXR7, 1);

        vector<vector<vector<vector<int>>>> minDigits(
            MAXR2+1, vector<vector<vector<int>>>(
                MAXR3+1, vector<vector<int>>(
                    MAXR5+1, vector<int>(MAXR7+1, INT_MAX))));
        minDigits[0][0][0][0] = 0;

        priority_queue<tuple<int,int,int,int,int>, vector<tuple<int,int,int,int,int>>, greater<>> pq;
        pq.push({0,0,0,0,0});
        vector<vector<vector<vector<bool>>>> visited(
            MAXR2+1, vector<vector<vector<bool>>>(
                MAXR3+1, vector<vector<bool>>(
                    MAXR5+1, vector<bool>(MAXR7+1, false))));

        while (!pq.empty()) {
            auto [cost, c2, c3, c5, c7] = pq.top(); pq.pop();
            if (visited[c2][c3][c5][c7]) continue;
            visited[c2][c3][c5][c7] = true;
            for (int d = 1; d <= 9; d++) {
                int nc2 = min(c2 + f2[d], MAXR2);
                int nc3 = min(c3 + f3[d], MAXR3);
                int nc5 = min(c5 + f5[d], MAXR5);
                int nc7 = min(c7 + f7[d], MAXR7);
                if (cost + 1 < minDigits[nc2][nc3][nc5][nc7]) {
                    minDigits[nc2][nc3][nc5][nc7] = cost + 1;
                    pq.push({cost+1, nc2, nc3, nc5, nc7});
                }
            }
        }

        auto cap = [&](int val, int mx) { return min(max(val,0), mx); };

        auto canAchieve = [&](long long L, int r2, int r3, int r5, int r7) -> bool {
            if (L < 0) return false;
            int cr2 = cap(r2, MAXR2), cr3 = cap(r3, MAXR3), cr5 = cap(r5, MAXR5), cr7 = cap(r7, MAXR7);
            int md = minDigits[cr2][cr3][cr5][cr7];
            return md != INT_MAX && md <= L;
        };

        auto buildSmallest = [&](int L, int r2, int r3, int r5, int r7) -> string {
            string res;
            int cc2=0, cc3=0, cc5=0, cc7=0;
            for (int pos = 0; pos < L; pos++) {
                int remLen = L - pos - 1;
                for (int d = 1; d <= 9; d++) {
                    int nc2 = cc2 + f2[d], nc3 = cc3 + f3[d], nc5 = cc5 + f5[d], nc7 = cc7 + f7[d];
                    int need2 = max(0, r2 - nc2), need3 = max(0, r3 - nc3);
                    int need5 = max(0, r5 - nc5), need7 = max(0, r7 - nc7);
                    if (canAchieve(remLen, need2, need3, need5, need7)) {
                        res += ('0' + d);
                        cc2=nc2; cc3=nc3; cc5=nc5; cc7=nc7;
                        break;
                    }
                }
            }
            return res;
        };

        auto checkExact = [&](const string &s) -> bool {
            long long p2=0,p3=0,p5=0,p7=0;
            for (char ch : s) {
                int d = ch - '0';
                if (d == 0) return false;
                p2 += f2[d]; p3 += f3[d]; p5 += f5[d]; p7 += f7[d];
            }
            return p2 >= req2 && p3 >= req3 && p5 >= req5 && p7 >= req7;
        };

        if (checkExact(num)) return num;

        string result = "";
        {
            // ---- KEY FIX: O(1) prefix-validity check instead of O(n) rescan ----
            int firstZero = n; // no zero found => n
            for (int i = 0; i < n; i++) if (num[i] == '0') { firstZero = i; break; }

            vector<long long> pref2(n+1,0), pref3(n+1,0), pref5(n+1,0), pref7(n+1,0);
            for (int i = 0; i < n; i++) {
                int d = num[i]-'0';
                if (d != 0) {
                    pref2[i+1] = pref2[i] + f2[d];
                    pref3[i+1] = pref3[i] + f3[d];
                    pref5[i+1] = pref5[i] + f5[d];
                    pref7[i+1] = pref7[i] + f7[d];
                } else {
                    pref2[i+1] = pref2[i]; pref3[i+1] = pref3[i];
                    pref5[i+1] = pref5[i]; pref7[i+1] = pref7[i];
                }
            }

            for (int i = n-1; i >= 0 && result.empty(); i--) {
                if (firstZero < i) continue; // prefix [0,i-1] contains a zero -> O(1) check now

                int origDigit = num[i]-'0';
                for (int d = origDigit+1; d <= 9; d++) {
                    long long c2 = pref2[i] + f2[d], c3 = pref3[i] + f3[d];
                    long long c5 = pref5[i] + f5[d], c7 = pref7[i] + f7[d];
                    int need2 = max(0LL, (long long)req2 - c2);
                    int need3 = max(0LL, (long long)req3 - c3);
                    int need5 = max(0LL, (long long)req5 - c5);
                    int need7 = max(0LL, (long long)req7 - c7);
                    int remLen = n - i - 1;
                    if (canAchieve(remLen, need2, need3, need5, need7)) {
                        string suffix = buildSmallest(remLen, need2, need3, need5, need7);
                        result = num.substr(0, i) + char('0'+d) + suffix;
                        break;
                    }
                }
            }
        }

        if (!result.empty()) return result;

        int L = n+1;
        if (canAchieve(L, req2, req3, req5, req7)) {
            return buildSmallest(L, req2, req3, req5, req7);
        }
        for (L = n+2; L <= n + 60; L++) {
            if (canAchieve(L, req2, req3, req5, req7)) {
                return buildSmallest(L, req2, req3, req5, req7);
            }
        }
        return "-1";
    }
};