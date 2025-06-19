#include "bits/stdc++.h"
#include <iostream>
using namespace std;
#define int long long
using ll = long long;
const int N = 1e6 + 10;
int mod = 1e9 + 7;
int n, m, k;
int inv2 = (mod + 1) / 2;
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
#define lpara L, R, l, md, ld
#define rpara L, R, md + 1, r, rd
template <typename T>
void dbg(const T &t)
{
    cerr << ' ' << t;
}

template <typename T, typename... Args>
void dbg(const T &t, const Args &...args)
{
    cerr << ' ' << t;
    dbg(args...);
}
#define bg(...) (cerr << #__VA_ARGS__ << ":", dbg(__VA_ARGS__), cerr << "\n")
mt19937 rng(time(0));

int a[N];
int bit[62];
int zero;

void lbase(int n)
{
    rp(i, 1, n)
    {
        int num = a[i];
        pr(j, 59, 0)
        {
            if (num >> j & 1)
            {
                if (bit[j] == 0)
                {
                    bit[j] = num;
                    break;
                }
                else
                    num ^= bit[j];
            }
        }
    }
}

void solve()
{
    cin >> n;
    memset(bit,0,sizeof bit);
    rp(i, 1, n)
    {
        cin >> a[i];
    }
    lbase(n);

    rp(i, 0, 60)
    {
        if (bit[i] == 0)
        {
            cout << (1LL << i);
            break;
        }
    }

    cout << "\n";
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    cin >> T;
    while (T--)
    {
        solve();
    }
    return 0;
}