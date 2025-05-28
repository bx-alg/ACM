#include "bits/stdc++.h"
#include <iostream>
using namespace std;
using ll = long long;
const int N = 1e6 + 10;
int mod = 1e9 + 7;
int n, m, k;
int inv2 = (mod + 1) / 2;
#define get cin >>
#define ex cout <<
#define rp(i, j, k) for (int i = j; i <= k; i++)
#define pr(i, j, k) for (int i = j; i >= k; i--)
#define mild (r - l) / 2 + l
#define paras int L, int R, int l, int r, int i
#define ld i << 1
#define cover L <= l &&R >= r
#define rd i << 1 | 1
#define vi vector<int>
#define vl vector<ll>
#define pb push_back

class Solution
{

    int father[N], siz[N];

    int find(int a)
    {
        while (a != father[a])
        {
            a = father[a];
        }
        return a;
    }

    void unite(int a, int b)
    {
        int fa = find(a);
        int fb = find(b);
        if (fa != fb)
        {
            int sa = siz[fa];
            int sb = siz[fb];
            if (sa < sb)
                swap(fa, fb);
            father[fb] = fa;
            siz[fa] += siz[fb];
        }
    }

public:
    bool isBipartite(vector<vector<int>> &g)
    {
        int n = g.size();
        int res = 1;
        rp(i, 0, n * 2 - 1) father[i] = i, siz[i] = 1;
        for (int i = 0; i < n; i++)
        {
            for (int v : g[i])
            {
                if (find(i) == find(v))
                    res = 0;
                unite(i, v + n);
                unite(v, i + n);
            }
        }
        return res;
    }
};