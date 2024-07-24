void gauss(int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (j < i && mat[j][j] == 1)
            {
                continue;
            }
            if (mat[j][i] == 1)
            {
                swap(mat[i], mat[j]);
                break;
            }
        }
        if (mat[i][i] == 1)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i != j && mat[j][i] == 1)
                {
                    for (int k = i; k <= n + 1; k++)
                    {
                        mat[j][k] ^= mat[i][k];
                    }
                }
            }
        }
    }
}