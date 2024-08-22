#include <iostream>

using namespace std;

long long d, x, y, px, py;

void exgcd(long long a, long long b)
{
    if (b == 0)
    {
        d = a;
        x = 1;
        y = 0;
    }
    else
    {
        exgcd(b, a % b);
        px = x;
        py = y;
        x = py;
        y = px - py * (a / b);
    }
}

int main()
{
    long long a, b;
    cin >> a >> b;
    exgcd(a, b);
    cout << (x % b + b) % b;
    return 0;
}