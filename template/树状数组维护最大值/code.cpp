int arr[N+ 2];
int tree[N + 2];

int lowbit(int i)
{
    return i &-i;
}

void update(int i,int val)
{
    arr[i] = max(arr[i],val);
    while(i <= N)
    {
        tree[i] = max(tree[i],val);
        i += lowbit(i);
    }
}

int query(int l,int r)
{
    int res = 0;
    while(l <= r)
    {
        if(r - lowbit(r) > l)
        {
            res = max(res,tree[r]);
            r ^= lowbit(r);
        }else res = max(res,arr[r--]);
    }
    return res;
}
