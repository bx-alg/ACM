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

int root, id;
int key[N], ls[N], rs[N], siz[N];
double pri[N];

int find(int i, int x)
{
    if (i == 0)
        return 0;
    if (x == key[i])
        return i;
    else if (x < key[i])
        return find(ls[i], x);
    else
        return find(rs[i], x);
}

void up(int i)
{
    siz[i] = siz[ls[i]] + siz[rs[i]] + 1;
}

void split(int l, int r, int i, int x)
{
    if (i == 0)
    {
        rs[l] = ls[r] = 0;
        return;
    }
    if (key[i] <= x)
    {
        rs[l] = i;
        split(i, r, rs[i], x);
    }
    else
    {
        ls[r] = i;
        split(l, i, ls[i], x);
    }
    up(i);
}
int newNode(int x)
{
    int nid = ++id;
    siz[nid] = 1;
    pri[nid] = (double)rand() / RAND_MAX;
    key[nid] = x;
    ls[nid] = rs[nid] = 0;
    return nid;
}

int merge(int l, int r)
{
    if (l == 0 || r == 0)
        return l + r;
    int head;
    if (pri[l] > pri[r])
        rs[l] = merge(rs[l], r), head = l;
    else
        ls[r] = merge(l, ls[r]), head = r;
    up(head);
    return head;
}

void add(int x)
{
    split(0, 0, root, x);
    int lroot = rs[0];
    int rroot = ls[0];
    int nid = newNode(x);
    lroot = merge(lroot, nid);
    root = merge(lroot, rroot);
}

void del(int x)
{
    split(0, 0, root, x);
    int l = rs[0];
    int r = ls[0];
    split(0, 0, l, x - 1);
    int ll = rs[0];
    int rr = ls[0];
    int h = merge(ls[rr], rs[rr]);
    root = merge(merge(ll, h), r);
}

int rk(int x)
{
    split(0, 0, root, x - 1);
    int ans = siz[rs[0]];
    root = merge(rs[0], ls[0]);
    return ans +1;
}
int index(int i, int rank)
{
    if (siz[ls[i]] < rank && siz[ls[i]] + 1 >= rank)
        return key[i];
    else if (siz[ls[i]] >= rank)
        return index(ls[i], rank);
    else
        return index(rs[i], rank - siz[ls[i]] - 1);
}

int getnumbyrk(int rank)
{
    return index(root, rank);
}

int pre(int x)
{
    int rank = rk(x);
    return getnumbyrk(rank - 1);
}

int post(int x)
{
    int rank = rk(x + 1);
    return getnumbyrk(rank);
}

void solve()
{
    get n;
    root = id = 0;
    rep(i, 1, n)
    {
        int op, x;
        get op >> x;
        switch (op)
        {
        case 1:
            add(x);
            break;
        case 2:
            del(x);
            break;
        case 3:
            ex rk(x) << "\n";
            break;
        case 4:
            ex getnumbyrk(x) << "\n";
            break;
        case 5:
            ex pre(x) << "\n";
            break;
        case 6:
            ex post(x) << "\n";
            break;
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T = 1;
    srand(time(0));
    while (T--)
    {
        solve();
    }
    return 0;
}