#include<iostream>
using namespace std;
using ll = long long;

int n;
ll m;
const int N = 1e5 + 10;
int a[N];

ll cnt[N];
int res[N];

ll sum[N * 4];
int L,R;


void pu(int i)
{
    sum[i] = sum[i << 1] + sum[i << 1 | 1];
}

int querySum(int i,int l,int r)
{
    if(L > R)return 0;
    if(L <= l && R >= r)
        return sum[i];
    int mid = (r - l) / 2 + l;
    int res = 0;
    if(L <= mid)
        res += querySum(i << 1,l,mid);
    if(R > mid)
        res += querySum(i << 1 | 1,mid + 1,r);
    return res;
}

int queryRank(int i,int l,int r,int rank)
{
    if(l == r)
        return r;
    int mid = (r - l) / 2 + l;
    if(sum[i << 1] >= rank)
        return queryRank(i << 1,l,mid,rank);
    return queryRank(i << 1 | 1,mid + 1,r,rank - sum[i << 1]);
}

void change(int i,int l,int r)
{
    if(L <= l && R >= r)
    {
        sum[i] = 0;
        return;
    }
    int mid = (r - l) / 2 + l;
    if(L <= mid)
        change(i << 1,l,mid);
    if(R > mid)
        change(i << 1 | 1,mid + 1,r);
    pu(i);
}


void build(int i,int l,int r )
{
    if(l == r)
    {
        sum[i] = 1;
        return;
    }
    int mid = (r - l) / 2 + l;
    build(i << 1,l,mid);
    build(i << 1 | 1,mid + 1,r);
    pu(i);
}


int main()
{
    cin >> n >> m;
    for(int i = n -1; i >= 0; i--)
    {
        cin >> a[i];
    }
    build(1,1,n);
    for(int i = n - 1; i >= 0; i--)
    {
        L = 1,R = a[i] - 1;
        cnt[i] = querySum(1,1,n);
        L = a[i],R = a[i];
        change(1,1,n);
    }
    cnt[0] += m;
    for(int i = 0; i < n -1; i++)
    {
        cnt[i + 1] += cnt[i] / (i + 1);
        cnt[i] = cnt[i] % (i + 1);
    }
    
    build(1,1,n);

    for(int i = n - 1; i >= 0; i--)
    {
        
            res[i] = queryRank(1,1,n,cnt[i] + 1);
            L = res[i],R = res[i];
            change(1,1,n);
        
    }
    for(int i = n - 1;i >= 0; i--)
    {
        cout << res[i] << " ";
    }

    return 0;

}
