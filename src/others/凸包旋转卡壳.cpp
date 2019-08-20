---
index: 2
title: tubao
---
tubao
---
#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
typedef  long long ll;
const ll maxn = 2005;
 
struct node{
    int x,y;
}e[maxn],res[maxn];
int cmp(node a,node b){
    if(a.x==b.x)return a.y<b.y;
    return a.x<b.x;
}
int cross(node a,node b,node c){
    return (a.x-c.x)*(b.y-c.y)-(b.x-c.x)*(a.y-c.y);
}
 
double area(int p1,int p2,int p3){
    return abs((res[p1].x-res[p3].x)*(res[p2].y-res[p3].y) - (res[p1].y-res[p3].y)*(res[p2].x-res[p3].x));
}
 
double dis(int p1,int p2) {
    return sqrt( (res[p1].x - res[p2].x)*(res[p1].x - res[p2].x)+(res[p1].y - res[p2].y)*(res[p1].y - res[p2].y) );
}

int convex(int n)
{
    sort(e,e+n,cmp);
    int m=0,i,j,k;
    for(i=0;i<n;i++) {
        while(m>1&&cross(res[m-1],e[i],res[m-2])<=0)m--;
        res[m++]=e[i];
    }
    k=m;
    for(i=n-2;i>=0;i--) {
        while(m>k&&cross(res[m-1],e[i],res[m-2])<=0)m--;
        res[m++]=e[i];
    }
    if(n>1)m--;
    return m;
}
 
int main() {
  //  freopen("in.txt","r",stdin);
    int m;
    scanf("%d",&m);
    for (int i=0;i<m;i++){
        scanf("%d%d",&e[i].x,&e[i].y);
    }
    int n = convex(m);
    double ans = 1e18;
    int t = 2;
    for (int i=0;i<n;i++){
        while( area(t+1,i,i+1) > area(t,i,i+1) ) t= (t+1)%n;
        ans = min(ans, area(t,i,i+1)/dis(i,i+1));
    }
    printf("%f\n",ans);
    return 0;
}
 
