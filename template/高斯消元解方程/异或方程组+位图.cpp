#include "bits/stdc++.h"
#include <iostream>
using namespace std;
using ll = long long;
const int N = 2e3 + 10;
int mod = 1e9 + 7;
int n, m, k, p;
#define get cin >>
#define ex cout <<

#define rep(i, j, k) for (int i = j; i <= k; i++)
#define per(i, j, k) for (int i = j; i >= k; i--)
int inv2 = (mod + 1) / 2;
const int M = 100;
int bit = 64;
ll mat[N][M];

void setbit(int i, int j, int v)
{
    j--;
    int p = j / bit;
    int q = j % bit;
    mat[i][p] |= (ll)v << q;
}

int getbit(int i, int j)
{
    j--;
    return mat[i][j / bit] >> (j % bit) & 1;
}

void eor(int j, int i)
{
    rep(k, 0, (p + 1) / bit)
    {
        mat[j][k] ^= mat[i][k];
    }
}

int kth;

void gauss(int n)
{
    kth = 0;
    rep(i, 1, n)
    {
        int c = i;
        rep(j, i, n)
        {
            if (getbit(j, i) == 1)
            {
                c = j;
                break;
            }
        }
        kth = max(kth, c);
        swap(mat[i], mat[c]);
        if (getbit(i, i) == 0)
            return;
        rep(j, 1, n)
        {
            if (getbit(j, i) == 0 || j == i)
                continue;
            eor(j, i);
        }
    }
}

void solve()
{
    get n >> m;
    p = max(n, m);
    rep(i, 1, m)
    {
        string s;
        int state;
        get s >> state;
        rep(j, 1, s.size())
        {
            setbit(i, j, s[j - 1] - '0');
        }
        setbit(i, p + 1, state);
    }
    gauss(p);
    int sign = 1;
    rep(i, 1, n)
    {
        if (getbit(i, i) == 0)
            sign = 0;
    }
    if (!sign)
        ex "Cannot Determine\n";
    else
    {
        ex kth << "\n";
        rep(i, 1, n)
        {
            if (getbit(i, p + 1) == 1)
                ex "?y7M#";
            else
                ex "Earth";
            ex "\n";
        }
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;

    while (T--)
    {
        solve();
    }
    return 0;
}