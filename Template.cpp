#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
#define sync                     \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);
#define files                        \
    freopen("input.in", "r", stdin); \
    freopen("output.out", "w", stdout);
typedef tree<
    int,
    null_type,
    less<int>,
    rb_tree_tag,
    tree_order_statistics_node_update>
    ordered_set;
#define ll long long
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
// const ll MOD = 1276381699;
const ll MOD = 1e9 + 7;
const int MXN = 2e5 + 5;
#define no cout << "No\n"
#define yes cout << "Yes\n"
int dx4[] = {1, -1, 0, 0};
int dy4[] = {0, 0, 1, -1};
int dx8[] = {0, 0, 1, 1, 1, -1, -1, -1};
int dy8[] = {1, -1, 1, -1, 0, 0, -1, 1};
void sol(int tc)
{
}
int main()
{
    sync;
    int tc = 1;
    // cin >> tc;
    for (int ii = 1; ii <= tc; ++ii)
        sol(ii);
}
// Aho-Corasick
struct Node
{
public:
    int par;
    int leaf = 0;
    char parChar;
    int link = -1;

    int go[26];
    int edges[26];
    Node(int _par = 0, char _parChar = '$') : par(_par), parChar(_parChar)
    {
        for (int ii = 0; ii < 26; ++ii)
            edges[ii] = go[ii] = -1;
    }
};
vector<Node> Trie;
vector<long long> points;
// add new string. if any transition not possible makes new node.
void addString(string s)
{
    int root = 0;
    for (char ch : s)
    {
        int cur = ch - 'a';
        if (Trie[root].edges[cur] == -1)
        {
            Trie[root].edges[cur] = Trie.size();
            Trie.emplace_back(root, ch);
        }
        root = Trie[root].edges[cur];
    }
    Trie[root].leaf++;
}
// gives you the node with current string ending. Must be in given string or custom the function
int findString(string s)
{
    int root = 0;
    for (char ch : s)
    {
        int cur = ch - 'a';
        root = Trie[root].edges[cur];
    }
    return root;
}

