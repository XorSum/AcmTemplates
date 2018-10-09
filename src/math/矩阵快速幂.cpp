const ll mod = 10000;
const int MATRX_SIZE = 2;
struct Matrx{
    ll a[MATRX_SIZE][MATRX_SIZE];
    Matrx(){
        memset(a,0,sizeof a);
    }
    Matrx operator*(const Matrx b) const{
        Matrx ans;
        for (int i=0;i<MATRX_SIZE;i++){
            for (int j=0;j<MATRX_SIZE;j++){
                for (int k=0;k<MATRX_SIZE;k++){
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
        for (int i=0;i<MATRX_SIZE;i++)
        {
            for (int j=0;j<MATRX_SIZE;j++)
                printf("%lld ",a[i][j]);
            printf("\n");
        }
    }
};
