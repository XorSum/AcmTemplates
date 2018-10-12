// 有封装
#include<iostream>
#include <cstdio>
#include <set>
#include <queue>
#include <cstring>
#include <cmath>
#include <algorithm>
typedef long long ll;
using  namespace std;
const int maxn=1000005;
ll num[maxn];
ll pen[maxn];
struct node{
    node* ch[2];
    ll key,fix,size,cnt;
    void mallain(){ size=ch[0]->size + ch[1]->size + cnt; }
};
typedef node* P_node;
struct Treap{
    node base[maxn],nil;
    P_node root,null,len;
    Treap(){
        root=null=&nil;
        null->key=null->fix=1e17;
        null->size=null->cnt=0;
        null->ch[0]=null->ch[1]=null;
        len=base;
    }
    P_node newnode(ll tkey){
        len->key=tkey; len->fix=rand();
        len->ch[0]=len->ch[1]=null;
        len->size=len->cnt=1;
        return len++;
    }
    void rot(P_node &p,ll d){
        P_node k=p->ch[d^1]; p->ch[d^1]=k->ch[d]; k->ch[d]=p;
        p->mallain(); k->mallain(); p=k;
    }
    void _Insert(P_node &p,ll tkey){
        if(p==null) p=newnode(tkey); else
        if(p->key==tkey) p->cnt++; else{
            ll d=tkey>p->key;
            _Insert(p->ch[d],tkey); if(p->ch[d]->fix > p->fix) rot(p,d^1);
        }
        p->mallain();
    }
    void _Erase(P_node &p,ll tkey){
        if(p->key==tkey){
            if(p->cnt>1) p->cnt--; else
            if(p->ch[0]==null) p=p->ch[1]; else
            if(p->ch[1]==null) p=p->ch[0]; else{
                ll d=p->ch[0]->fix > p->ch[1]->fix;
                rot(p,d); _Erase(p->ch[d],tkey);
            }
        } else _Erase(p->ch[tkey>p->key],tkey);
        p->mallain();
    }
    ll _Kth(P_node p,ll k){
        if(p==null||k<1||k>p->size) return 0;
        if(k<p->ch[0]->size+1) return _Kth(p->ch[0],k);
        if(k>p->ch[0]->size+p->cnt) return _Kth(p->ch[1],k-p->ch[0]->size-p->cnt);
        return p->key;
    }
    ll _Rank(P_node p,ll tkey,ll res){
        if (p==null) return -1;
        if(p->key==tkey) return p->ch[0]->size+res+1;
        if(tkey<p->key) return _Rank(p->ch[0],tkey,res);
        return _Rank(p->ch[1],tkey,res+ p->ch[0]->size + p->cnt);
    }
    ll _Pred(P_node p,ll tkey){
        if(p==null) return -1e+9;
        if(tkey<=p->key) return _Pred(p->ch[0],tkey);
        return max(p->key,_Pred(p->ch[1],tkey));
    }
    ll _Succ(P_node p,ll tkey){
        if(p==null) return 1e+9;
        if(tkey>=p->key) return _Succ(p->ch[1],tkey);
        return min(p->key,_Succ(p->ch[0],tkey));
    }
    void _Prll(P_node p){
        if(p==null) return;
        _Prll(p->ch[0]);
        for(ll i=1;i<=p->cnt;i++) printf("%lld ",p->key);
        _Prll(p->ch[1]);
    }
    void Insert(ll tkey){ _Insert(root,tkey); }
    void Erase(ll tkey){ _Erase(root,tkey); }
    ll Kth(ll k){ return _Kth(root,k); }
    ll Rank(ll tkey){ return _Rank(root,tkey,0); }
    ll Pred(ll tkey){ return _Pred(root,tkey); }
    ll Succ(ll tkey){ return _Succ(root,tkey); }
    void Prll(){ _Prll(root); printf("\n"); }
} T;
int main() {
//#ifndef ONLINE_JUDGE
//    freopen("in.txt", "r", stdin);
//#endif
    ll n, m, t, p;
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; i++)
        T.Insert(i + (1e5 - num[i]) * 1e13 + pen[i] * 1e5);
    for (ll i = 0; i < m; i++) {
        scanf("%lld%lld", &t, &p);
        ll r = T.Rank(t + (1e5 -  num[t]) * 1e13 + pen[t] * 1e5);
        if (r != -1) {
            T.Erase(t + (1e5 -  num[t]) * 1e13 + pen[t] * 1e5);
        }
        num[t] += 1;
        pen[t] += (int)p;
        T.Insert(t + (1e5 - num[t]) * 1e13 + pen[t] * 1e5);
        ll r1 = T.Rank(1 + (1e5 -  num[1]) * 1e13 + pen[1] * 1e5);
        printf("%lld\n", r1);
    }
    return 0;
}


