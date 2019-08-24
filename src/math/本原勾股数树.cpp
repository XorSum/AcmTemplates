---
index: 5
title: gougu
---
st
---

#include<iostream>

typedef long long ll;

unordered_map<ll, ll> mp;

ll N = 1500000;

void Search(ll a, ll b, ll c) {
    ll l = a + b + c;
    if (a > N || b > N || l > N) return;
    cout<<a<<" "<<b<<" "<<c<<endl;
    for (ll i = 1; i * l <= N; i++) mp[i * l]++;
    if (a < b) Search(2ll * c + b - 2ll * a, 2ll * c + 2ll * b - a, 3ll * c + 2ll * b - 2ll * a);
    Search(2ll * c - 2ll * b + a, 2ll * c - b + 2ll * a, 3ll * c - 2ll * b + 2ll * a);
    Search(2ll * c + b + 2ll * a, 2ll * c + 2ll * b + a, 3ll * c + 2ll * b + 2ll * a);
}

int main(){
    std::cin>>N;
    Search(3ll,4ll,5ll);
    return 0;
}

// [Tree of primitive Pythagorean triples](https://en.wikipedia.org/wiki/Tree_of_primitive_Pythagorean_triples)
// [csdn题解](https://blog.csdn.net/invariance/article/details/78234475)


