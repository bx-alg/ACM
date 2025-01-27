#include <iostream>
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e6 + 10;
int n, t, m;
int arr[N];
vector<pair<int,int>> g[N];
int e = 0;
void add(int u, int v)
{
    g[u].push_back({v, e});
    g[v].push_back({u, e++});
}

int top;
int ans[N];
int vis[N];

void dfs(int i)
{
    for (auto &p : g[i])
    {
        if (!vis[p.second])
        {
            vis[p.second] = 1;
            dfs(p.first);
        }
    }
    ans[++top] = i;
}

int main()
{

    cin >> n;
    vector<int> v(n + 1);
    v[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        v[i] = v[i - 1] + i;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            int c = v[i - 1] + j, l = v[i] + j, r = l + 1;
            add(c, l);
            add(c, r);
            add(l, r);
        }
    }
    cout << "Yes" << endl;
    memset(vis, 0, sizeof vis);
    top = 0;
    dfs(1);

    return 0;
}
