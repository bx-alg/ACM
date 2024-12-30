#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

int n, q;
const int N = 1e6 +10;
int c[N];
int p[N];
int to[N];
int bs;

struct Qu
{
    int l, r, t, ai;
} queries[N];

int res[N];
int cnt[N];
int distinct;

void add(int col)
{
    if (++cnt[col] == 1)
        distinct++;
}

void sub(int col)
{
    if (--cnt[col] == 0)
        distinct--;
}

void init()
{
    distinct = 0;
    memset(cnt, 0, sizeof cnt);
}

int main()
{
    init();
    cin >> n >> q;
    bs = pow(n, 0.66);
    for (int i = 1; i <= n; i++)
    {
        cin >> c[i];
    }
    char op;
    int a, b;
    int qi = 0;
    int mi = 0;
    while (q--)
    {
        cin >> op >> a >> b;
        if (op == 'Q')
        {
            ++qi;
            queries[qi] = {a, b, mi, qi};
        }
        else
        {
            p[++mi] = a;
            to[mi] = b;
        }
    }
 
auto cmp = [](const Qu &a, const Qu &b)
{
    if (a.l / bs != b.l / bs)
        return a.l / bs < b.l / bs;
    if (a.r / bs != b.r / bs)
        {
            if(a.l /bs % 2 == 0)
                return a.r / bs < b.r / bs;
            else return a.r / bs > b.r / bs;
         }
    return a.t < b.t;
};
    sort(queries + 1, queries + 1 + qi, cmp);
    int l, r;
    l = 1, r = 0;
    int x = 0;
    for (int i = 1; i <= qi; i++)
    {
        Qu &q = queries[i];
        while (l < q.l)
            sub(c[l++]);
        while (l > q.l)
            add(c[--l]);
        while (r < q.r)
            add(c[++r]);
        while (r > q.r)
            sub(c[r--]);
        while (x < q.t)
        {
            int pos = p[++x];
            if (l <= pos && r >= pos)
                sub(c[pos]), add(to[x]);
            swap(c[pos], to[x]);
        }
        while (x > q.t)
        {
            int pos = p[x];
            if (l <= pos && r >= pos)
                sub(c[pos]), add(to[x]);
            swap(c[pos], to[x--]);
        }
        res[q.ai] = distinct;
    }
    for (int i = 1; i <= qi; i++)
    {
        cout << res[i] << '\n';
    }
    return 0;
}