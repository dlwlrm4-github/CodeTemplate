#include <bits/stdc++.h>
using namespace std;
// better way to is to sort even block increasing odd decreasing
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
