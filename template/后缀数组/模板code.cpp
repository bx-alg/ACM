#include "bits/stdc++.h"
#include <iostream>
using namespace std;
using ll = long long;
const int N = 2e6 + 10;
int mod = 1e9 + 7;
int n, m, k;
#define get cin >>
#define ex cout <<
#define rep(i, j, k) for (int i = j; i <= k; i++)
#define per(i, j, k) for (int i = j; i >= k; i--)
int inv2 = (mod + 1) / 2;
int sa[N], cnt[N], x[N], y[N], lcp[N], rk[N];
int s[N];

void clr()
{
    memset(cnt, 0, sizeof cnt);
}

void getsa()
{
    rep(i, 1, n)
        x[i] = s[i];
    rep(i, 1, n)
        cnt[x[i]]++;
    rep(i, 1, m)
        cnt[i] += cnt[i - 1];
    per(i, n, 1)
        sa[cnt[x[i]]--] = i;
    for (int k = 1; k <= n; k <<= 1)
    {
        clr();
        rep(i, 1, n)
            y[i] = sa[i];
        rep(i, 1, n)
            cnt[x[y[i] + k]]++;
        rep(i, 1, m)
            cnt[i] += cnt[i - 1];
        per(i, n, 1)
            sa[cnt[x[y[i] + k]]--] = y[i];
        clr();
        rep(i, 1, n)
            y[i] = sa[i];
        rep(i, 1, n)
            cnt[x[y[i]]]++;
        rep(i, 1, m)
            cnt[i] += cnt[i - 1];
        per(i, n, 1)
            sa[cnt[x[y[i]]]--] = y[i];

        rep(i, 1, n)
            y[i] = x[i];
        m = 0;
        rep(i, 1, n)
        {
            if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k])
                x[sa[i]] = m;
            else
                x[sa[i]] = ++m;
        }
    }
}

void getlcp()
{
    rep(i, 1, n)
    {
        rk[sa[i]] = i;
    }
    lcp[1] = 0;
    int k = 0;
    rep(i, 1, n)
    {
        if (rk[i] == 1)
            continue;
        if (k)
            k--;
        int j = sa[rk[i] - 1];
        while (s[i + k] == s[j + k])
            k++;
        lcp[rk[i]] = k;
    }
}

struct Node
{
    int i, v;
};

void solve()
{
    get n >> k;
    rep(i, 1, n)
        get s[i];
    m = N;
    getsa();
    getlcp();
    deque<Node> q;
    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        while (q.size() && q.back().v >= lcp[i])
            q.pop_back();
        q.push_back({i, lcp[i]});
        if (q.front().i <= i - (k - 1))
            q.pop_front();
        if (i >= k - 1)
            ans = max(ans, q.front().v);
    }
    ex ans << "\n";
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