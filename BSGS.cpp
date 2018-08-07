
// BSGS，就是平常所说的大步小步算法，  求出形如同余方程Ax≡B(mod C)(C是质数)的解。
// 我们可以使用分块来优化暴力枚举，对于Ax≡B(mod C)，我们可以令n=sqrt(C)，x=i∗n+j，
// 那么该式子就可以写成A^(i∗n)∗A^j ≡ B(mod C)，于是我们可以将A^j进行预处理，
// 表示达到这个值的指数项为多少，存到一个哈希表或者map里，
// 之后我们只要枚举A^(i∗n)就行了，大致复杂度是O(sqrt(n)*log(n))。

typedef long long ll;

ll qpow(ll a,ll x,ll mod) {
    ll ret=1;
    while(x) {
        if (x&1) ret=ret*a%mod;
        a=a*a%mod;
        x>>=1;
    }
    return ret;
}

struct BSGS
{
    // A^x = B (mod C)
    map<ll,ll>hs;
    ll n,a,c;
    BSGS(ll _a,ll _c) {
        a=_a;
        c=_c;
        n = ceil(sqrt(c));
        ll x=1;
        hs[x]=0;
        for (ll i=1; i<=n; i++) {
            x=x*a%c;
            if (!hs.count(x))
                hs[x]=i;
        }
    }

    ll solv(ll b) {
        for (int i=0; i<=n; i++) {
            ll u = qpow(a,i*n,c);
            ll v = b*qpow(u,c-2,c)%c;
            if (hs.count(v))
                return hs[v]+i*n;
        }
        return -1;
    }
};

int main() {

//   freopen("in.txt","r",stdin);

    ll g,p;
    scanf("%lld%lld",&g,&p);
    BSGS bsgs(g,p);
    int t;
    scanf("%d",&t);
    while(t--) {
        ll a,b;
        scanf("%lld%lld",&a,&b);
        ll k = bsgs.solv(a);
        ll ans = qpow(b,k,p);
        printf("%lld\n",ans);
    }

    return 0;
}
