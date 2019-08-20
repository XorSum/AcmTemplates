---
index: 2
title: lca
---
st
---

typedef long long ll;
const ll maxn = 300010;
vector<int> mmp[maxn];
int fa[maxn][22];
int dep[maxn];

int dfs(int x,int f,int dp) {
    dep[x]=dp;
    fa[x][0]=f;
    for (int i=1; i<=20; i++)
        fa[x][i]=fa[fa[x][i-1]][i-1];
    for (int i=0; i<mmp[x].size(); i++)
        if (mmp[x][i]!=f)
            dfs(mmp[x][i],x,dp+1);
    return 0;
}

int lca(int x,int y)
{
    if (dep[x]>dep[y]) swap(x,y);
    for (int i=24; i>=0; i--)
        if (dep[fa[y][i]]>=dep[x])
            y=fa[y][i];
    if (x==y) return x;
    for (int i=24; i>=0; i--)
        if (fa[x][i] != fa[y][i] )
            x=fa[x][i] , y=fa[y][i];
    return fa[x][0];
}

int main(){
	int n;
    scanf("%d",&n);
    for (int i=1,x,y; i<n; i++){
        scanf("%d%d",&x,&y);
        mmp[x].push_back(y);
        mmp[y].push_back(x);
    }
    dep[0]=-1;
    dfs(1,0,0);
}
