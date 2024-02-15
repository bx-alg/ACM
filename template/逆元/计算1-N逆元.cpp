for(inv[1]=1, i=2; i<N; ++i)
    inv[i] = (M - M/i) * inv[M % i] % M