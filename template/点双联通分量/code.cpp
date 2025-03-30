#include "bits/stdc++.h"
#include <iostream>
using namespace std;
using ll = long long;
const int N = 2e6 + 10;
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
#define pb push_back

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

int dfn[N], low[N], siz[N], cp[N], stk[N];
int id, tot, root, tp;
map<int, vector<int>> dcc;

void dfs(int u)
{
    dfn[u] = low[u] = ++tot;
    stk[++tp] = u;
    if (!h[u])
    {
        dcc[++id].pb(u);
        return;
    }
    int child = 0;
    for (int ei = h[u]; ei; ei = e[ei].nx)
    {
        int v = e[ei].v;
        if (!dfn[v])
        {
            dfs(v);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u])
            {
                child++;
                if (u != root || child > 1)
                    cp[u] = 1;
                int x;
                ++id;
                dcc[id].pb(u);
                do
                {
                    x = stk[tp--];
                    dcc[id].pb(x);
                } while (x != v);
            }
        }
        else
            low[u] = min(dfn[v], low[u]);
    }
}

void solve()
{
    get n >> m;
    cnt = 1;
    rep(i, 1, m)
    {
        int u, v;
        get u >> v;
        if (u == v)
            continue;
        add(u, v);
        add(v, u);
    }
    rep(i, 1, n)
    {
        if (!dfn[i])
            root = i, dfs(i);
    }
    ex id << "\n";
    rep(i, 1, id)
    {
        ex dcc[i].size() << " ";
        for (int j : dcc[i])
            ex j << " ";
        ex "\n";
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