#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll maxn = 100005;

struct STree{

    ll data[maxn<<2];
    ll lazy[maxn<<2];
    
    void modify(ll rt,ll l,ll r,ll val) {
        data[rt] += val*(r-l+1);
        lazy[rt] += val;
    }
    
    void pushdown(ll rt,ll l,ll r){
        if (lazy[rt]){
            ll mid = (l+r)/2;
            modify(rt*2,l,mid,lazy[rt]);
            modify(rt*2+1,mid+1,r,lazy[rt]);
            lazy[rt] = 0;
        }
    }

    void update(ll rt,ll l,ll r,ll L,ll R,ll val){
        if (L<=l&r<=R){
            modify(rt,l,r,val);
        }else{
            ll mid = (l+r)/2;
            pushdown(rt,l,r);
            if (L<=mid) update(rt*2,l,mid,L,R,val);
            if (mid<R) update(rt*2+1,mid+1,r,L,R,val);
            data[rt] = data[rt*2] + data[rt*2+1];            
        }
    }

    ll query(ll rt,ll l,ll r,ll L,ll R){
        if (L<=l&&r<=R){
            return data[rt];
        }
        pushdown(rt,l,r);
        ll mid = (l+r)/2;
        ll ret =  0;
        if (L<=mid) ret += query(rt*2,l,mid,L,R);
        if (mid<R) ret += query(rt*2+1,mid+1,r,L,R);
        return ret;
    }
        
};

STree st;


ll fa[maxn],dep[maxn],siz[maxn],top[maxn],w[maxn];
vector<ll> son[maxn];
ll totw;

ll dfs1(ll x,ll f,ll d){
    siz[x] = 1;
    fa[x]=f;
    dep[x]=d;
    for (ll j=0;j<son[x].size();j++){
        if (son[x][j]!=f){
            siz[x] +=  dfs1(son[x][j],x,d+1);
        }
    }
    return siz[x];
}


void dfs2(ll x,ll tp){
    w[x] = ++totw;
    top[x] = tp;
    if (son[x].size()==0) return;
    ll ws = 0;
    for (ll j=0;j<son[x].size();j++)
        if (siz[son[x][j]]>siz[son[x][ws]]) 
            ws = j;
    dfs2(son[x][ws],tp);
    for (ll j=0;j<son[x].size();j++)
        if (j!=ws) dfs2(son[x][j],son[x][j]);
}

void update(ll x,ll y,ll val){

    while( top[x] != top[y] ){
        if (dep[top[x]] < dep[top[y]]) swap(x,y);
        st.update(1,1,totw,w[top[x]],w[x],val);
        x = fa[top[x]];
    }
    if (x!=y) {
        if (dep[x]<dep[y]) swap(x,y);
        st.update(1,1,totw,w[y]+1,w[x],val);
    }
}

ll query(ll x,ll y) {
    ll ret = 0;
    while( top[x] != top[y] ){
        if (dep[top[x]] < dep[top[y]]) swap(x,y);
        ret += st.query(1,1,totw,w[top[x]],w[x]);
        x = fa[top[x]];
    }
    if (x!=y) {
        if (dep[x]<dep[y]) swap(x,y);
        ret += st.query(1,1,totw,w[y]+1,w[x]);
    }
    return ret;
}



int main(){

    ll n;
    scanf("%lld",&n);
    for (ll i=0;i<n;i++){
        ll k,s;
        scanf("%lld",&k);
        for (ll j=0;j<k;j++){
            scanf("%lld",&s);
            son[i].push_back(s);
        }
    }
    dfs1(0,0,1);
    dfs2(0,0);
    
    ll q;
    scanf("%lld",&q);
    for (ll i=0;i<q;i++){
        ll op,u,v,w;
        scanf("%lld",&op);
        if (op==0){
            scanf("%lld%lld",&u,&w);
            update(u,0,w);
        }else {
            scanf("%lld",&v);
            printf("%ld\n",query(0,v));
        }
    }


    return 0;
}
