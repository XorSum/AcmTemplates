---
index: 6
title: Min Cost Max Flow
---
st
---

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 1010;
const int MAXM = 4010;
const int INF  = 0x3f3f3f3f;
struct Edge {
    int from, to, cap, flow, cost, next;
};
Edge edge[MAXM];
int head[MAXN], edt;
int pre[MAXN];
int dist[MAXN];
bool vis[MAXN];

void init() {
    edt = 0;
    memset(head, -1, sizeof(head));
}

void addEdge(int u, int v, int f, int c){
  //  cout<<u<<" "<<v<<" "<<f<<" "<<c<<endl;
    edge[edt] = (Edge){u, v, f, 0, c, head[u]};
    head[u] = edt++;
    edge[edt] = (Edge){v, u, 0, 0, -c, head[v]};
    head[v] = edt++;
}

bool SPFA(int s, int t) {
    queue<int> q;
    memset(dist, INF, sizeof(dist));
    memset(vis, false, sizeof(vis));
    memset(pre, -1, sizeof(pre));
    dist[s] = 0;
    vis[s] = true;
    q.push(s);
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        vis[u] = false;
        for(int i = head[u]; i != -1; i = edge[i].next) {
            Edge &e = edge[i];
            if(dist[e.to] > dist[u] + e.cost && e.cap > e.flow) {
                dist[e.to] = dist[u] + e.cost;
                pre[e.to] = i;
                if(!vis[e.to]) {
                    vis[e.to] = true;
                    q.push(e.to);
                }
            }
        }
    }
    return pre[t] != -1;
}

void MCMF(int s, int t, int &flow, int &cost) {
    flow = 0;
    cost = 0;
    while(SPFA(s, t)) {
        int Min = INF;
        for(int i = pre[t]; i != -1; i = pre[edge[i^1].to]){
            Edge &e = edge[i];
            Min = min(Min, e.cap - e.flow);
        }
        for(int i = pre[t]; i != -1; i = pre[edge[i^1].to]){
            edge[i].flow += Min;
            edge[i^1].flow -= Min;
            cost += edge[i].cost * Min;
        }
        flow += Min;
    }
}

int main() {
    init();
    int s = 2*n+1,t = 2*n+2;
    addEdge(from,t0,flow,cost);
    int cost,flow;
    MCMF(s,t,flow,cost);
    printf("%d %d\n",flow,cost);
    return 0;
}

