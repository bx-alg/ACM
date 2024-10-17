//测试地址:https://www.luogu.com.cn/record/182689497


#include<iostream>
#include<functional>
#include<vector>
using namespace std;

vector<vector<int>>V;
vector<vector<pair<int,int>>>query;
vector<int>vis;
vector<int>ans;

vector<int>father;
int find( int i)
{
    if(father[i] != i)
        father[i] = find(father[i]);
    return father[i];
}

void unite(int a,int b)
{
    int fa = find(a);
    int fb = find(b);
    if(fa != fb)
    {
        father[fb] = fa;
    }
    
}

int main()
{
    int n,m,root;
    cin >> n >>m >> root;
    n++;
    V = vector<vector<int>>(n);
    int u,v;
    for(int i = 2; i < n; i++)
    {
        cin >> u >> v;
        V[u].push_back(v);
        V[v].push_back(u);
    }
    query = vector<vector<pair<int,int>>>(n);
    for(int i = 0; i < m; i++)
    {
        cin >> u >> v;
        query[u].push_back({v,i});
        query[v].push_back({u,i});
    }
    
    vis.resize(n);
    father.resize(n);
    for(int i = 0; i < n; i++)
        father[i] = i;
    ans.resize(m);
    function<void(int)>tarjan = [&](int u)
    {
        vis[u] = 1;
        for(int v : V[u])
        {
            if(!vis[v])
            {
                tarjan(v);
                unite(u,v);
            }
        }
        for(auto&[v,i]:query[u])
        {
            if(vis[v])
            {
                ans[i] = find(v);
            }
        }
    };
    tarjan(root);
    for(int i = 0; i < m; i++)
    {
        printf("%d\n",ans[i]);
    }
}

