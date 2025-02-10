

// 生成本源勾股数组
vector<tuple<int, int, int>> generatePrimitiveTriples(int limit)
{
    vector<tuple<int, int, int>> triples;

    for (int m = 2; m * m <= limit; ++m)
    {
        for (int n = 1; n < m; ++n)
        {
            // 检查 m 和 n 是否互质，且一奇一偶
            if (gcd(m, n) == 1 && (m % 2 != n % 2))
            {
                int a = m * m - n * n;
                int b = 2 * m * n;
                int c = m * m + n * n;

                // 确保 c 不超过限制
                if (c <= limit)
                {
                    // 确保 a < b
                    if (a > b)
                        swap(a, b);
                    triples.push_back(make_tuple(a, b, c));
                }
                else
                    break;
            }
        }
    }
    return triples;
}
