class Solution {
public:
    int zigZagArrays(int n, int l, int r) {
        const int MOD = 1e9 + 7;
        long long m = r - l + 1;

        if (n == 1) return (int)(m % MOD);

        // Preallocate ALL buffers once, outside the loop
        vector<long long> up(m + 1, 0), down(m + 1, 0);
        vector<long long> newUp(m + 1, 0), newDown(m + 1, 0);
        vector<long long> prefDown(m + 2, 0), sufUp(m + 2, 0);

        // i = 2 initialization
        for (int v = 1; v <= m; v++) {
            up[v]   = v - 1;
            down[v] = m - v;
        }

        for (int i = 3; i <= n; i++) {
            // prefix sum of down[]
            prefDown[0] = 0;
            for (int u = 1; u <= m; u++)
                prefDown[u] = (prefDown[u - 1] + down[u]) % MOD;

            // suffix sum of up[]
            sufUp[m + 1] = 0;
            for (int u = m; u >= 1; u--)
                sufUp[u] = (sufUp[u + 1] + up[u]) % MOD;

            for (int v = 1; v <= m; v++) {
                newUp[v]   = prefDown[v - 1];
                newDown[v] = sufUp[v + 1];
            }

            // swap instead of reallocating
            swap(up, newUp);
            swap(down, newDown);
        }

        long long ans = 0;
        for (int v = 1; v <= m; v++)
            ans = (ans + up[v] + down[v]) % MOD;

        return (int)ans;
    }
};