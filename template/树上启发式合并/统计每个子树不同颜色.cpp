//https://cses.fi/problemset/result/11604500/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

// 颜色映射
int main_color[MAXN];
int color_map_cnt = 0;

// 结果数组
int res_count[MAXN];

// 树的邻接表
vector<int> adj[MAXN];

// 颜色计数数组
unordered_map<int, int> cntcolor_arr;
int distinct = 0;

// 函数：添加颜色
inline void add_color(int col)
{
    cntcolor_arr[col]++;
    if (cntcolor_arr[col] == 1)
        distinct++;
}

int siz[MAXN];

// 函数：移除颜色
inline void remove_color(int col)
{
    cntcolor_arr[col]--;
    if (cntcolor_arr[col] == 0)
        distinct--;
}

int bigson[MAXN];

void dfs1(int u, int f)
{
    int big = -1;
    siz[u] = 1;
    for (auto &v : adj[u])
    {
        if (v != f)
        {
            dfs1(v, u);
            siz[u] += siz[v];
            if (big == -1 || siz[big] < siz[v])
            {
                big = v;
            }
        }
    }
    bigson[u] = big;
}

void remove(int u, int f)
{
    remove_color(main_color[u]);
    for (int v : adj[u])
    {
        if (v != f)
            remove(v, u);
    }
}

void add_tree(int u, int f)
{
    add_color(main_color[u]);
    for (int v : adj[u])
    {
        if (v != f)
            add_tree(v,u);
    }
}

// DFS函数，执行DSU on Trees
void dfs(int u, int parent, bool keep)
{

    // 先处理所有不是最大的子节点
    for (auto &v : adj[u])
    {
        if (v != parent && v != bigson[u])
        {
            dfs(v, u, false);
        }
    }

    // 处理最大的子节点，并保留其信息
    if (bigson[u] != -1)
    {
        dfs(bigson[u], u, true);
    }

    // 处理其他子节点，并合并其信息
    for (auto &v : adj[u])
    {
        if (v != parent && v != bigson[u])
        {
            add_tree(v,u);
        }
    }

    // 添加当前节点的颜色
    add_color(main_color[u]);

    // 记录当前节点子树中不同颜色的数量
    res_count[u] = distinct;

    if (!keep)
    {
        remove(u, parent);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    
    for (int i = 1; i <= n; i++)
    {
        cin >> main_color[i];
    }
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    dfs1(1, 0);

    dfs(1, -1, true);


    for (int i = 1; i <= n; i++)
    {
        cout << res_count[i] << " ";
    }

    return 0;
}