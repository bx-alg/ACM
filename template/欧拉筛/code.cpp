#include <iostream>
#include <vector>
using namespace std;

const int N = 1e6 + 10;
bool is_prime[N];
vector<int> primes;

void eulerSieve(int n)
{
    fill(is_prime, is_prime + n + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i <= n; i++)
    {
        if (is_prime[i])
        {
            primes.push_back(i);
        }
        for (int j = 0; j < primes.size() && i * primes[j] <= n; j++)
        {
            is_prime[i * primes[j]] = false;
            if (i % primes[j] == 0)
            {
                break;
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;
    eulerSieve(n);
    for (int prime : primes)
    {
        cout << prime << " ";
    }
    return 0;
}
