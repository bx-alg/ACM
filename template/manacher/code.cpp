  vector<int> manacher(string &ss)
    {
        int n = ss.size();
        vector<int> p(n);
        for (int i = 0, c = 0, r = 0, len; i <= n / 2; i++)
        {
            len = r > i ?  min(p[2 * c - i],r - i) : 1;
            while(i - len >= 0 && i + len < n && ss[i - len] == ss[i + len])
                len++;
            p[i] = len;
            if(i + len > r)
            {
                r = i + len; c = i;
            }
        }
        return p;
    }