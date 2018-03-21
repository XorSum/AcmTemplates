typedef long long ll;
const ll mod = 7777777;
struct Matrx{
    ll a[10][10];
    Matrx(){
        memset(a,0,sizeof a);
    }
    Matrx operator*(const Matrx b) const{
        Matrx ans;
        for (int i=0;i<10;i++){
            for (int j=0;j<10;j++){
                for (int k=0;k<10;k++){
                    ans.a[i][j]=(ans.a[i][j]+a[i][k]*b.a[k][j]%mod)%mod;
                }
            }
        }
        return ans;
    }
    Matrx pow(int x){
        Matrx ans=*this,base=*this;
        x--;
        while(x>0){
            if (x&1) ans=ans*base;
            base=base*base;
            x>>=1;
        }
        return ans;
    }
    void show(){
        for (int i=0;i<10;i++)
        {
            for (int j=0;j<10;j++)
                printf("%lld ",a[i][j]);
            printf("\n");
        }
    }
};