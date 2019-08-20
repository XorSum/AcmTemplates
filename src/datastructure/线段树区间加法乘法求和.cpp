---
index: 2
title: SegmentTree
---
st
---

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll maxn = 100005;

struct STree {

    ll data[maxn << 2];
    ll lazy_add[maxn << 2];
    ll lazy_mul[maxn << 2];

    void build() {
        memset(data, 0, sizeof data);
        memset(lazy_mul, 0, sizeof lazy_mul);
        memset(lazy_add, 0, sizeof lazy_add);
    }

    void pushdown(ll rt, ll l, ll r) {
        if (lazy_add[rt] != 0 || lazy_mul[rt] != 1) {
            ll mid = (l + r) / 2;
            data[rt * 2] = data[rt * 2] * lazy_mul[rt] + lazy_add[rt] * (mid - l + 1);
            data[rt * 2 + 1] = data[rt * 2 + 1] * lazy_mul[rt] + lazy_add[rt] * (r - mid);
            lazy_mul[rt * 2] = lazy_mul[rt * 2] * lazy_mul[rt];
            lazy_mul[rt * 2 + 1] = lazy_mul[rt * 2 + 1] * lazy_mul[rt];
            lazy_add[rt * 2] = lazy_add[rt * 2] * lazy_mul[rt] + lazy_add[rt];
            lazy_add[rt * 2 + 1] = lazy_add[rt * 2 + 1] * lazy_mul[rt] + lazy_add[rt];
            lazy_add[rt] = 0;
            lazy_mul[rt] = 1;
        }
    }

    void update(ll rt, ll l, ll r, ll L, ll R, ll val, ll type) {
        //   cout << "update " << rt << " " << l << " " << r << " " << L << " " << R << " " << val << " " << type << endl;
        if (l > R || r < L) return;
        if (L <= l & r <= R) {
            if (type == 2) {
                data[rt]  += val * (r - l + 1);
                lazy_add[rt] += val;
            } else {
                data[rt] *= val;
                lazy_add[rt] *= val;
                lazy_mul[rt] *= val;
            }
        } else {
            ll mid = (l + r) / 2;
            pushdown(rt, l, r);
            if (L <= mid) update(rt * 2, l, mid, L, R, val, type);
            if (mid < R) update(rt * 2 + 1, mid + 1, r, L, R, val, type);
            data[rt] = data[rt * 2] + data[rt * 2 + 1];
        }
    }

    ll query(ll rt, ll l, ll r, ll L, ll R) {
        if (L <= l && r <= R) {
            return data[rt];
        }
        pushdown(rt, l, r);
        ll mid = (l + r) / 2;
        ll ret = 0;
        if (L <= mid) ret += query(rt * 2, l, mid, L, R);
        if (mid < R) ret += query(rt * 2 + 1, mid + 1, r, L, R);
        return ret;
    }
};
