---
index: 7
title: Second Shortest Route
---
那么我们现在先回忆下Dijkstra是怎么求解最短路问题的。Dijkstra的思想是根据确定最短路的顶点来计算尚未确定顶点的最短路，这句话是什么意思呢？比如在一幅无向图中，s为源点，v1为已经确定最短路的顶点，v2，v3为尚未确定的顶点。那么我们使用v1的最短距离加上v1->v2或v3的距离，来更新v2，v3到源点s的距离。显然这么一直更新下去，那么最终s到v2，v3的距离就是最短距离（详情请参考：Here）。如果dist[v]表示s->v的最短距离，dist2[v]表示s->v的次短距离，d为s->v的第k短距离(k>1)。那么一定满足这样一个关系，dist[v] < dist2[v] <= k。看到这个等式的时候我们可以发现，如果dist2[v] > d2 > dist[v]，显然这时候我们需要将dist2[v]更新为d2。那么我们只要找到不满足dist[v] < dist2[v] <= k这个的式子的dist2[v]，那么我们就更新他。一直更新到所以式子都满足这个式子，那么dist2[v]就为源点s->v的次短路。到此我们已经推出了求解次短路的方法。
---
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <set>
#include <queue>
#include <cstdio>
using namespace std;
typedef pair<long long ,int> pii;
const int INF = 0x3f3f3f3f;
const int MAXN= 100050;
const int mod = 1000000007;
struct Edge{
    int to;
    long long cost;
    Edge(int tv=0,long long cv=0){
        to=tv;
        cost=cv;
    }
};
int n,r;
vector<Edge> graph[MAXN];
long long dist[MAXN]; //最短距离
long long dist2[MAXN]; //次短距离
long long  solve(){
    memset(dist,INF,sizeof dist);
    memset(dist2,INF,sizeof dist2);
    priority_queue<pii,vector<pii>,greater<pii> > Q;
      //从小到大的优先队列  
    //使用pair而不用edge结构体  
    //是因为这样我们不需要重载运算符  
    //pair是以first为主关键字进行排序  
    dist[1]=0;
    Q.push(pii(0,1));
    while (!Q.empty()){
        pii p=Q.top();
        Q.pop();
        //first为s->to的距离，second为edge结构体的to  
        long long v=p.second,d=p.first;
        if (dist2[v]<d) continue;
          //当取出的值不是当前最短距离或次短距离，就舍弃他  
        for (unsigned int i=0;i<graph[v].size();i++)
        {
            Edge &e=graph[v][i];
            long long d2=d+e.cost;
            if (dist[e.to]>d2){
                swap(dist[e.to],d2);
                Q.push(pii(dist[e.to],e.to));
            }
            //更新最短距离
            if (dist2[e.to]>d2&&dist[v]<d2){
                dist2[e.to]=d2;
                Q.push(pii(dist2[e.to],e.to));
            }
            //更新次短距离
        }
    }
    return dist2[n];
}
int main() {
    int a,b,t;
    long long d;
    scanf("%d",&t);
    while (t--) {
        scanf("%d%d", &n, &r);
        for (int i=0;i<=n;i++)
            graph[i].clear();
        for (int i = 0; i < r; i++) {
            scanf("%d%d%lld", &a, &b, &d);
            graph[a].push_back(Edge(b , d));
            graph[b].push_back(Edge(a , d));
        }
        printf("%lld\n", solve());
    }
    return 0;
}
