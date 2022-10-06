
#include <bits/stdc++.h>
using namespace std;

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
