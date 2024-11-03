#include"iostream"
#include"climits"
#include "queue"

using namespace std;


const int maxn = 2002;
const int maxm = 7000;
int head[maxn];
int ne[maxm];
int to[maxm];
int weight[maxm];
int cnt;
int dis[maxn];
int co[maxn];
bool vis[maxn];
int l,r;

int n;
int m;
int tests;

void initial()
{
    cnt = 0;
    l = r = 0;
    fill(head,head + n + 1,-1 );
    fill(dis,dis + n + 1,INT_MAX);
    fill(vis,vis + n + 1,false);
    fill(co,co + n + 1,0);
}

void addEdge(int u,int v,int w)
{
    ne[cnt] = head[u];
    head[u] = cnt;
    weight[cnt] = w;
    to[cnt] = v;
    cnt++;
}


bool f()
{
    dis[1] = 0;
    co[1] = 1;
    vis[1] = true;
    queue<int>q;
    q.push(1);
    while(!q.empty())
    {
        int pop = q.front();
        q.pop();
        vis[pop] = false;
        for(int ei = head[pop]; ei != -1 ; ei = ne[ei])
        {
            int v = to[ei];
            if(dis[v] > dis[pop] + weight[ei])
            {
                dis[v] = dis[pop] + weight[ei];
                if(!vis[v])
                {
                    if(co[v]++ == n)
                        return true;
                   q.push(v);
                    vis[v] = true;
                }
            }
        }
    }
    return false;
}



int main()
{
    cin >> tests;
    for(int i = 0; i < tests; i++)
    {
        cin >> n >> m;
        initial();
        for(int j = 0; j < m; j++)
        {
            int u = 0;
            int v = 0;
            int w = 0;
            cin >> u >> v >> w;
            addEdge(u,v,w);
            if(w >= 0)
            {
                addEdge(v,u,w);
            }
        }
        cout << (f() ? "YES" : "NO") << endl;
    }

}
