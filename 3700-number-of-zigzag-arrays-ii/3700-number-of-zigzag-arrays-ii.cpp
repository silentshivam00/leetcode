class Solution {
public:
    const long long MOD = 1e9 + 7;

    vector<vector<long long>> matMult(const vector<vector<long long>>& A,
                                       const vector<vector<long long>>& B) {
        int n = A.size(), p = B.size(), k = B[0].size();
        vector<vector<long long>> C(n, vector<long long>(k, 0));
        for (int i = 0; i < n; i++) {
            for (int x = 0; x < p; x++) {
                long long a = A[i][x];
                if (a == 0) continue;
                const auto& Bx = B[x];
                auto& Ci = C[i];
                for (int j = 0; j < k; j++)
                    Ci[j] = (Ci[j] + a * Bx[j]) % MOD;
            }
        }
        return C;
    }

    vector<vector<long long>> matPow(vector<vector<long long>> M, long long power) {
        int n = M.size();
        vector<vector<long long>> result(n, vector<long long>(n, 0));
        for (int i = 0; i < n; i++) result[i][i] = 1;   // identity

        while (power > 0) {
            if (power & 1) result = matMult(result, M);
            M = matMult(M, M);
            power >>= 1;
        }
        return result;
    }

    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;
        if (n == 1) return (int)(m % MOD);

        int size = 2 * m;

        // T[m+u][v] = 1 if u > v   (needDown[u] -> newNeedUp[v])
        // T[u][m+v] = 1 if u < v   (needUp[u]   -> newNeedDown[v])
        vector<vector<long long>> T(size, vector<long long>(size, 0));
        for (int u = 0; u < m; u++) {
            for (int v = 0; v < m; v++) {
                if (u > v) T[m+u][v] = 1;
                if (u < v) T[u][m+v] = 1;
            }
        }

        vector<vector<long long>> Tn = matPow(T, (long long)n - 1);

        vector<long long> init(size, 1);   // length-1: all needUp=1, needDown=1
        vector<long long> final(size, 0);
        for (int i = 0; i < size; i++) {
            if (init[i] == 0) continue;
            for (int j = 0; j < size; j++)
                final[j] = (final[j] + init[i] * Tn[i][j]) % MOD;
        }

        long long ans = 0;
        for (int j = 0; j < size; j++) ans = (ans + final[j]) % MOD;
        return (int)ans;
    }
};