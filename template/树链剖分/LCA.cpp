int getlca(int a,int b)
{
    while(top[a] != top[b])
    {
        if(dep[top[a]] < dep[top[b]])swap(a,b);
        a = fa[top[a]];
    }
    return dep[a] < dep[b] ? a : b;
}