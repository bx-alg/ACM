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

int ball[N][2];
int ans[N];
int father[N];
int ecnt[N], pcnt[N];
int stk[N][2], tp;

struct Edge
{
    int v, nx;
} e[N * 2];
int h[N], cnt;
void add(int u, int v)
{
    e[++cnt] = {v, h[u]};
    h[u] = cnt;
}

int find(int a)
{
    while (1)
    {
        int f = father[a];
        if (f == a)
            return a;
        a = f;
    }
}

void unite(int a, int b)
{
    int sa = pcnt[a];
    int sb = pcnt[b];
    if (sa < sb)
        swap(a, b);
    father[b] = a;
    ecnt[a] += ecnt[b] + 1;
    pcnt[a] += pcnt[b];
    stk[++tp][0] = a;
    stk[tp][1] = b;
}

void undo()
{
    int a = stk[tp][0];
    int b = stk[tp--][1];
    ecnt[a] -= ecnt[b] + 1;
    pcnt[a] -= pcnt[b];
    father[b] = b;
}

void dfs(int u, int f)
{
    int a = ball[u][0];
    int b = ball[u][1];
    int fa = find(a);
    int fb = find(b);
    if (pcnt[fa] < pcnt[fb])
        swap(fa, fb);
    int united = 0;
    ans[u] = ans[f];
    if (fa == fb)
    {
        if (ecnt[fa] < pcnt[fa])
        {
            ans[u]++;
        }
        ecnt[fa]++;
    }
    else
    {
        united = 1;
        if (ecnt[fa] < pcnt[fa] || ecnt[fb] < pcnt[fb])
        {
            ans[u]++;
            unite(fa, fb);
        }
        else
        {
            unite(fa, fb);
        }
    }
    for (int ei = h[u]; ei; ei = e[ei].nx)
    {
        int v = e[ei].v;
        if (v == f)
            continue;
        dfs(v, u);
    }
    if (united)
        undo();
    else
        ecnt[fa]--;
}

void solve()
{
    cin >> n;
    rp(i, 1, n) father[i] = i, ecnt[i] = 0, pcnt[i] = 1;
    rp(i, 1, n)
    {
        int a, b;
        cin >> a >> b;
        ball[i][0] = a;
        ball[i][1] = b;
    }
    rp(i, 1, n - 1)
    {
        int u, v;
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    ans[1] = 1;
    dfs(1, 0);
    rp(i, 2, n)
            cout
        << ans[i] << " ";
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