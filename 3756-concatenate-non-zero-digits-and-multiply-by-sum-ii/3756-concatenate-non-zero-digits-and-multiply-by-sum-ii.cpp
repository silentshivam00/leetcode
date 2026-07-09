class Solution {
public:
    static const int MOD = 1e9 + 7;

    struct Node {
        long long val;   // value of concatenated digits, mod MOD
        long long sum;   // sum of digits
        int cnt;         // count of non-zero digits (length of x)
    };

    vector<Node> tree;
    vector<long long> pow10;
    int n;

    Node merge(const Node& a, const Node& b) {
        Node res;
        res.cnt = a.cnt + b.cnt;
        res.val = (a.val * pow10[b.cnt] + b.val) % MOD;
        res.sum = (a.sum + b.sum) % MOD;
        return res;
    }

    void build(int node, int start, int end, const string& s) {
        if (start == end) {
            int d = s[start] - '0';
            if (d == 0) tree[node] = {0, 0, 0};
            else tree[node] = {d, d, 1};
            return;
        }
        int mid = (start + end) / 2;
        build(node * 2, start, mid, s);
        build(node * 2 + 1, mid + 1, end, s);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    Node query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return {0, 0, 0};
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        Node left = query(node * 2, start, mid, l, r);
        Node right = query(node * 2 + 1, mid + 1, end, l, r);
        return merge(left, right);
    }

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        n = s.size();
        tree.resize(4 * n);
        pow10.resize(n + 1);
        pow10[0] = 1;
        for (int i = 1; i <= n; i++) pow10[i] = pow10[i - 1] * 10 % MOD;

        build(1, 0, n - 1, s);

        vector<int> answer;
        answer.reserve(queries.size());
        for (auto& q : queries) {
            int l = q[0], r = q[1];
            Node res = query(1, 0, n - 1, l, r);
            long long ans = (res.val * res.sum) % MOD;
            answer.push_back((int)ans);
        }
        return answer;
    }
};