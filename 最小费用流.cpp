const int MAXN = 100010;
const int MAXM = 100010;
const int INF  = 0x3f3f3f3f;
struct Edge {
    int from, to, cap, flow, cost, next;
};
Edge edge[MAXM];
int head[MAXN], edgenum;
int pre[MAXN];
int dist[MAXN];
bool vis[MAXN];

void init() {
    edgenum = 0;
    memset(head, -1, sizeof(head));
}

void addEdge(int u, int v, int w, int c){
  //  cout<<u<<" "<<v<<" "<<w<<" "<<c<<endl;
    Edge E1 = {u, v, w, 0, c, head[u]};
    edge[edgenum] = E1;
    head[u] = edgenum++;
    Edge E2 = {v, u, 0, 0, -c, head[v]};
    edge[edgenum] = E2;
    head[v] = edgenum++;
}

bool SPFA(int s, int t) {
    queue<int> Q;
    memset(dist, INF, sizeof(dist));
    memset(vis, false, sizeof(vis));
    memset(pre, -1, sizeof(pre));
    dist[s] = 0;
    vis[s] = true;
    Q.push(s);
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        vis[u] = false;
        for(int i = head[u]; i != -1; i = edge[i].next) {
            Edge E = edge[i];
            if(dist[E.to] > dist[u] + E.cost && E.cap > E.flow) {
                dist[E.to] = dist[u] + E.cost;
                pre[E.to] = i;
                if(!vis[E.to]) {
                    vis[E.to] = true;
                    Q.push(E.to);
                }
            }
        }
    }
    return pre[t] != -1;
}

void MCMF(int s, int t, int &cost, int &flow)
{
    flow = 0;
    cost = 0;
    while(SPFA(s, t)) {
        int Min = INF;
        for(int i = pre[t]; i != -1; i = pre[edge[i^1].to]){
            Edge E = edge[i];
            Min = min(Min, E.cap - E.flow);
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
    int s = 2*n+1,t =2*n+2;
    addEdge(from,t0,flow,cost);
    int cost,flow;
    MCMF(s,t,cost,flow);
    printf("%d %d\n",flow,cost);
    return 0;
}

