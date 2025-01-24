void getInv(int N)
{
    inv[1] = 1;
    for(int i=2; i<N; ++i)
        inv[i] = mod - inv[mod % i] * (mod / i) % mod;
}
