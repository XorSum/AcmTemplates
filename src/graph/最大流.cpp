---
title: Dijkstra
chapter: Graph
---

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N  = 40050;
const ll M = 40050;
const ll inf =  LLONG_MAX/2;

struct ss{
    int v,next;
    ll flow;
}edg[M];

int tot,S,T;
int head[N];
int dis[N];
int cur[N];
void init(){
    tot=0;
    memset(head,-1,sizeof(head));
}

void addedge(int u,int v,ll flow){
    edg[tot]=(ss){v,head[u],flow};
    head[u]=tot++;
    edg[tot]=(ss){u,head[v],0}; // 如果想加双向边就把0改成flow
    head[v]=tot++;
}

int bfs(){
    memset(dis,0,sizeof(dis));
    queue<int>q;
    q.push(S);
    dis[S]=1;
    while(!q.empty()){
        int now=q.front();  q.pop();
        for(int i=head[now];i!=-1;i=edg[i].next){
            ss &e=edg[i];
            if(e.flow>0&&dis[e.v]==0){
                dis[e.v]=dis[now]+1;
                q.push(e.v);
            }
        }
    }
    if (dis[T]==0) return 0;
    return 1;
}

ll dfs(int x,ll mf) {
    if(x==T) return mf;
    for(int i=cur[x];i!=-1;i=edg[i].next){
        cur[x]=i;
        ss &e=edg[i];
        if(e.flow>0&&dis[e.v]==dis[x]+1){
            ll flow=dfs(e.v,min(mf,e.flow));
            if(flow!=0){
                e.flow-=flow;
                edg[i^1].flow+=flow;
                return flow;
            }
        }
    }
    return 0;
}

ll dinic() {
    ll ans=0,flow;
    while (bfs()) {
        for (int i=0;i<N;i++) cur[i]=head[i];
        while (flow=dfs(S,inf)) ans+=flow;
    }
    return ans;
}

int main() {
    init();
    ll n,m;
    scanf("%lld%lld",&n,&m);
    S = 1;
    T = n;
    addedge(from,to,flow);
    ll maxFlow = dinic();
    printf("%lld\n",maxFlow);
    return 0;
}
