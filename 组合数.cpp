


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

ll init(){
    fac[0]=1;
    for (int i=1;i<maxn;i++)
        fac[i]=fac[i-1]*i%mod;
    inv[maxn-1]=qpow(fac[maxn-1],mod-2);
    for (int i=maxn-2;i>=0;i--)
        inv[i]=inv[i+1]*(i+1)%mod;
    return 0;
}

ll c(ll n,ll m){
    return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
