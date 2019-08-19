---
title: SegmentTree
chapter: DataStructure
---

STree st;
ll fa[maxn], dep[maxn], siz[maxn], top[maxn], w[maxn];
vector<ll> son[maxn];
ll totw;

ll dfs1(ll x, ll f, ll d) {
    siz[x] = 1;
    fa[x] = f;
    dep[x] = d;
    for (ll j = 0; j < son[x].size(); j++) {
        if (son[x][j] != f) {
            siz[x] += dfs1(son[x][j], x, d + 1);
        }
    }
    return siz[x];
}


void dfs2(ll x, ll tp) {
    w[x] = ++totw;
    top[x] = tp;
    if (son[x].size() == 0) return;
    ll ws = 0;
    for (ll j = 0; j < son[x].size(); j++)
        if (siz[son[x][j]] > siz[son[x][ws]])
            ws = j;
    dfs2(son[x][ws], tp);
    for (ll j = 0; j < son[x].size(); j++)
        if (j != ws) dfs2(son[x][j], son[x][j]);
}

void update(ll x, ll y, ll val, ll type) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        st.update(1, 1, totw, w[top[x]], w[x], val, type);
        x = fa[top[x]];
    }
    if (dep[x] < dep[y]) swap(x, y);
    st.update(1, 1, totw, w[y], w[x], val, type);
}

ll query(ll x, ll y) {
    ll ret = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        ret += st.query(1, 1, totw, w[top[x]], w[x]);
        x = fa[top[x]];
    }
    if (dep[x] < dep[y]) swap(x, y);
    ret += st.query(1, 1, totw, w[y], w[x]);
    return ret;
}
