#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;

// 题目链接:https://www.acwing.com/problem/content/4660/

const int N = 1e5 + 10;
int n,m;
int a[N];
int s;
int pos[N];

struct Q
{
  int l,r,k,id;  
}qs[N];

int res[N];
int times[N];
int cnt[N];

void add(int i)
{
    cnt[times[a[i]]]--;
    times[a[i]]++;
    cnt[times[a[i]]]++;
}

void sub(int i)
{
    cnt[times[a[i]]]--;
    times[a[i]]--;
    cnt[times[a[i]]]++;
}




int main()
{
    cin >> n;
    s = sqrt(n);
    memset(times,0,sizeof times);
    memset(cnt,0,sizeof cnt);
    for(int i = 1; i <= n; i++)
    {
        cin >> a[i];
        pos[i] = i / s;
    }
    cin >> m;
    int l,r,k;
    for(int i = 0; i < m; i++)
    {
        cin >> l >> r >> k;
        qs[i] = {l,r,k,i};
    }
    sort(qs,qs + m,[](Q&x,Q&y)
    {
        return pos[x.l] != pos[y.l] ? pos[x.l] < pos[y.l] : x.r < y.r;
    });
    
    l = 1,r = 0;
    
    for(int i = 0; i < m; i++)
    {
       while(qs[i].l < l)add(--l);
       while(qs[i].r > r)add(++r);
       while(qs[i].l > l)sub(l++);
       while(qs[i].r < r)sub(r--);
       res[qs[i].id] = cnt[qs[i].k];
    }
    for(int i = 0; i < m; i++)
    {
        cout << res[i] << '\n';
    }
    return 0;
    
}    
