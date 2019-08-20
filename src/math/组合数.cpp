---
index: 10
title: combination
---
st
---
///////////////////

typedef long long ll;
const int maxn = 1000010;
const ll mod = 1e9+7;
ll fac[maxn]; 
ll inv[maxn]; 

ll qpow(ll a,ll x){
    ll ret=1;
    while (x){
        if (x&1)
            ret = ret*a%mod;
        a=a*a%mod;
        x>>=1;
    }
    return ret;
}

void init(){
    fac[0]=1;
    for (int i=1;i<maxn;i++)
        fac[i]=fac[i-1]*i%mod;
    inv[maxn-1]=qpow(fac[maxn-1],mod-2);
    for (int i=maxn-2;i>=0;i--)
        inv[i]=inv[i+1]*(i+1)%mod;
}

void init() {
    fac[0]=1;
    for(int i = 1; i < mod; ++i) fac[i]=fac[i-1]*i%mod;
    inv[1]=1;
    for(int i = 2; i < mod; ++i) inv[i]=inv[mod%i]*(mod-mod/i)%mod;
    inv[0]=1;
    for(int i = 2; i < mod; ++i) inv[i]=inv[i]*inv[i-1]%mod;
}

ll c(ll n, ll m) {
    if (m > n) return 0;
    return fac[n] * inv[n - m] % mod * inv[m] % mod;
}

ll lucas(ll n, ll m) {
    if (m > n) return 0;
    if (m == 0) return 1;
    return c(n % mod, m % mod) * lucas(n / mod, m / mod) % mod;
}

///////////////////

const int N = 1005;
ll f[N][N];
void init(int n)
{
    f[0][0] = 1;
    for(int i = 1;i <= n;i++){
        f[i][0] = 1;
        for(int j = 1;j <= i;j++)
            f[i][j] = f[i-1][j] + f[i-1][j-1];
    }
}

///////////////////

ll n = 6;
ll cc = 1;
for (int i = 0; i <= n; i++) {
    cout << cc << endl;
    cc = cc * (n - i) * qpow(i + 1, mod - 2) % mod;
}

///////////////////
