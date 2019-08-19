---
title: TreeArray
chapter: DataStructure
---

typedef long long ll;
const ll maxn = 200005;

struct TreeArray{
    ll a[maxn];
    ll n=maxn;
    void init(ll nn){
        n=nn;
        memset(a,0, sizeof(a));
    }
    inline ll lowbit(ll x){
        return -x&x;
    }
    void add(ll x,ll v){
        for (;x<=n;x+=lowbit(x)) a[x]+=v;
    }
    ll query(ll x){
        ll ret = 0;
        for (;x;x-=lowbit(x))  ret+=a[x];
        return ret;
    }
};
