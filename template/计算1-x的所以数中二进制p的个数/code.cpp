  ll countOneOfBit(int p,ll x)
    {
        ll len = 1ll << p;
        ll cycleLen = len * 2;
        ll cycleNum = x / cycleLen;
        ll cnt = cycleNum * len;
        ll rest = x % cycleLen;
        if(rest >= len)
            cnt += rest - len + 1;
        return cnt;
    }// 计算 1- x中,有多少个数在二进制p位上有1
