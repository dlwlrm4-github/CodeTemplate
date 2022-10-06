
#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
public:
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

class SegmentTree
{
public:
    vector<pair<int, int>> segTree;
    void innit(int n)
    {
        segTree.resize(4 * n);
    }
    pair<int, int> combine(pair<int, int> x, pair<int, int> y)
    {
        pair<int, int> curPair;
        curPair.first = min(x.first, y.first);
        curPair.second = 0;
        if (curPair.first == x.first)
            curPair.second += x.second;
        if (curPair.first == y.first)
            curPair.second += y.second;
        return curPair;
    }
    void build(int aa[], int id, int left, int right)
    {
        if (left == right)
        {
            segTree[id] = {aa[left], 1};
            return;
        }
        int mid = (left + right) / 2;
        build(aa, 2 * id, left, mid);
        build(aa, 2 * id + 1, mid + 1, right);
        segTree[id] = combine(segTree[2 * id], segTree[2 * id + 1]);
        return;
    }
    void update(int id, int left, int right, int pos, int rep)
    {
        if (left == right)
        {
            segTree[id] = {rep, 1};
            return;
        }
        int mid = (left + right) / 2;
        if (pos <= mid)
            update(2 * id, left, mid, pos, rep);
        else
            update(2 * id + 1, mid + 1, right, pos, rep);
        segTree[id] = combine(segTree[2 * id], segTree[2 * id + 1]);
        return;
    }
    pair<int, int> query(int id, int left, int right, int l, int r)
    {
        if (l > r)
            return {1e9, 0};
        if (left == l && right == r)
            return segTree[id];
        int mid = (left + right) / 2;
        pair<int, int> x = query(2 * id, left, mid, l, min(mid, r));
        pair<int, int> y = query(2 * id + 1, mid + 1, right, max(mid + 1, l), r);
        return combine(x, y);
    }
};

class SegmentTree
{
public:
    struct node
    {
        long long pre, suf, sum, res;
    };
    vector<node> segTree;
    void innit(int n)
    {
        segTree.resize(4 * n);
    }
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
    void build(int aa[], int id, int left, int right)
    {
        if (left == right)
        {
            segTree[id] = make(aa[left]);
            return;
        }
        int mid = (left + right) / 2;
        build(aa, 2 * id, left, mid);
        build(aa, 2 * id + 1, mid + 1, right);
        segTree[id] = combine(segTree[2 * id], segTree[2 * id + 1]);
        return;
    }
    void update(int id, int left, int right, int pos, int val)
    {
        if (left == right)
        {
            segTree[id] = make(val);
            return;
        }
        int mid = (left + right) / 2;
        if (pos <= mid)
            update(2 * id, left, mid, pos, val);
        else
            update(2 * id + 1, mid + 1, right, pos, val);
        segTree[id] = combine(segTree[2 * id], segTree[2 * id + 1]);
        return;
    }
};