  public long getC(int n, int m)
    {
        long ans = 1;
        for (int i = 0; i < m; i++)
        {
            ans *= n - i;
            ans /= i + 1;
        }
        return ans;
    }