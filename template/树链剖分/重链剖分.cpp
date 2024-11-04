#include <bits/stdc++.h>
using namespace std;
// 链接:
https://loj.ac/p/10138
const int N = 3e4 + 10;
const int M = 1e5;
int head[N], nex[M], to[M], cnt;
int val[N], siz[N], dep[N], fa[N], top[N], bigson[N], dfn[N];
int tim, sum[N * 4], maxval[N * 4];
int dfntoi[N];

void add(int u, int v)
{
    nex[++cnt] = head[u];
    head[u] = cnt;
    to[cnt] = v;
}

void dfs1(int u, int f)
{
    fa[u] = f;
    dep[u] = dep[f] + 1;
    siz[u] = 1;
    int w = 0;

    for (int ei = head[u]; ei; ei = nex[ei])
    {
        int v = to[ei];
        if (v != f)
        {
            dfs1(v, u);
            siz[u] += siz[v];
            if (siz[v] > w)
            {
                bigson[u] = v;
                w = siz[v];
            }
        }
    }
}

void dfs2(int u, int h)
{
    
    dfntoi[tim] = u;
    dfn[u] = tim++;
    top[u] = h;

    if (bigson[u])
        dfs2(bigson[u], h);

    for (int ei = head[u]; ei; ei = nex[ei])
    {
        int v = to[ei];
        if (v != fa[u] && v != bigson[u])
            dfs2(v, v);
    }
}

void init()
{
    memset(bigson, 0, sizeof bigson);
    memset(head, 0, sizeof head);
    cnt = 0;
    tim = 1;
    siz[0] = 0;
    fa[0] = 0;
    dep[0] = 0;
}

void build(int i = 1, int l = 1, int r = N)
{
    if (l == r)
    {
        sum[i] = val[dfntoi[l]];
        maxval[i] = val[dfntoi[l]];
        return;
    }
    
    int mid = (l + r) / 2;
    build(i << 1, l, mid);
    build(i << 1 | 1, mid + 1, r);
    sum[i] = sum[i << 1] + sum[i << 1 | 1];
    maxval[i] = max(maxval[i << 1], maxval[i << 1 | 1]);
}

void change(int i, int pos, int val, int curl = 1, int curr = N)
{
    if (curl == curr)
    {
        sum[i] = val;
        maxval[i] = val;
        return;
    }

    int mid = (curl + curr) / 2;
    if (pos <= mid)
        change(i << 1, pos, val, curl, mid);
    else
        change(i << 1 | 1, pos, val, mid + 1, curr);

    sum[i] = sum[i << 1] + sum[i << 1 | 1];
    maxval[i] = max(maxval[i << 1], maxval[i << 1 | 1]);
}

int queryMax(int i, int ql, int qr, int curl = 1, int curr = N)
{
    if (ql <= curl && qr >= curr)
        return maxval[i];

    int mid = (curl + curr) / 2;
    int ans = INT_MIN;

    if (ql <= mid)
        ans = max(ans, queryMax(i << 1, ql, qr, curl, mid));
    if (qr > mid)
        ans = max(ans, queryMax(i << 1 | 1, ql, qr, mid + 1, curr));

    return ans;
}

int querySum(int i, int ql, int qr, int curl = 1, int curr = N)
{
    if (ql <= curl && qr >= curr)
        return sum[i];

    int mid = (curl + curr) / 2;
    int ans = 0;

    if (ql <= mid)
        ans += querySum(i << 1, ql, qr, curl, mid);
    if (qr > mid)
        ans += querySum(i << 1 | 1, ql, qr, mid + 1, curr);

    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    init();
    int n, q;
    cin >> n;

    for (int i = 1, a, b; i < n; i++)
    {
        cin >> a >> b;
        add(a, b);
        add(b, a);
    }
    
    for (int i = 1; i <= n; i++)
        cin >> val[i];

    dfs1(1, 0);
    dfs2(1, 1);
    build();
    
    cin >> q;
    string tp;
    
    for (int i = 0, a, b; i < q; i++)
    {
        cin >> tp >> a >> b;

        if (tp == "CHANGE")
        {
            change(1, dfn[a], b);
        }
        else if (tp == "QMAX")
        {
            int ans = INT_MIN;
            while (top[a] != top[b])
            {
                if (dep[top[a]] < dep[top[b]]) swap(a, b);
                ans = max(ans, queryMax(1, dfn[top[a]], dfn[a]));
                a = fa[top[a]];
            }
            if (dep[a] > dep[b]) swap(a, b);
            ans = max(ans, queryMax(1, dfn[a], dfn[b]));
            cout << ans << endl;
        }
        else
        {
            int ans = 0;
            while (top[a] != top[b])
            {
                if (dep[top[a]] < dep[top[b]]) swap(a, b);
                ans += querySum(1, dfn[top[a]], dfn[a]);
                a = fa[top[a]];
            }
            if (dep[a] > dep[b]) swap(a, b);
            ans += querySum(1, dfn[a], dfn[b]);
            cout << ans << endl;
        }
    }
    return 0;
}
