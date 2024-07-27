void gauss(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            if (j < i && mat[j][j] != 0)
            {
                continue;
            }
            if (mat[j][i] != 0)
            {
                swap_rows(i, j);
                break;
            }
        }
        if (mat[i][i] != 0)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (i != j && mat[j][i] != 0)
                {
                    int gcd_val = gcd(mat[j][i], mat[i][i]);
                    int a = mat[i][i] / gcd_val;
                    int b = mat[j][i] / gcd_val;
                    if (j < i && mat[j][j] != 0)
                    {
                        for (int k = j; k < i; ++k)
                        {
                            mat[j][k] = (mat[j][k] * a) % MOD;
                        }
                    }
                    for (int k = i; k <= n + 1; ++k)
                    {
                        mat[j][k] = ((mat[j][k] * a - mat[i][k] * b) % MOD + MOD) % MOD;
                    }
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        if (mat[i][i] != 0)
        {
            bool flag = false;
            for (int j = i + 1; j <= n; ++j)
            {
                if (mat[i][j] != 0)
                {
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                mat[i][n + 1] = (mat[i][n + 1] * inv[mat[i][i]]) % MOD;
                mat[i][i] = 1;
            }
        }
    }
}