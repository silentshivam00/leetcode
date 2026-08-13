class Solution {
public:
    struct Node {
        int length;
        char leftChar, rightChar;
        int prefLen, sufLen, maxLen;
    };

    vector<Node> tree;
    string str;
    int n;

    Node merge(const Node& L, const Node& R) {
        Node res;
        res.length = L.length + R.length;
        res.leftChar = L.leftChar;
        res.rightChar = R.rightChar;
        res.maxLen = max(L.maxLen, R.maxLen);

        res.prefLen = L.prefLen;
        if (L.prefLen == L.length && L.rightChar == R.leftChar) {
            res.prefLen += R.prefLen;
        }

        res.sufLen = R.sufLen;
        if (R.sufLen == R.length && R.leftChar == L.rightChar) {
            res.sufLen += L.sufLen;
        }

        if (L.rightChar == R.leftChar) {
            res.maxLen = max(res.maxLen, L.sufLen + R.prefLen);
        }

        return res;
    }

    void build(int node, int start, int end) {
        if (start == end) {
            tree[node] = {1, str[start], str[start], 1, 1, 1};
            return;
        }
        int mid = (start + end) / 2;
        build(node * 2, start, mid);
        build(node * 2 + 1, mid + 1, end);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    void update(int node, int start, int end, int idx, char c) {
        if (start == end) {
            tree[node] = {1, c, c, 1, 1, 1};
            return;
        }
        int mid = (start + end) / 2;
        if (idx <= mid) update(node * 2, start, mid, idx, c);
        else update(node * 2 + 1, mid + 1, end, idx, c);
        tree[node] = merge(tree[node * 2], tree[node * 2 + 1]);
    }

    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        str = s;
        n = s.size();
        tree.resize(4 * n);
        build(1, 0, n - 1);

        int k = queryCharacters.size();
        vector<int> result(k);

        for (int i = 0; i < k; i++) {
            int idx = queryIndices[i];
            char c = queryCharacters[i];
            str[idx] = c;
            update(1, 0, n - 1, idx, c);
            result[i] = tree[1].maxLen;
        }

        return result;
    }
};