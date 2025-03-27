

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int MAXN = 2000001;

int root = 0;
int cnt = 0;
char key[MAXN];
int ls[MAXN];
int rs[MAXN];
int siz[MAXN];
double pri[MAXN];
char ans[MAXN];
int ansi;

void up(int i)
{
    siz[i] = siz[ls[i]] + siz[rs[i]] + 1;
}

void split(int l, int r, int i, int rank)
{

    if (i == 0)
    {
        rs[l] = ls[r] = 0;
        return;
    }
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
        inorder(ls[i]);
        ans[++ansi] = key[i];
        inorder(rs[i]);
    }
}

int newNode(char c)
{
    int nid = ++cnt;
    ls[nid] = rs[nid] = 0;
    siz[nid] = 1;
    key[nid] = c;
    pri[nid] = (double)rand() / RAND_MAX;
    return nid;
}

int main()
{
    srand(time(0));
    int pos = 0, len, l, m, lm, r;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        char op[10];
        cin >> op;
        if (op[0] == 'P')
        {
            pos--;
        }
        else if (op[0] == 'N')
        {
            pos++;
        }
        else if (op[0] == 'M')
        {
            cin >> pos;
        }
        else if (op[0] == 'I')
        {
            cin >> len;
            split(0, 0, root, pos);
            int l, r;
            l = rs[0], r = ls[0];
            for (int j = 1; j <= len; j++)
            {
                char ch = getchar();
                while (ch < 32 || ch > 126)
                {
                    ch = getchar();
                }
                int nid = newNode(ch);
                l = merge(l, nid);
            }
            root = merge(l, r);
        }
        else if (op[0] == 'D')
        {
            cin >> len;
            split(0, 0, root, pos + len);
            int r = ls[0];
            split(0, 0, rs[0], pos);
            root = merge(rs[0], r);
        }
        else
        {
            cin >> len;
            split(0, 0, root, pos + len);
            int r = ls[0];
            split(0, 0, rs[0], pos);
            ansi = 0;
            inorder(ls[0]);
            int l = merge(rs[0], ls[0]);
            root = merge(l, r);
            for (int i = 1; i <= ansi; i++)
                cout << ans[i];
            cout << "\n";
        }
    }
    return 0;
}