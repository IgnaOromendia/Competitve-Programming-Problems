#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

// judge: https://www.spoj.com/submit/PRIME1/

long long n,m;
vector<long long> primes;

// O(√n)
bool isPrime(long long x) {
    if (x == 1) return false;
    int limit = sqrt(x);
    for (int i = 2; i <= limit; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

// O((n - m) * √n )
void generate_primes() {
    for(long long i = m; i <= n; i++) {
        if (isPrime(i)) primes.push_back(i);
    }
}

int main() {
    int c; cin >> c;
    while(c--) {
        cin >> m >> n;
        generate_primes();
        for(long long p: primes) cout << p << " ";
        cout << endl;
        primes.clear();
    }
}