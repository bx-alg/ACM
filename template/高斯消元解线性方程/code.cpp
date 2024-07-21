void gauss(int n)
{
    for (int i = 1; i <= n; i++)
    {
        int max = i;
        for (int j = 1; j <= n; j++)
        {
            if (j < i && fabs(mat[j][j]) >= EPS)
            {
                continue;
            }
            if (fabs(mat[j][i]) > fabs(mat[max][i]))
            {
                max = j;
            }
        }
        swapRows(i, max, n);
        if (fabs(mat[i][i]) >= EPS)
        {
            double tmp = mat[i][i];
            for (int j = i; j <= n + 1; j++)
            {
                mat[i][j] /= tmp;
            }
            for (int j = 1; j <= n; j++)
            {
                if (i != j)
                {
                    double rate = mat[j][i] / mat[i][i];
                    for (int k = i; k <= n + 1; k++)
                    {
                        mat[j][k] -= mat[i][k] * rate;
                    }
                }
            }
        }
    }
}