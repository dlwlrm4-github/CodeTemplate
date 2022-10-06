#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;
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
