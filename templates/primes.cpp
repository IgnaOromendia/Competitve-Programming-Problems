using namespace std;

#define forn(i,from,to) for (int i = from; i < to; i++)

const int MAXN = 1e8;

void sieve(int prime[]) {
    forn(i, 0, MAXN) prime[i] = 1; 
    prime[0] = prime[1] = 0;      

    for (int i = 2; i * i < MAXN; i++) 
        if (prime[i]) 
            for (int j = i * i; j < MAXN; j += i) 
                prime[j] = 0; 
}

