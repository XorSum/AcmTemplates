---
title: Dijkstra
chapter: Graph
---

#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
const int maxn = 400005;
const int inf = 0x3f3f3f3f;
vector<pii> mmp[maxn];
int dis[maxn];
int vis[maxn];
int n,m;

void dijkstra(int s){

    for (int i=0;i<=n+m;i++) {dis[i] = inf;vis[i]=0;}
    priority_queue<pii> q;
    dis[s] = 0;
    q.push(pii(0,s)); // dis ,pos
    while(!q.empty()){
        pii fir = q.top(); q.pop();
        int u = fir.second;
        if (vis[u]) continue;
        vis[u]=1;
        for (pii nx : mmp[u]){
            int v = nx.first,d = nx.second;
            if (vis[v]) continue;
            if (dis[v]>dis[u]+d){
                dis[v]=dis[u]+d;
                q.push(pii(-dis[v],v));
            }
        }
    }
}


#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
typedef long long ll;
const ll inf = 0x3f3f3f3f;
const int maxn = 1005;
const int maxm = 1005;
struct Node
{
    int u,v,dis,next;
}node[maxm];
int head[maxn];
int cnt;
void addEdge(int x,int y,int dis){
    node[++cnt]=Node{x,y,dis,head[x]};
    head[x]=cnt;
}
int dis[maxn];
bool vis[maxn];
int pre[maxn];
int n,m;
struct cmp{ // 函数对象
    bool operator()(int a,int b){
        return dis[a]>dis[b];
    }
};
std::priority_queue<int, std::vector<int>, cmp > Q;
void dijkstra(int s){
    for (int i=1;i<=n;i++)
        dis[i]=inf;
    dis[s]=0;
    pre[s]=0;
    Q.push(s);
    while(!Q.empty()){
        int u = Q.top();
        Q.pop();
        if (vis[u]) continue;
        vis[u]=1;
        for (int i=head[u];i;i=node[i].next){
            int v = node[i].v,d = node[i].dis;
            if (!vis[v]&&dis[u]+d<dis[v]){
                dis[v]=dis[u]+d;
                pre[v]=u;
                Q.push(v);
            }
        }
    }
}
int main()
{
    freopen("in.txt","r",stdin);
    scanf("%d%d",&n,&m);
    for (int i=1,x,y,z;i<=m;i++){
        scanf("%d%d%d",&x,&y,&z);
        addEdge(x,y,z);
    }
    dijkstra(1);
    for (int i=1;i<=n;i++){
        printf("%d ",dis[i]);
        for (int j=i;j;j=pre[j]){
            printf("%d ",j);
        }
        printf("\n");
    }
    return 0;
}
