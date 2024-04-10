#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int MAXN = 500001;
const long long LOWEST = LLONG_MIN;

int arr[MAXN];
long long sum[MAXN << 2];
long long Max[MAXN << 2];
int cnt[MAXN << 2];
long long sem[MAXN << 2];
long long maxAdd[MAXN << 2];
long long otherAdd[MAXN << 2];
long long maxHistory[MAXN << 2];
long long maxAddTop[MAXN << 2];
long long otherAddTop[MAXN << 2];

void up(int i)
{
    int l = i << 1;
    int r = i << 1 | 1;
    maxHistory[i] = max(maxHistory[l], maxHistory[r]);
    sum[i] = sum[l] + sum[r];
    Max[i] = max(Max[l], Max[r]);
    if (Max[l] > Max[r])
    {
        cnt[i] = cnt[l];
        sem[i] = max(sem[l], Max[r]);
    } else if (Max[l] < Max[r])
    {
        cnt[i] = cnt[r];
        sem[i] = max(Max[l], sem[r]);
    } else
    {
        cnt[i] = cnt[l] + cnt[r];
        sem[i] = max(sem[l], sem[r]);
    }
}

void lazy(int i, int n, long long maxAddv, long long otherAddv, long long maxUpv, long long otherUpv)
{
    maxHistory[i] = max(maxHistory[i], Max[i] + maxUpv);
    maxAddTop[i] = max(maxAddTop[i], maxAdd[i] + maxUpv);
    otherAddTop[i] = max(otherAddTop[i], otherAdd[i] + otherUpv);
    sum[i] += maxAddv * cnt[i] + otherAddv * (n - cnt[i]);
    Max[i] += maxAddv;
    sem[i] += (sem[i] == LOWEST ? 0 : otherAddv);
    maxAdd[i] += maxAddv;
    otherAdd[i] += otherAddv;
}

void down(int i, int ln, int rn)
{
    int l = i << 1;
    int r = i << 1 | 1;
    long long tmp = max(Max[l], Max[r]);
    if (Max[l] == tmp)
    {
        lazy(l, ln, maxAdd[i], otherAdd[i], maxAddTop[i], otherAddTop[i]);
    } else
    {
        lazy(l, ln, otherAdd[i], otherAdd[i], otherAddTop[i], otherAddTop[i]);
    }
    if (Max[r] == tmp)
    {
        lazy(r, rn, maxAdd[i], otherAdd[i], maxAddTop[i], otherAddTop[i]);
    } else
    {
        lazy(r, rn, otherAdd[i], otherAdd[i], otherAddTop[i], otherAddTop[i]);
    }
    maxAdd[i] = otherAdd[i] = maxAddTop[i] = otherAddTop[i] = 0;
}

void build(int l, int r, int i)
{
    if (l == r)
    {
        sum[i] = Max[i] = maxHistory[i] = arr[l];
        sem[i] = LOWEST;
        cnt[i] = 1;
    } else
    {
        int mid = (l + r) >> 1;
        build(l, mid, i << 1);
        build(mid + 1, r, i << 1 | 1);
        up(i);
    }
    maxAdd[i] = otherAdd[i] = maxAddTop[i] = otherAddTop[i] = 0;
}

void add(int jobl, int jobr, long long jobv, int l, int r, int i)
{
    if (jobl <= l && r <= jobr)
    {
        lazy(i, r - l + 1, jobv, jobv, jobv, jobv);
    } else
    {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid)
        {
            add(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid)
        {
            add(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

void setMin(int jobl, int jobr, long long jobv, int l, int r, int i)
{
    if (jobv >= Max[i])
    {
        return;
    }
    if (jobl <= l && r <= jobr && sem[i] <= jobv)
    {
        lazy(i, r - l + 1, jobv - Max[i], 0, 0, 0);
    } else
    {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        if (jobl <= mid)
        {
            setMin(jobl, jobr, jobv, l, mid, i << 1);
        }
        if (jobr > mid)
        {
            setMin(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
        }
        up(i);
    }
}

long long querySum(int jobl, int jobr, int l, int r, int i)
{
    if (jobl <= l && r <= jobr)
    {
        return sum[i];
    } else
    {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        long long ans = 0;
        if (jobl <= mid)
        {
            ans += querySum(jobl, jobr, l, mid, i << 1);
        }
        if (jobr > mid)
        {
            ans += querySum(jobl, jobr, mid + 1, r, i << 1 | 1);
        }
        return ans;
    }
}

long long queryMax(int jobl, int jobr, int l, int r, int i)
{
    if (jobl <= l && r <= jobr)
    {
        return Max[i];
    } else
    {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        long long ans = LLONG_MIN;
        if (jobl <= mid)
        {
            ans = max(ans, queryMax(jobl, jobr, l, mid, i << 1));
        }
        if (jobr > mid)
        {
            ans = max(ans, queryMax(jobl, jobr, mid + 1, r, i << 1 | 1));
        }
        return ans;
    }
}

long long queryHistoryMax(int jobl, int jobr, int l, int r, int i)
{
    if (jobl <= l && r <= jobr)
    {
        return maxHistory[i];
    } else
    {
        int mid = (l + r) >> 1;
        down(i, mid - l + 1, r - mid);
        long long ans = LLONG_MIN;
        if (jobl <= mid)
        {
            ans = max(ans, queryHistoryMax(jobl, jobr, l, mid, i << 1));
        }
        if (jobr > mid)
        {
            ans = max(ans, queryHistoryMax(jobl, jobr, mid + 1, r, i << 1 | 1));
        }
        return ans;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
    {
        cin >> arr[i];
    }
    build(1, n, 1);
    long long jobv;
    for (int i = 1, op, jobl, jobr; i <= m; ++i)
    {
        cin >> op >> jobl >> jobr;
        if (op == 1)
        {
            cin >> jobv;
            add(jobl, jobr, jobv, 1, n, 1);
        } else if (op == 2)
        {
            cin >> jobv;
            setMin(jobl, jobr, jobv, 1, n, 1);
        } else if (op == 3)
        {
            cout << querySum(jobl, jobr, 1, n, 1) << "\n";
        } else if (op == 4)
        {
            cout << queryMax(jobl, jobr, 1, n, 1) << "\n";
        } else
        {
            cout << queryHistoryMax(jobl, jobr, 1, n, 1) << "\n";
        }
    }
    return 0;
}
