---
index: 0
title: MaxFlowWithDijkstra
---

min cost max flow using dijkstra

---
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
const int INF = 0x3f3f3f3f;
const int maxn = 1e4;

struct edge {
    int to, cap, cost, rev;

    edge() {}

    edge(int to, int _cap, int _cost, int _rev) :
            to(to), cap(_cap), cost(_cost), rev(_rev) {}
};

struct Min_Cost_Max_Flow {
    int V, H[maxn + 5], dis[maxn + 5], PreV[maxn + 5], PreE[maxn + 5];
    vector<edge> G[maxn + 5];

    void Init(int n) {
        V = n;
        for (int i = 0; i <= V; ++i)G[i].clear();
    }

    void Add_Edge(int from, int to, int cap, int cost) {
        G[from].push_back(edge(to, cap, cost, G[to].size()));
        G[to].push_back(edge(from, 0, -cost, G[from].size() - 1));
    }

    void dijk(int s) {
        priority_queue<pii, vector<pii>, greater<pii> > q;
        fill(dis, dis + 1 + V, INF);
        dis[s] = 0;
        q.push(pii(0, s));
        while (!q.empty()) {
            pii now = q.top();
            q.pop();
            int v = now.second;
            if (dis[v] < now.first)continue;
            for (int i = 0; i < G[v].size(); ++i) {
                edge &e = G[v][i];
                if (e.cap > 0 && dis[e.to] > dis[v] + e.cost + H[v] - H[e.to]) {
                    dis[e.to] = dis[v] + e.cost + H[v] - H[e.to];
                    PreV[e.to] = v;
                    PreE[e.to] = i;
                    q.push(pii(dis[e.to], e.to));
                }
            }
        }
    }

    int Min_cost_max_flow(int s, int t, int f, int &flow) {
        int res = 0;
        fill(H, H + 1 + V, 0);
        while (f) {
            dijk(s);
            if (dis[t] == INF)break;
            for (int i = 0; i <= V; ++i)H[i] += dis[i];
            int d = f;
            for (int v = t; v != s; v = PreV[v])d = min(d, G[PreV[v]][PreE[v]].cap);
            f -= d;
            flow += d;
            res += d * H[t];
            for (int v = t; v != s; v = PreV[v]) {
                edge &e = G[PreV[v]][PreE[v]];
                e.cap -= d;
                G[v][e.rev].cap += d;
            }
        }
        return res;
    }
} MCMF;

int a[maxn];


int main() {

//    freopen("in.txt", "r", stdin);

    int t;
    scanf("%d", &t);
    while (t--) {
        int n, k;
        scanf("%d%d", &n, &k);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        MCMF.Init(2 * n + 2);
        int S = 0, T = 2 * n + 1;
        for (int i = 1; i <= n; i++) {
            MCMF.Add_Edge(S, i, 1, 0);
            MCMF.Add_Edge(i, n + i, 1, -a[i]);
            MCMF.Add_Edge(n + i, T, 1, 0);
            for (int j = 1; j < i; j++) {
                if (a[j] <= a[i]) {
                    MCMF.Add_Edge(n + j, i, 1, 0);
                }
            }
        }
        MCMF.Add_Edge(2 * n + 1, 2 * n + 2, k, 0);
        ll ans = -MCMF.Min_cost_max_flow(S, 2 * n + 2, INF, k);
        printf("%lld\n", ans);
    }
    
    return 0;
}

