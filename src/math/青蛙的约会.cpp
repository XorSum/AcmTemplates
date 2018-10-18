#include <iostream>  
#include <stdio.h>  
#include <string>  
#include <cstring>  
#include <cmath>  
#include <algorithm>  
typedef long long ll;  
  
using namespace std;  
  
ll exgcd(ll a,ll b,ll &x,ll &y)  
{  
    ll r,t;  
    if(b==0)  
    {  
        x=1;  
        y=0;  
        return a;  
    }  
    r=exgcd(b,a%b,x,y);  
    t=x;  
    x=y;  
    y=t-a/b*y;  
  
    return r;  
}  
  
int main()  
{  
    ll x,y,m,n,L;  
    ll d,r,xx,yy;  
  
    while(~scanf("%lld%lld%lld%lld%lld",&x,&y,&m,&n,&L))  
    {  
        d=exgcd( (n-m),L,xx,yy );//求得最大公约数  
  
        if( (x-y)%d )//判断线性同余方程是否有解  
        {  
            printf("Impossible\n");  
            continue;  
        }  
  
        xx=xx*((x-y)/d);  
        r=L/d;  
        xx=(xx%r+r)%r;  
  
        printf("%lld\n",xx);  
    }  
  
    return 0;  
}  