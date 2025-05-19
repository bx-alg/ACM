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

const int M = 1e7;
int val[M];
int headfa[N], headsiz[N], ls[M], rs[M];
int cnt;
int bd(int l, int r, int t)
{
    int i = ++cnt;
    if (l == r)
    {
        if (t)
            val[i] = 1;
        else
            val[i] = l;
        return i;
    }
    int md = mild;
    ls[i] = bd(l, md, t);
    rs[i] = bd(md + 1, r, t);
    return i;
}

int cp(int i)
{
    int j = ++cnt;
    val[j] = val[i];
    ls[j] = ls[i];
    rs[j] = rs[i];
    return j;
}

int change(paras, int v)
{
    i = cp(i);
    if (cover)
    {
        val[i] = v;
        return i;
    }
    int md = mild;
    if (L <= md)
    {
        ls[i] = change(L, R, l, md, ls[i], v);
    }
    if (R > md)
        rs[i] = change(L, R, md + 1, r, rs[i], v);
    return i;
}

int que(paras)
{
    if (cover)
        return val[i];
    int md = mild;
    if (L <= md)
        return que(L, R, l, md, ls[i]);
    if (R > md)
        return que(L, R, md + 1, r, rs[i]);
    return 0;
}

int find(int i, int h)
{
    while (1)
    {
        int f = que(i, i, 1, n, h);
        if (f == i)
            return i;
        i = f;
    }
}

void unite(int a, int b, int k)
{
    int fa = find(a, headfa[k]);
    int fb = find(b, headfa[k]);
    if (fa != fb)
    {
        int sa = que(fa, fa, 1, n, headsiz[k]);
        int sb = que(fb, fb, 1, n, headsiz[k]);
        if (sa < sb)
            swap(fa, fb);
        headfa[k + 1] = change(fb, fb, 1, n, headfa[k], fa);
        headsiz[k + 1] = change(fa, fa, 1, n, headsiz[k], sa + sb);
    }
}

void solve()
{
    cin >> n >> m;
    cnt = 0;
    headfa[0] = bd(1, n, 0);
    headsiz[0] = bd(1, n, 1);

    rp(i, 1, m)
    {
        int o, a, b, k;
        cin >> o;
        headfa[i] = headfa[i - 1];
        headsiz[i] = headsiz[i - 1];
        if (o == 1)
        {
            cin >> a >> b;
            unite(a, b, i - 1);
        }
        else if (o == 2)
        {
            cin >> k;
            headfa[i] = headfa[k];
            headsiz[i] = headsiz[k];
        }
        else
        {
            cin >> a >> b;
            a = find(a, headfa[i]);
            b = find(b, headfa[i]);
            cout << (a == b) << "\n";
        }
    }
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    while (T--)
    {
        solve();
    }
    return 0;
}