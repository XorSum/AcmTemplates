

//  线段树 区间更新 最小值

using namespace std;
typedef long long ll;
const int inf = 0x3f3f3f3f;
const int MAXN = 1000005;
int Min[MAXN<<2],lazy[MAXN<<2];
void build(int rt,int l,int r) {
    if (l == r) {
    // 改这里
        Min[rt] = 0;
        return;
    }
    int mid = (l + r) >> 1;
    build(rt << 1, l, mid);
    build(rt << 1 | 1, mid + 1, r);
    Min[rt] = min(Min[rt << 1], Min[rt << 1 | 1]);
    return;
}
void pushdown(int rt) {
    if (lazy[rt]) {
        lazy[rt << 1] += lazy[rt];
        lazy[rt << 1 | 1] += lazy[rt];
        Min[rt << 1] += lazy[rt];
        Min[rt << 1 | 1] += lazy[rt];
        lazy[rt] = 0;
    }
}
void add(int rt,int l,int r,int L,int R,int x) {
    if (L <= l && r <= R) {
        lazy[rt] += x;
        Min[rt] += x;
        return;
    }
    pushdown(rt);
    int mid = (l + r) >> 1;
    if (L <= mid) add(rt << 1, l, mid, L, R, x);
    if (R > mid) add(rt << 1 | 1, mid + 1, r, L, R, x);
    Min[rt] = min(Min[rt << 1], Min[rt << 1 | 1]);
}
int query(int rt,int l,int r,int L,int R) {
    if (L <= l && r <= R) {
        return Min[rt];
    }
    pushdown(rt);
    int mid = (l + r) >> 1;
    int ans = inf;
    if (L <= mid) ans = min(query(rt << 1, l, mid, L, R), ans);
    if (mid < R) ans = min(query(rt << 1 | 1, mid + 1, r, L, R), ans);
    return ans;
}




//  ZKW线段树


class ZkwTree {
private:
    int M, N;
    int *tree;
    inline int Ope(int x, int y) {
        return x + y;
    }
    inline void Maintain(int x) {
        tree[x] = Ope(tree[x << 1], tree[x << 1 | 1]);
    }
public:
    ZkwTree(int n) {
        N = n;
        for (M = 1; M < N; M <<= 1);
        tree = new int[M + N + 50];
        for (int i = M + 1; i <= M + N; ++i) scanf("%d", &tree[i]);
        for (int i = M - 1; i; --i) Maintain(i);
    }
    inline void Update(int pos, int v) {
        pos += M;
        tree[pos] = v;
        for (pos >>= 1; pos; pos >>= 1) Maintain(pos);
    }
    inline int Query(int l, int r) {
        int ans = 0;
        for (l = l + M - 1, r = r + M + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
            if (~l & 1)
                ans = Ope(ans, tree[l ^ 1]);
            if (r & 1)
                ans = Ope(ans, tree[r ^ 1]);
        }
        return ans;
    }
};












