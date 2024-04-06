
    ll getInv(ll x)
    {
        int M = mod;
        ll s = 1;
        for (; x > 1; x = M % x)
            s = s * (M - M / x) % M;
        return s;
    }
