#include <cstdio>  
#include <cstring>  
#include <iostream>  
using namespace std;  
void gcd(int a,int b,int &d,int &x,int &y)  
{//a*x+b*y=gcd(a,b)=d;(x,y)为其一组整数解  
    if(!b){d=a;x=1;y=0;}  
    else{ gcd(b,a%b,d,y,x);y-=x*(a/b);}  
}  
int main()  
{  
    int n,m,m1,r1,m2,r2,flag=0,a[11],b[11],T;  
    cin>>T;  
    while(T--)  
    {  
        cin>>n>>m;  
        int i,j,k,d,x,y,c,t;  
        for(i=0;i<m;i++)  
            cin>>a[i];  
        for(i=0;i<m;i++)  
            cin>>b[i];  
        flag=0;  
        m1=a[0];r1=b[0];  
        for(i=1;i<m;i++)  
        {  
            m2=a[i];r2=b[i];  
            if(flag)continue;  
            gcd(m1,m2,d,x,y);//d=gcd(m1,m2);x*m1+y*m2=d;  
            c=r2-r1;  
            if(c%d)//对于方程m1*x+m2*y=c，如果c不是d的倍数就无整数解  
            {  
                flag=1;  
                continue;  
            }  
            t=m2/d;//对于方程m1x+m2y=c=r2-r1,若(x0,y0)是一组整数解,那么(x0+k*m2/d,y0-k*m1/d)也是一组整数解(k为任意整数)  
                    //其中x0=x*c/d,y0=x*c/d;  
            x=(c/d*x%t+t)%t;//保证x0是正数，因为x+k*t是解，(x%t+t)%t也必定是正数解(必定存在某个k使得(x%t+t)%t=x+k*t)  
            r1=m1*x+r1;//新求的r1就是前i组的解，Mi=m1*x+M(i-1)=r2-m2*y(m1为前i个m的最小公倍数);对m2取余时，余数为r2；  
                        //对以前的m取余时，Mi%m=m1*x%m+M(i-1)%m=M(i-1)%m=r  
            m1=m1*m2/d;  
        }  
        if(flag||n<r1)cout<<0<<endl;  
        else  
        {  
            int ans=(n-r1)/m1+1;//m1为ai的最小公倍数，凡是m1*i+r1的都是符合要求的数，其中r1最小  
            if(r1==0)ans--;//要求是正整数  
            cout<<ans<<endl;  
        }  
    }  
    return 0;  
}  
/* 
    中国剩余定理的普通情况：ai不一定相互互质 
*/  
