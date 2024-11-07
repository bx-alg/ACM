#include<iostream>
#include<climits>
#include<vector>
using namespace std;
int n,k;
static const  int V = 5501;
static const int H = 502;
static const int N = 1e4 + 1;
int tree[V][H];
int arr[N];
int ori[V][H];

int getmax(int x1,int y1,int x2,int y2)
{
    int res = INT_MIN;
    for(int i = x; i >= 1; i ^= i & -i)
    {
        for(int j = y; j >= 1; j ^= j & -j)
        {
            res = max(res,tree[i][j]);
        }
    }
    return res;
}

void update(int x,int y,int val)
{
    ori[x][y] = val;
    for(int i = x; i < V; i += i & -i)
    {
        for(int j = y; j < H; j += j & -j)
        {
            tree[i][j] = max(val,tree[i][j]);
        }
    }
}



int main()
{
    ios::sync_with_stdio(false);
    cin >> n >> k;
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    int v,dp;
    int res = INT_MIN;
    for(int i = 0; i < n; i++)
    {
        for(int j = k; j >= 0; j--)
        {
            v = arr[i] + j;
            dp = getmax(v,j + 1) + 1;
            update(v,j + 1,dp);
            res = max(res,dp);
        }
    }
    cout << res;
}
