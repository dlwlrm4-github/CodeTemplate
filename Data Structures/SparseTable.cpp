
#include <bits/stdc++.h>
using namespace std;

const int MXN = 1e5 + 5;

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

int query(int L, int R)
{
    int jj = lg[R - L + 1];
    int mn = min(st[L][jj], st[R - (1 << jj) + 1][jj]);
    return mn;
}