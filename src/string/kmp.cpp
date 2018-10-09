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
