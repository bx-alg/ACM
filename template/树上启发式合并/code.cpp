
//链接:https://oi-wiki.org/graph/hld/
// https://www.acwing.com/problem/content/description/5001/

时间复杂度:n*log2(n)



#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int n;
const int N = 2e5 + 10;


vector<vector<int>>g(N);
vector<int>color(N);

int res = 0;

int siz[N];
int bigson[N];

void dfs(int u)
{
    siz[u] = 1;
    int w = INT_MIN;
    for(int v: g[u])
    {
        dfs(v);
        siz[u] += siz[v];
        if(w < siz[v])
        {
            w = siz[v];
            bigson[u] = v;
        }
    }
}

int cnt[N];
int c,m;

void count(int u,int val)
{
    int i = color[u];
    if(cnt[i] == 0)
        c++;
    cnt[i] += val;
    m = max(m,cnt[i]);
    for(int v: g[u])
        count(v,val);
}




void dfs2(int u,bool keep)
{
    for(int v: g[u])
    {
        if(bigson[u] != v)
            dfs2(v,false);
    }
    if(bigson[u])
        dfs2(bigson[u],1);
   for(int v: g[u])
   {
        if(v != bigson[u])
            count(v,1);
   }
   if(++cnt[color[u]] == 1)c++;
    m = max(m,cnt[color[u]]);
    if(m * c == siz[u])
        res++;
    if(!keep)
    {
        count(u,-1);
        c = 0;
        m = 0;
    }
}






int main()
{
    memset(cnt,0,sizeof cnt);
    memset(bigson,0,sizeof bigson);
    c = 0;
    cin >> n;
    
    for(int i = 1,c,f; i <= n; i++)
    {
            cin >> c >> f;
            color[i] = c;
            g[f].push_back(i);
    }
    dfs(1);
    dfs2(1,1);
    cout << res;
    return 0;
    
}
