#include "bits/stdc++.h"
#include <iostream>
using namespace std;
#define int long long
using ll = long long;
const int N = 1e6 + 10;
int n, t, m;
int arr[N];
int ls[N], rs[N];
int from[N], to[N];
int fa[N];
int dist[N];
int stk[N];
int ans[N];
int siz[N];
int sum = 0;
int find(int i)
{
    fa[i] = (fa[i] == i ? fa[i] : find(fa[i]));
    return fa[i];
}

void prepare()
{
    dist[0] = -1;
    for (int i = 1; i <= n; i++)
        from[i] = i, to[i] = i, fa[i] = i, siz[i] = 1;
}

int merge(int i, int j)
{
    if (i == 0 || j == 0)
        return i + j;
    if (arr[i] < arr[j])
        swap(i, j);
    rs[i] = merge(rs[i], j);
    if (dist[ls[i]] < dist[rs[i]])
        swap(ls[i], rs[i]);
    fa[rs[i]] = fa[ls[i]] = i;
    dist[i] = dist[rs[i]] + 1;
    return i;
}

int pop(int i)
{
    i = find(i);
    fa[ls[i]] = ls[i];
    fa[rs[i]] = rs[i];
    int h = merge(ls[i], rs[i]);
    fa[i] = h;
    return h;
}

void compute()
{

    int stackSize = 0;
    for (int i = 1, pre, cur, s; i <= n; i++)
    {
        while (stackSize > 0)
        {
            pre = find(stk[stackSize]);
            cur = find(i);
            if (arr[pre] <= arr[cur])
            {
                break;
            }
            s = siz[pre] + siz[cur];
            cur = merge(pre, cur);
            while (s > ((i - from[pre] + 1 + 1) / 2))
            {
                cur = pop(cur);
                s--;
            }
            from[cur] = from[pre];
            to[cur] = i;
            siz[cur] = s;
            stackSize--;
        }
        stk[++stackSize] = i;
    }
    sum = 0;
    for (int i = 1, cur; i <= stackSize; i++)
    {
        cur = find(stk[i]);
        for (int j = from[cur]; j <= to[cur]; j++)
        {
            ans[j] = arr[cur];
            sum += llabs(ans[j] - arr[j]);
        }
    }
}

void solve()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
        arr[i] -= i;
    }
    prepare();
    compute();
    cout << sum << endl;
    for (int i = 1; i <= n; i++)
        cout << ans[i] + i << " ";
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