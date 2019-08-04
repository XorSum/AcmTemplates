#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

vector<int>v[N];
int num[N], dep[N], sz[N], fa[N][20], pos[N], tot[N];
queue<int>q;

int en, head[N];
struct Edge {
    int to, nxt;
} e[N];

inline void add(int x, int y)
{
    e[++en].to = y;
    e[en].nxt = head[x];
    head[x] = en;
}

inline void update(int x)
{
    for (register int i = 1; i <= 18; ++i) {
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    }
}

inline int get_lca(int x, int y)
{
    if (dep[x] < dep[y]) swap(x, y);
    for (register int i = 18; i >= 0; --i) {
        if (dep[fa[x][i]] >= dep[y]) x = fa[x][i];
    }
    if (x == y) return x;
    for (register int i = 18; i >= 0; --i) {
        if (fa[x][i] != fa[y][i]) {
            x = fa[x][i], y = fa[y][i];
        }
    }
    return fa[x][0];
}

inline void dfs(int x)
{
    for (register int i = head[x]; i; i = e[i].nxt) {
        dfs(e[i].to);
        tot[x] += tot[e[i].to];
    }
    ++tot[x];
}

int main()
{
    register int n;
    scanf("%d", &n);
    for (register int i = 1, x; i <= n; ++i) {
        scanf("%d", &x);
        while (x != 0) {
            v[x].push_back(i);
            ++num[i];
            scanf("%d", &x);
        }
        pos[i] = -1;
    }
    for (register int i = 1; i <= n; ++i) {
        sz[i] = v[i].size();
        if (num[i] == 0) q.push(i), pos[i] = 0;
    }
    register int now;
    while (!q.empty()) {
        now = q.front(); q.pop();
        dep[now] = dep[pos[now]] + 1;
        fa[now][0] = pos[now], update(now);
        add(pos[now], now);
        for (register int i = 0; i < sz[now]; ++i) {
            --num[v[now][i]];
            if (pos[v[now][i]] == -1) pos[v[now][i]] = now;
            else pos[v[now][i]] = get_lca(pos[v[now][i]], now);
            if (num[v[now][i]] == 0) q.push(v[now][i]);
        }
    }
    return 0;
}
