
const int maxn = 1000010;
ll prime[maxn], notPrime[maxn], priCnt=0;

void getPrime() {
    for (int i = 2; i < maxn; i++) {
        if (!notPrime[i])
            prime[priCnt++] = i;
        for (int j = 0; j < priCnt && i * prime[j] < maxn; j++) {
            notPrime[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}