int goLink(int root, char curChar);
// find the suffix / failure link
int findLink(int root)
{
    if (Trie[root].link == -1)
    {
        if (root == 0 || Trie[root].par == 0)
        {
            Trie[root].link = 0;
        }
        else
        {
            Trie[root].link = goLink(findLink(Trie[root].par), Trie[root].parChar);
        }
    }
    return Trie[root].link;
}
// automaton next transition with some character
int goLink(int root, char curChar)
{
    int cur = curChar - 'a';
    if (Trie[root].go[cur] == -1)
    {
        if (Trie[root].edges[cur] != -1)
        {
            Trie[root].go[cur] = Trie[root].edges[cur];
        }
        else
        {
            Trie[root].go[cur] = root == 0 ? 0 : goLink(findLink(root), curChar);
        }
    }
    return Trie[root].go[cur];
}
// Suffix Array
class SuffixArray
{
public:
    vector<int> sort_cyclic_shifts(string const &s)
    {
        int n = s.size();
        const int alphabet = 256;
        vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
        for (int i = 0; i < n; i++)
            cnt[s[i]]++;
        for (int i = 1; i < alphabet; i++)
            cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; i++)
            p[--cnt[s[i]]] = i;
        c[p[0]] = 0;
        int classes = 1;
        for (int i = 1; i < n; i++)
        {
            if (s[p[i]] != s[p[i - 1]])
                classes++;
            c[p[i]] = classes - 1;
        }
        vector<int> pn(n), cn(n);
        for (int h = 0; (1 << h) < n; ++h)
        {
            for (int i = 0; i < n; i++)
            {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0)
                    pn[i] += n;
            }
            fill(cnt.begin(), cnt.begin() + classes, 0);
            for (int i = 0; i < n; i++)
                cnt[c[pn[i]]]++;
            for (int i = 1; i < classes; i++)
                cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; i--)
                p[--cnt[c[pn[i]]]] = pn[i];
            cn[p[0]] = 0;
            classes = 1;
            for (int i = 1; i < n; i++)
            {
                pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
                pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
                if (cur != prev)
                    ++classes;
                cn[p[i]] = classes - 1;
            }
            c.swap(cn);
        }
        return p;
    }
    vector<int> lcp_construction(string const &s, vector<int> const &p)
    {
        int n = s.size();
        vector<int> rank(n, 0);
        for (int i = 0; i < n; i++)
            rank[p[i]] = i;

        int k = 0;
        vector<int> lcp(n - 1, 0);
        for (int i = 0; i < n; i++)
        {
            if (rank[i] == n - 1)
            {
                k = 0;
                continue;
            }
            int j = p[rank[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k])
                k++;
            lcp[rank[i]] = k;
            if (k)
                k--;
        }
        return lcp;
    }
    vector<int> p, lcp;
    void work(string s)
    {
        p.clear();
        lcp.clear();

        s += '$';
        p = sort_cyclic_shifts(s);
        lcp = lcp_construction(s, p);
        p.erase(p.begin());
    }
};
// KMP
class KMP
{
public:
    vector<int> pi;
    void kmp(string s)
    {
        int n = (int)s.size();
        pi.resize(n);
        pi[0] = 0;

        for (int ii = 1; ii < n; ++ii)
        {
            int jj = pi[ii - 1];
            while (jj > 0 && s[ii] != s[jj])
                jj = pi[jj - 1];
            if (s[ii] == s[jj])
                ++jj;
            pi[ii] = jj;
        }
    }
};
// Hashing
class Hash
{
public:
    vector<long long> hash;
    vector<long long> hash_pw;
    Hash(string s)
    {
        int n = s.size();
        hash.resize(n);
        hash_pw.resize(n);
        hash_pw[0] = 1;
        int prime = 31;
        for (int ii = 0; ii < n; ++ii)
        {
            hash[ii] = s[ii] - 'a' + 1;
            hash[ii] = hash[ii] * hash_pw[ii] % MOD;
            if (ii != 0)
            {
                hash[ii] = (hash[ii] + hash[ii - 1]) % MOD;
            }
            if (ii + 1 < n)
            {
                hash_pw[ii + 1] = hash_pw[ii] * prime % MOD;
            }
        }
    }
};
// Segment Tree
class SegmentTree
{
public:
    // maximum / minimum sum of subarray.
    struct node
    {
        long long pre, suf, sum, res;
    };
    node make(int val)
    {
        node cur;
        cur.sum = val;
        cur.pre = cur.suf = cur.res = max(val, 0);
        return cur;
    }
    node combine(node x, node y)
    {
        node cur;
        cur.res = max({x.res, y.res, x.suf + y.pre});
        cur.pre = max({x.pre, x.sum + y.pre});
        cur.suf = max({y.suf, y.sum + x.suf});
        cur.sum = x.sum + y.sum;
        return cur;
    }
    vector<int> segTree;
    void innit(int n)
    {
        segTree.resize(4 * n);
    }
    void build(int id, int left, int right)
    {
        if (left == right)
        {
            segTree[id] = 0;
            return;
        }
        int mid = (left + right) / 2;
        build(id * 2, left, mid);
        build(id * 2 + 1, mid + 1, right);
        segTree[id] = 0;
        return;
    }
    void update(int id, int left, int right, int pos, int val)
    {
        if (left == right)
        {
            segTree[id] = val;
            return;
        }
        int mid = (left + right) / 2;
        if (pos <= mid)
            update(2 * id, left, mid, pos, val);
        else
            update(2 * id + 1, mid + 1, right, pos, val);
        segTree[id] = segTree[2 * id] + segTree[2 * id + 1];
        return;
    }
    int query(int id, int left, int right, int l, int r)
    {
        if (l > r)
            return 0;
        if (left == l && right == r)
            return segTree[id];
        int mid = (left + right) / 2;
        int x = query(2 * id, left, mid, l, min(mid, r));
        int y = query(2 * id + 1, 1 + mid, right, max(l, mid + 1), r);
        return x + y;
    }
};
// Sparse Table
int lg[MXN + 1];
int st[MXN][26 + 1];
void build(vector<int> x)
{
    lg[1] = 0;
    int n = x.size();
    for (int ii = 2; ii <= MXN; ii++)
        lg[ii] = lg[ii / 2] + 1;

    for (int ii = 0; ii < n; ii++)
        st[ii][0] = x[ii];

    for (int jj = 1; jj <= 26; jj++)
        for (int ii = 0; ii + (1 << jj) <= n; ii++)
            st[ii][jj] = min(st[ii][jj - 1], st[ii + (1 << (jj - 1))][jj - 1]);
}
int RMQ(int L, int R)
{
    int jj = lg[R - L + 1];
    int mn = min(st[L][jj], st[R - (1 << jj) + 1][jj]);
    return mn;
}
// MO's
int block;
struct Query
{
    int left, right, idx;
    bool operator<(Query other) const
    {
        if (left / block != other.left / block)
            return left < other.left;
        return right < other.right;
    }
};
struct record
{
    int curNode, par, cng;
};
const long long MXN = 1e5 + 5;
int node, edge, query;
int u[MXN], v[MXN];
Query process[MXN];
int par[MXN], level[MXN];
vector<record> restore[MXN];
void innit()
{
    for (int ii = 0; ii <= node; ++ii)
        par[ii] = ii, level[ii] = 0;
    for (int ii = 0; ii <= edge; ++ii)
        restore[ii].clear();
}
int rollback(int id)
{
    int cnt = 0;
    while (!restore[id].empty())
    {
        cnt += restore[id].back().cng;
        par[restore[id].back().curNode] = restore[id].back().par;
        restore[id].pop_back();
    }
    return cnt;
}
int f(int x, int pas)
{
    if (x == par[x])
        return x;
    int old = par[x];
    int cur = f(par[x], pas);
    restore[pas].push_back({x, old, 0});
    return par[x] = cur;
}
int unite(int x, int y, int pas)
{
    x = f(x, pas);
    y = f(y, pas);
    if (x != y)
    {
        if (level[x] < level[y])
            swap(x, y);
        restore[pas].push_back({y, y, 1});
        par[y] = x;
        return 1;
    }
    return 0;
}
void sol(int tc)
{
    cin >> node >> edge >> query;
    block = sqrt(edge);
    for (int ii = 0; ii < edge; ++ii)
    {
        cin >> u[ii] >> v[ii];
        --u[ii];
        --v[ii];
    }
    for (int ii = 0; ii < query; ++ii)
    {
        cin >> process[ii].left >> process[ii].right;
        process[ii].idx = ii;
        process[ii].left--;
        process[ii].right--;
    }
    sort(process, process + query);
    int res[query];
    for (int curBlock = 0, curIdx = 0; curBlock < (edge + block - 1) / block && curIdx < query; ++curBlock)
    {
        innit();
        int left = curBlock * block;
        int right = left - 1;
        int ans = node;
        while (curIdx < query && process[curIdx].left / block == curBlock)
        {
            int clr = (curBlock + 1) * block - 1;
            clr = min(right, clr);

            for (int ii = left; ii <= clr; ++ii)
                ans += rollback(ii);
            if (clr != right)
                ++right;
            else
                --clr;
            right = max(right, process[curIdx].left);
            for (int ii = process[curIdx].right; ii >= right; --ii)
                ans -= unite(u[ii], v[ii], ii);
            for (int ii = clr; ii >= process[curIdx].left; --ii)
                ans -= unite(u[ii], v[ii], ii);
            left = process[curIdx].left;
            right = process[curIdx].right;
            res[process[curIdx++].idx] = ans;
        }
    }
    for (int ii = 0; ii < query; ++ii)
        cout << res[ii] << "\n";
}