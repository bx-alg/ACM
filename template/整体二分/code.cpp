#include "bits/stdc++.h"
#include <iostream>
using namespace std;
#define int long long
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

vector<int> nation[N];
int need[N];
int qid[N], lq[N], rq[N];

struct Node
{
    int l, r, num;
} rain[N];

int res[N];
int use;

int t[N];

void add(int i, int v)
{
    while (i <= m * 2)
        t[i] += v, i += i & -i;
}

void add(int l, int r, int num)
{
    add(l, num);
    add(r + 1, -num);
}

int que(int i)
{
    int sum = 0;
    while (i)
        sum += t[i], i ^= i & -i;
    return sum;
}

void dfs(int L, int R, int l, int r)
{
    if (L > R)
        return;
    if (l == r)
    {
        rp(i, L, R) res[qid[i]] = l;
    }
    else
    {
        int md = mild;
        while (use < md)
        {
            auto [l, r, num] = rain[++use];
            add(l, r, num);
        }
        while (use > md)
        {
            auto [l, r, num] = rain[use--];
            add(l, r, -num);
        }
        int lsiz = 0, rsiz = 0;
        rp(i, L, R)
        {
            int id = qid[i];
            int sum = 0;
            for (int j : nation[id])
            {
                sum += que(j) + que(j + m);
                if( sum >= need[id])break;
            }
            if (sum >= need[id])
                lq[++lsiz] = id;
            else
                rq[++rsiz] = id;
        }
        int j = L;
        rp(i, 1, lsiz) qid[j++] = lq[i];
        rp(i, 1, rsiz) qid[j++] = rq[i];
        dfs(L, L + lsiz - 1, l, md);
        dfs(L + lsiz, R, md + 1, r);
    }
}

void solve()
{
    cin >> n >> m;
    rp(i, 1, m)
    {
        int o;
        cin >> o;
        nation[o].pb(i);
    }
    rp(i, 1, n)
    {
        cin >> need[i];
        qid[i] = i;
    }
    int k;
    cin >> k;
    rp(i, 1, k)
    {
        int l, r, num;
        cin >> l >> r >> num;
        if (l > r)
            r += m;
        rain[i] = {l, r, num};
    }
    dfs(1, n, 1, k + 1);
    rp(i, 1, n)
    {
        if (res[i] == k + 1)
            cout << "NIE";
        else
            cout << res[i];
        cout << "\n";
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