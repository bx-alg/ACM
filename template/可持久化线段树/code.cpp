#include "bits/stdc++.h"
#include <iostream>
using namespace std;
using ll = long long;
const int N = 2e5 + 10;
const int M = 2e7;
int n, t, m;
int a[N];
int sorted[N];
int toroot[N];
int sum[M];
int s = 0;
int cnt = 0;
int ls[M], rs[M];

void cle()
{
    memset(ls, 0, sizeof ls);
    memset(rs, 0, sizeof rs);
    memset(sum, 0, sizeof sum);
}

int build(int l, int r)
{
    int node = ++cnt;
    sum[node] = 0;
    if (l < r)
    {
        int mid = (r + l) >> 1;
        if (l <= mid)
            ls[node] = build(l, mid);
        if (r > mid)
            rs[node] = build(mid + 1, r);
    }
    return node;
}

int copy(int h)
{
    int node = ++cnt;
    ls[node] = ls[h];
    rs[node] = rs[h];
    sum[node] = sum[h];
    return node;
}

int update(int h, int l, int r, int j, int val)
{
    int node = copy(h);
    if (l == r)
        sum[node] += val;
    else
    {
        int mid = (r + l) >> 1;
        if (j <= mid)
            ls[node] = update(ls[node], l, mid, j, val);
        if (j > mid)
            rs[node] = update(rs[node], mid + 1, r, j, val);
        sum[node] = sum[ls[node]] + sum[rs[node]];
    }

    return node;
}

int query(int l, int r, int k, int lh, int rh)
{
    if (l == r)
        return l;
    int mid = (r + l) >> 1;
    int sub = sum[ls[rh]] - sum[ls[lh]];
    if (sub >= k)
        return query(l, mid, k, ls[lh], ls[rh]);
    else
        return query(mid + 1, r, k - sub, rs[lh], rs[rh]);
}

void solve()
{
    cin >> n >> m;
    cle();
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    int l, r, k;
    copy(a + 1, a + 1 + n, sorted + 1);
    sort(sorted + 1, sorted + 1 + n);
    s = 1;
    unordered_map<int, int> torank;
    torank[sorted[1]] = 1;
    for (int i = 1; i <= n; i++)
    {
        if (sorted[s] != sorted[i])
            sorted[++s] = sorted[i], torank[sorted[s]] = s;
    }
    toroot[0] = build(1, s);
    for (int i = 1; i <= n; i++)
    {
        int k = torank[a[i]];
        toroot[i] = update(toroot[i - 1], 1, s, k, 1);
    }
    for (int i = 0; i < m; i++)
    {
        cin >> l >> r >> k;
        int res = sorted[query(1, s, k, toroot[l - 1], toroot[r])];
        cout << res << endl;
    }
}

int main()
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