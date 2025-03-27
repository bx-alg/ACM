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
#define rep(i, j, k) for (int i = j; i <= k; i++)
#define per(i, j, k) for (int i = j; i >= k; i--)
#define mild (r - l) / 2 + l
#define paras int L, int R, int l, int r, int i
#define ld i << 1
#define rd i << 1 | 1

int a[N], stk[N], root, ls[N], rs[N];
void bd()
{
    rep(i, 0, n)
        ls[i] = rs[i] = 0;
    int r = 0;
    rep(i, 1, n)
    {
        while (r && a[stk[r]] > a[i])
            r--;
        if (r == 0)
            root = i;
        ls[i] = rs[stk[r]];
        rs[stk[r]] = i;
        stk[++r] = i;
    }
}

int res;
void dfs(int i, int l, int r)
{
    if (i == 0)
        return;
    int width = r - l + 1;
    int height = a[i];
    res = max(res, width * height);
    dfs(ls[i], l, i - 1);
    dfs(rs[i], i + 1, r);
}

void solve()
{

    bd();
    res = 0;
    dfs(root, 1, n);
    
}

class Solution
{
public:
    int largestRectangleArea(vector<int> &h)
    {
        n = h.size();
        rep(i, 1, n)
            a[i] = h[i - 1];
        solve();
        return res;
    }
};