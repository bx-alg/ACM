 vector<int> getZ(string &s)
    {
        int n = s.size();
        vector<int> z(n);
        z[0] = n;
        for (int i = 1, r = 0, c = 0, len; i < n; i++)
        {
            len = r > i ? min(z[i - c], r - i) : 0;
            while (i + len < n && s[i + len] == s[len])
                len++;
            z[i] = len;
            if (i + len > r)
            {
                r = i + len;
                c = i;
            }
        }
        return z;
    }