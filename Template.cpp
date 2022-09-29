
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