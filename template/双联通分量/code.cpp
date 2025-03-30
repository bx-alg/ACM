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
#define rep(i, j, k) for (int i = j; i <= k; i++)
#define per(i, j, k) for (int i = j; i >= k; i--)
#define mild (r - l) / 2 + l
#define paras int L, int R, int l, int r, int i
#define ld i << 1
#define rd i << 1 | 1

struct Edge
{
    int v, nx;
} e[N * 2];
int h[N], cnt;
void add(int u, int v)
{
    e[cnt] = {v, h[u]};
    h[u] = cnt;
    cnt++;
}
int a[N];
int f[N];
int dfn[N], low[N], stk[N], scc[N], siz[N], weit[N], bri[N];
int id, tp, tot;
void dfs(int u, int inedge)
{
    dfn[u] = low[u] = ++tot;
    stk[++tp] = u;

    for (int ei = h[u]; ~ei; ei = e[ei].nx)
    {
        int v = e[ei].v;
        if (!dfn[v])
        {
            dfs(v, ei);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u])
                bri[ei] = bri[ei ^ 1] = 1;
        }
        else if (ei != (inedge ^ 1))
        {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if (low[u] == dfn[u])
    {
        ++id;
        int x;
        do
        {
            x = stk[tp--];
            scc[x] = id;
            siz[id]++;

        } while (x != u);
    }
}

void solve()
{
    get n >> m;
    rep(i, 0, 2 * m)
        h[i] = -1;
    rep(i, 1, m)
    {
        int u, v;
        get u >> v;
        add(u, v);
        add(v, u);
    }
    rep(i, 1, n)
    {
        if (!dfn[i])
            dfs(i, -1);
    }
    vector<int> in(id + 1);
    rep(i, 0,cnt-1)
    {
        if(bri[i])
            in[scc[e[i].v]]++;
    }
    int cnt = 0;
    rep(i, 1, id)
    {
        cnt += (in[i] == 1);
    }
    ex(cnt + 1) / 2 << "\n";
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