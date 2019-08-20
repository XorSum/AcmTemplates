---
index: 5
title: gougu
---
st
---

#include<iostream>

typedef long long ll;

ll N;

void Search(ll a,ll b,ll c){
    std::cout<<a<<' '<<b<<' '<<c<<std::endl;
    if(a<b && 2ll*c+b-2ll*a<=N && 2ll*c+2ll*b-a<=N && 3ll*c+2ll*b-2ll*a<=N) Search(2ll*c+b-2ll*a, 2ll*c+2ll*b-a, 3ll*c+2ll*b-2ll*a);
    if(2ll*c-2ll*b+a<=N && 2ll*c-b+2ll*a<=N && 3ll*c-2ll*b+2ll*a<=N) Search(2ll*c-2ll*b+a, 2ll*c-b+2ll*a, 3ll*c-2ll*b+2ll*a);
    if(2ll*c+b+2ll*a<=N && 2ll*c+2ll*b+a<=N && 3ll*c+2ll*b+2ll*a<=N) Search(2ll*c+b+2ll*a, 2ll*c+2ll*b+a, 3ll*c+2ll*b+2ll*a);
}

int main(){
    std::cin>>N;
    Search(3ll,4ll,5ll);
    return 0;
}

// [Tree of primitive Pythagorean triples](https://en.wikipedia.org/wiki/Tree_of_primitive_Pythagorean_triples)
// [csdn题解](https://blog.csdn.net/invariance/article/details/78234475)


