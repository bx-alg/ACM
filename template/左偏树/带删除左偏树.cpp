
#include "bits/stdc++.h"

using namespace std;

const int MAXN = 2000001;
int t, w, n, m;
long long k;
long long num[MAXN];
int up[MAXN];
int ls[MAXN];
int rs[MAXN];
int dist[MAXN];
int fa[MAXN];

void prepare()
{
    for (int i = 1; i <= n; i++)
    {
        up[i] = ls[i] = rs[i] = dist[i] = 0;
        fa[i] = i;
    }
}

int find(int i)
{
    return fa[i] == i ? i : (fa[i] = find(fa[i]));
}

int merge(int i, int j)
{
    if (i == 0 || j == 0)
    {
        return i + j;
    }
    if (num[i] < num[j] || (num[i] == num[j] && i > j))
    {
        swap(i, j);
    }
    rs[i] = merge(rs[i], j);
    up[rs[i]] = i;
    if (dist[ls[i]] < dist[rs[i]])
    {
        swap(ls[i], rs[i]);
    }
    dist[i] = dist[rs[i]] + 1;
    return i;
}

int pop(int i)
{
    int s = merge(ls[i], rs[i]);
    fa[ls[i]] = fa[rs[i]] = fa[i] = s;
    ls[i] = rs[i] = dist[i] = up[i] = 0;
    return s;
}

int remove(int i)
{
    int h = find(i);
    if (h == i)
    {
        return pop(i);
    }
    int f = up[i];
    int s = merge(ls[i], rs[i]);
    up[s] = f;
    fa[s] = h;
    if (ls[f] == i)
    {
        ls[f] = s;
    }
    else
    {
        rs[f] = s;
    }
    int d = dist[s];
    while (f && dist[f] > d + 1)
    {
        dist[f] = d + 1;
        if (dist[ls[f]] < dist[rs[f]])
            swap(ls[f], rs[f]);
        d = dist[f];
        f = up[f];
    }
    up[i] = ls[i] = rs[i] = dist[i] = 0;
    return fa[s];
}

void reduce(int i, long long v)
{
    int h = remove(i);
    num[i] = max(num[i] - v, 0LL);
    fa[h] = fa[i] = merge(h, i);
}

long long compute()
{
    long long ans = 0;
    long long mx = 0;
    for (int i = 1; i <= n; i++)
    {
        if (fa[i] == i)
        {
            ans += num[i];
            if (num[i] > mx)
                mx = num[i];
        }
    }
    if (w == 2)
    {
        ans -= mx;
    }
    else if (w == 3)
    {
        ans += mx;
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> t >> w >> k;
    for (int i = 1; i <= t; i++)
    {
        cin >> n >> m;
        prepare();
        for (int j = 1; j <= n; j++)
        {
            cin >> num[j];
        }
        for (int j = 1, op, a, b; j <= m; j++)
        {
            cin >> op >> a;
            if (op == 2)
            {
                reduce(a, num[a]);
            }
            else if (op == 3)
            {
                cin >> b;
                reduce(find(a), b);
            }
            else
            {
                cin >> b;
                int l = find(a);
                int r = find(b);
                if (l != r)
                {
                    int h = merge(l, r);
                    fa[l] = fa[r] = h;
                }
            }
        }
        long long ans = compute();
        if (ans == 0)
        {
            cout << "Gensokyo " << ans << endl;
        }
        else if (ans > k)
        {
            cout << "Hell " << ans << endl;
        }
        else
        {
            cout << "Heaven " << ans << endl;
        }
    }
    return 0;
}