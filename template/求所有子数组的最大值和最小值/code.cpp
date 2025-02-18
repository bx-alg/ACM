#include "bits/stdc++.h"
#include <iostream>
using namespace std;
using ll = long long;
const int N = 1e6 + 10;
int n, t, m, q;
int arr[N];

void solve()
{
    cin >> n >> m >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    vector<int> mx(n + 1), mi(n + 1);
    mx[n] = mi[n] = n+1;
    for (int i = n - 1; i >= 1; i--)
    {
        int t = i + 1;
        while (t <= n && a[t] <= a[i])
        {
            t = mx[t];
        }
        mx[i] = t;
        t = i + 1;
        while (t <= n && a[t] >= a[i])
        {
            t = mi[t];
        }
        mi[i] = t;
    }
    map<ll, int> mp;
    for (int i = 1; i <= n; i++)
    {
        int x = i, y = i;
        while (1)
        {
            if (mx[x] < mi[y])
            {
                mp[a[x] * a[y]] += mx[x] - max(x, y);
                x = mx[x];
            }
            else
            {
                mp[a[x] * a[y]] += mi[y] - max(x, y);
                y = mi[y];
            }
            if (x > n || y > n)
                break;
        }
    }
    vector<pair<int,int>>v(mp.begin(),mp.end());
    for(int i = v.size()-2; i >= 0;i-- )
        v[i].second += v[i+1].second;
    v.push_back({1e18,0});
    ll res = 0;
    while (q--)
    {
        ll k;
        cin >> k;
        res  += (*lower_bound(v.begin(),v.end(),pair<int,int>{k,0})).second;
    }
    cout << res << endl;
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