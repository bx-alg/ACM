  vector<int> getE(string &a, string &b)
    {
        int n = a.size();
        int m = b.size();
        vector<int> z = getZ(b);
        vector<int> e(n);
        for (int i = 0, c = 0, r = 0, len; i < n; i++)
        {
            len = r > i ? min(r - i, z[i - c]) : 0;
            while (i + len < n && len < m && a[i + len] == b[len])
            {
                len++;
            }
            if (i + len > r)
            {
                r = i + len;
                c = i;
            }
            e[i] = len;
        }
        return e;
    }