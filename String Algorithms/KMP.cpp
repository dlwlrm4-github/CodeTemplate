
#include <bits/stdc++.h>
using namespace std;

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