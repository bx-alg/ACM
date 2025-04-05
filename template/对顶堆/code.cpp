#include "bits/stdc++.h"
#include <iostream>
using namespace std;
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
#define vi vector<int>
#define vl vector<ll>
#define pqi priority_queue<int>
#define pb push_back

vector<double> solve(vi &a, int k)
{
    n = a.size();
    pqi l;
    priority_queue<int, vector<int>, greater<int>> r;
    int ls, rs;
    ls = rs = 0;
    map<int, int> del;
    rep(i, 0, k - 1)
        l.push(a[i]);
    rep(i, 1, k / 2)
    {
        r.push(l.top());
        l.pop();
    }
    rs = k / 2;
    ls = k - rs;
    vector<double> res;

    auto check = [&]()
    {
        int ba = ls - rs;
        if (ba == 2)
        {
            r.push(l.top());
            l.pop();
            ls--, rs++;
        }
        else if (ba == -1)
        {
            l.push(r.top());
            r.pop();
            ls++, rs--;
        }
    };

    rep(i, k, n)
    {
        while (l.size() && del[l.top()] > 0)
        {
            del[l.top()]--;
            l.pop();
        }
        while (r.size() && del[r.top()] > 0)
        {
            del[r.top()]--;
            r.pop();
        }
        int ba = ls - rs;
        if (ba == 0)
            res.pb(((double)l.top() + r.top()) / 2.0);
        else
            res.pb(l.top());
        if (i == n)
            break;

        if (a[i] <= l.top())
        {
            l.push(a[i]);
            ls++;
            ba++;
        }
        else
        {
            r.push(a[i]);
            rs++;
            ba--;
        }
        check();
        if (a[i - k] <= l.top())
            ls--;
        else
            rs--;
        check();
        del[a[i - k]]++;
    }
    return res;
}

class Solution
{
public:
    vector<double> medianSlidingWindow(vector<int> &nums, int k)
    {
        return solve(nums, k);
    }
};
