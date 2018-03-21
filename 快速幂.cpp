

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