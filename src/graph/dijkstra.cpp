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
