
#include "bits/stdc++.h"
#include <iostream>
using namespace std;
using ll = long long;

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
const int N = 1e6 + 10;
int root = 0;
int cnt = 0;
int key[N];
int ls[N];
int rs[N];
int siz[N];
double pri[N];
int ans[N];
int lazy[N];
int ansi;

void up(int i)
{
    siz[i] = siz[ls[i]] + siz[rs[i]] + 1;
}

void down(int i)
{
    if (lazy[i])
    {
        swap(ls[i], rs[i]);
        lazy[ls[i]] ^= 1;
        lazy[rs[i]] ^= 1;
        lazy[i] = 0;
    }
}

void split(int l, int r, int i, int rank)
{
    if (i == 0)
    {
        rs[l] = ls[r] = 0;
        return;
    }
    down(i);
    if (siz[ls[i]] >= rank)
    {
        ls[r] = i;
        split(l, i, ls[i], rank);
    }
    else
    {
        rs[l] = i;
        split(i, r, rs[i], rank - siz[ls[i]] - 1);
    }
    up(i);
}

int merge(int l, int r)
{
    if (l == 0 || r == 0)
        return l + r;
    int head;
    down(l);
    down(r);
    if (pri[l] > pri[r])
    {
        rs[l] = merge(rs[l], r);
        head = l;
    }
    else
    {
        ls[r] = merge(l, ls[r]);
        head = r;
    }
    up(head);
    return head;
}

void inorder(int i)
{
    if (i != 0)
    {
        down(i);
        inorder(ls[i]);
        ans[++ansi] = key[i];
        inorder(rs[i]);
    }
}

int newNode(int c)
{
    int nid = ++cnt;
    ls[nid] = rs[nid] = 0;
    siz[nid] = 1;
    key[nid] = c;
    pri[nid] = (double)rand() / RAND_MAX;
    return nid;
}

void rev(int l, int r)
{
    split(0, 0, root, r);
    int lh = rs[0], rh = ls[0];
    split(0, 0, lh, l - 1);
    lazy[ls[0]] ^= 1;
    lh = merge(rs[0], ls[0]);
    root = merge(lh, rh);
}

void bd(int n)
{
    rep(i, 1, n)
    {
        int nid = newNode(i);
        root = merge(root, nid);
    }
}

void solve()
{
    srand(time(0));
    get n >> m;
    bd(n);
    rep(i, 1, m)
    {
        int l, r;
        get l >> r;
        rev(l, r);
    }
    ansi = 0;
    inorder(root);
    rep(i, 1, n)
            ex ans[i]
        << " ";
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
