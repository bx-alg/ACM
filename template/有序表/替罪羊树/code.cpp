#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int n;
double alpha = 0.7;

int top, father, side;
int ci;

int collect[N];

int l[N];
int r[N];
int cnt[N];
int siz[N];
int diff[N];
int key[N];
int head;
int node;

void init()
{
    node = 0;
    head = 0;
    memset(l, 0, sizeof l);
    memset(r, 0, sizeof r);
    memset(cnt, 0, sizeof cnt);
    memset(siz, 0, sizeof siz);

    memset(diff, 0, sizeof diff);
}

void up(int i)
{
    siz[i] = siz[l[i]] + siz[r[i]] + cnt[i];
    diff[i] = diff[l[i]] + diff[r[i]] + (cnt[i] > 0 ? 1 : 0);
}

int imbalance(int i)
{
    return max(diff[l[i]], diff[r[i]]) > diff[i] * alpha;
}

int initNode(int x)
{
    key[++node] = x;
    cnt[node] = siz[node] = diff[node] = 1;
    return node;
}

void add(int i, int f, int s, int x)
{
    if (i == 0)
    {
        int h = initNode(x);
        if (f == 0)
        {
            head = h;
        }
        else if (s == 0)
        {
            l[f] = h;
        }
        else
            r[f] = h;
        return;
    }
    if (key[i] == x)
    {
        cnt[i]++;
    }
    else if (key[i] > x)
    {
        add(l[i], i, 0, x);
    }
    else
    {
        add(r[i], i, 1, x);
    }
    up(i);
    if (imbalance(i))
    {
        top = i;
        father = f;
        side = s;
    }
}

void inorder(int i)
{
    if (i == 0)
        return;
    inorder(l[i]);
    if (cnt[i] > 0)
        collect[++ci] = i;
    inorder(r[i]);
}

void inorder()
{
    inorder(top);
}

int build(int L, int R)
{
    if (L > R)
        return 0;
    int mid = (R + L) >> 1;
    int h = collect[mid];
    l[h] = build(L, mid - 1);
    r[h] = build(mid + 1, R);
    up(h);
    return h;
}

int build()
{
    return build(1, ci);
}

void rebuild()
{
    if (top != 0)
    {
        ci = 0;
        inorder();
        if (ci)
        {
            if (father == 0)
                head = build();
            else if (side == 0)
            {
                l[father] = build();
            }
            else
                r[father] = build();
        }
    }
}

void add(int x)
{
    top = father = side = 0;
    add(head, 0, 0, x);
    rebuild();
}

void del(int i, int f, int s ,int x)
{
    if (key[i] == x)
    {
        cnt[i]--;
    }
    else if (x < key[i])
        del(l[i], i, 0, x);
    else
        del(r[i], i, 1, x);
    up(i);
    if (imbalance(i))
    {
        top = i;
father = f;
        side = s;
    }
}

int small(int i, int x)
{
    if(i == 0) return 0;
    if (key[i] < x)
        return siz[l[i]] + cnt[i] + small(r[i], x);
    else
        return small(l[i], x);
}

int getrank(int x)
{
    return small(head, x) + 1;
}

void del(int x)
{
    if (getrank(x) != getrank(x + 1))
    {
        top = father = side = 0;
        del(head, 0, 0, x);
        rebuild();
    }
}

int index(int i, int x)
{
    if (siz[l[i]] >= x)
        return index(l[i], x);
    else if (siz[l[i]] + cnt[i] < x)
        return index(r[i], x - siz[l[i]] - cnt[i]);
    return key[i];
}

int index(int x)
{
    return index(head, x);
}

int pre(int x)
{
    int k = getrank(x);
    return index(k - 1);
}

int post(int x)
{
    int k = getrank(x + 1);
    return index(k);
}

int main()
{
    ios::sync_with_stdio(false);
    init();
    cin >> n;
    int op, x;
    int res;
    for (int 
    i = 0; i < n; i++)
    {
        cin >> op >> x;
        /*
        1.向M 中插入一个数 。
2. 从 M 中删除一个数g（若有多个相同的数，应只删除一个）。
3. 查询 M 中有多少个数比小，并且将得到的答案加一。
4. 查询如果将 M 从小到大排列后，排名位于第2位的数。
5.查询M 中心的前驱（前驱定义为小于 ，且最大的数）。
6.查询 M 中心的后继（后继定义为大于 2，且最小的数）。*/
        switch (op)
        {
        case 1:
            add(x);
            break;
        case 2:
            del(x);
            break;
        case 3:
            res = getrank(x);
            cout << res << endl;
            break;
        case 4:
            res = index(x);
            cout << res << endl;
            break;
        case 5:
            res = pre(x);
            cout << res << endl;
            break;
        case 6:
            res = post(x);
            cout << res << endl;
            break;
        }
    }
};