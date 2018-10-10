#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <set>
#include <queue>

using namespace std;
typedef long long ll;
const ll maxn = 1000005;

struct Trie {
    int nxt[26];
    int count;
    int fail;
} trie[maxn];

struct ACauto {

    int cnt;

    void init(){
        memset(trie,0,sizeof trie);
        cnt = 2;
    }

    void insert(char s[], int rt = 1) {
        int p = rt;
        for (int i = 0; s[i]; i++) {
            int j = s[i]-'a';
            if (trie[p].nxt[j] == 0) {
                trie[p].nxt[j] = cnt++;
            }
            p = trie[p].nxt[j];
        }
        trie[p].count++;
    }

    void build_fail(int rt = 1) {
        trie[rt].fail = 0;
        queue<int> q;
        q.push(rt);
        while (!q.empty()) {
            int fr = q.front();
            q.pop();
            for (int i = 0; i < 26; i++) {
                if (trie[fr].nxt[i] != 0) {
                    if (fr == rt) trie[trie[fr].nxt[i]].fail = rt;
                    else {
                        int p = trie[fr].fail;
                        while (p != 0) {
                            if (trie[p].nxt[i] != 0) {
                                trie[trie[fr].nxt[i]].fail = trie[p].nxt[i];
                                break;
                            }
                            p = trie[p].fail;
                        }
                        if (p == 0) trie[trie[fr].nxt[i]].fail = rt;
                    }
                    q.push(trie[fr].nxt[i]);
                }
            }
        }
    }

    int query_count(char s[], int rt = 1) {
        int p = rt, i = 0, cnt = 0;
        while (s[i]) {
            int j = s[i] - 'a';
            while (trie[p].nxt[j] == 0 && p != rt) p = trie[p].fail;
            p = trie[p].nxt[j];
            if (p == 0) p = rt;
            int tmp = p;
            while (tmp != rt && trie[tmp].count != -1) {
                cnt += trie[tmp].count;
                trie[tmp].count = -1;
                tmp = trie[tmp].fail;
            }
            i++;
        }
        return cnt;
    }

}ac ;


char str[maxn];

int main() {

   // freopen("in.txt", "r", stdin);

    int t;
    scanf("%d",&t);
    while (t--){
        ac.init();
        int n;
        scanf("%d",&n);
        while (n--){
            scanf("%s",str);
            ac.insert(str);
        }
        scanf("%s",str);
        ac.build_fail();
        int ans = ac.query_count(str);
        printf("%d\n",ans);
    }
    return 0;
}