// 无封装
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<ctime>
using namespace std;
struct node{
    node *left,*right;
    int v,p,cnt,sz;
}*root,*null=new node((node){null,null,0,0,0,0});
int in(){
    int x=0; char ch=getchar(); bool f=true;
    while (ch<'0' || ch>'9'){
        if (ch=='-') f=false;
        ch=getchar();
    }
    while (ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
    if (!f) x=-x;
    return x;
}
void push_up(node *x){
    x->sz=x->left->sz+x->right->sz+x->cnt;
}
void lturn(node *&x){
    node *y=x->right;
    x->right=y->left; y->left=x;
    y->sz=x->sz; push_up(x); x=y;
}
void rturn(node *&x){
    node *y=x->left;
    x->left=y->right; y->right=x;
    y->sz=x->sz; push_up(x); x=y;
}
void Insert(node *&x,int k){
    if (!x->sz){
        x=new node;
        x->left=x->right=null;
        x->v=k; x->p=rand();
        x->sz=x->cnt=1;
        return;
    }
    x->sz++;
    if (k==x->v) x->cnt++;
    else if (k>x->v){
        Insert(x->right,k);
        if (x->right->p<x->p) lturn(x);
    }
    else {
        Insert(x->left,k);
        if (x->left->p<x->p) rturn(x);
    }
}
void Delete(node *&x,int k){
    if (!x->sz) return;
    if (k==x->v){
        if (x->cnt>1) x->cnt--,x->sz--;
        else if (!x->left->sz || !x->right->sz){
            node *t=x;
            if (!x->left->sz) x=x->right;
            else x=x->left;
            delete t;
        }
        else if (x->left->p<x->right->p)
            rturn(x),Delete(x,k);
        else lturn(x),Delete(x,k);
    }
    else if (k<x->v) x->sz--,Delete(x->left,k);
    else x->sz--,Delete(x->right,k);
}
int Q_rank(node *x,int k){
    if (!x->sz) return 0;
    if (k==x->v) return x->left->sz+1;
    else if (k<x->v) return Q_rank(x->left,k);
    else return Q_rank(x->right,k)+x->left->sz+x->cnt;
}
int Q_num(node *x,int k){
    if (!x->sz) return 0;
    if (k<=x->left->sz) return Q_num(x->left,k);
    else if (k>x->left->sz+x->cnt)
        return Q_num(x->right,k-x->left->sz-x->cnt);
    else return x->v;
}
int Q_pro(node *x,int k,int c){
    if (!x->sz) return c;
    if (k>x->v) return Q_pro(x->right,k,x->v);
    else return Q_pro(x->left,k,c);
}
int Q_suc(node *x,int k,int c){
    if (!x->sz) return c;
    if (k<x->v) return Q_suc(x->left,k,x->v);
    else return Q_suc(x->right,k,c);
}
int main(){
    freopen("phs.in","r",stdin);
    freopen("phs.out","w",stdout);
    int n=in(); root=null; srand(time(0));
    while (n--){
        int opt=in(),x=in();
        switch (opt){
            case 1:Insert(root,x); break;
            case 2:Delete(root,x); break;
            case 3:printf("%d\n",Q_rank(root,x)); break;
            case 4:printf("%d\n",Q_num(root,x)); break;
            case 5:printf("%d\n",Q_pro(root,x,0)); break;
            case 6:printf("%d\n",Q_suc(root,x,0)); break;
        }
    }
    return 0;
}
