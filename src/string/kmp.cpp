const ll maxn = 1000006;
int Next[maxn];
char  str[maxn];
char t[maxn];
void getNext( char * str, int len , int * next) {
    int i, j;
    next[0] = -1;
    for (i = 1; i < len; i++) {
        j = next[i - 1];
        while (str[j + 1] != str[i] && j >= 0)
            j = next[j];
        if (str[i] == str[j + 1])
            next[i] = j + 1;
        else
            next[i] = -1;
    }
}

int kmp_cnt(char  *s,int slen,char *t,int tlen,int *nxt){
    getNext(t,tlen,nxt);
    int k=-1;
    int cnt = 0;
    for (int i=0;i<slen;i++){
        while(k>-1&&t[k+1]!=s[i]) k=nxt[k];
        if (t[k+1]==s[i])k++;
        if (k==tlen-1){
            cnt++;
            k=nxt[k];
        }
    }
    return  cnt;
}


#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstring>
const int maxn = 110;
typedef long long ll;
const int inf = 0x3f3f3f3f;
using namespace std;
void getNext(char *t,int len,int* nxt){
    nxt[0]=-1;
    int k=-1;
    for (int i=1;i<len;i++){
        while (k>-1&&t[k+1]!=t[i]) k=nxt[k];
        if (t[k+1]==t[i]) k++;
        nxt[i]=k;
    }
}
int kmp(char *s,int slen,char* t,int tlen,int *nxt){
    getNext(t,tlen,nxt);
    int k=-1;
    for (int i=0;i<slen;i++){
        while (k>-1&&t[k+1]!=s[i]) k=nxt[k];
        if (t[k+1]==s[i]) k++;
        if (k==tlen-1){
            return i-tlen+1;
        }
    }
    return -1;
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    char pat[100],str[100];
    int nxt[100];
    cin>>pat;
    cin>>str;
    int p = kmp(str,strlen(str),pat,strlen(pat),nxt);
    cout<<p<<endl;
    return 0;
}
