
vector<int> getnext(string &s)
{
    int n = s.size();
    vector<int> nx(n + 1);
    nx[0] = -1;
    if (n == 0)
        return nx;
    nx[1] = 0;
    int i = 2,j = 0;
    while(i <= n)
    {
        if(s[i-1] == s[j])
            nx[i++] = ++j;
        else if(j == 0)i++;
        else j = nx[j];
    }
    return nx;
}

vector<int> kmp(string &s, string &p)
{
    vector<int> nx = getnext(p);
    int n = s.size();
    vector<int> idx;
    int i = 0, j = 0;
    int m = p.size();
    while (i < n)
    {
        if (s[i] == p[j])
        {
            i++, j++;
            if (j == m)
                idx.push_back(i - m), j = nx[j];
        }
        else if (j == 0)
            i++;
        else
            j = nx[j];
    }
    return idx;
}
