---
index: 0
title: unordered_map
---

description

---

struct Node {
    int x, y;
    ll l2;
};

//
bool operator==(Node a, Node b) {
    return a.x == b.x && a.y == b.y && a.l2 == b.l2;
}

struct myHash {
    size_t operator()(Node __val) const {
        return static_cast<size_t>(__val.x * 101 + __val.y * 100007 + __val.l2);
    }
};

unordered_map<Node, list<Node2>, myHash> mp;


