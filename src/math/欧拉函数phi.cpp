---
index: 6
title: eulur function
---
st
---
// 单个
ll Euler(ll n) {
    ll ret=n;
    for(ll i=2;i<=sqrt(n);i++)
    if(n%i==0)
    {
        ret=ret/i*(i-1);
        while(n%i==0)
          n/=i;
    }
    if(n>1)
          ret=ret/n*(n-1);
    return ret;
}

//所有
const ll  maxn = 1000005;
ll euler[maxn];
void init() {
    memset(euler,0,sizeof(euler));
    euler[1]=1;
    for(ll i=2; i<maxn; i++)
        if(!euler[i])
            for(ll j=i; j<maxn; j+=i) {
                if(!euler[j])
                    euler[j]=j;
                euler[j]=euler[j]/i*(i-1);
            }
}
