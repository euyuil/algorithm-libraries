#include <iostream>
using namespace std;
const int N = 120000;
const int tk = 4;
char s[30],str[1010];
struct node {
    int fail,danger;
    int nxt[tk];
    void init() {
        fail = -1;
        danger = 0;
        memset(nxt,0,sizeof(nxt));
    }
} trie[N];
int top,q[N];
int f[1010][1010];
inline int idx(char c) {
    if(c == 'A')  return 0;
    else if(c == 'G') return 1;
    else if(c == 'C') return 2;
    return 3;
}
inline void ini() {
    top = 1;
    trie[0].init();
}
void ins(char *str) {
    int p = 0;
    for(int i=0; str[i]; i++) {
        int k = idx(str[i]);
        if( !trie[p].nxt[k] ) {
            trie[top].init();
            trie[p].nxt[k] = top++;
        }
        p = trie[p].nxt[k];
    }
    trie[p].danger = 1;
}
void ac() {
    int v,*s = q,*e = q, p, f;
    *e ++ = 0;
    while(s != e) {
        p = *s ++;
        for(int i=0; i<tk; i++) {
            if(trie[p].nxt[i]) {
                f = trie[p].fail;
                v = trie[p].nxt[i];
                if(p == 0) trie[v].fail = 0;
                else trie[v].fail = trie[f].nxt[i];
                if(f!=-1 && trie[trie[f].nxt[i]].danger) trie[v].danger = 1;  //如果fail节点是危险的，那么本节点也是危险的
                *e ++ = v;
            } else {
                int f = trie[p].fail;
                if(p == 0) trie[p].nxt[i] = 0;
                else trie[p].nxt[i] = trie[f].nxt[i];
            }
        }
    }
}
inline int min(int x,int y) {
    if(x == -1) return y;
    if(y == -1) return x;
    return x>y?y:x;
}
int dp(char *str) {
    memset(f,-1,sizeof(f));
    int i,k,v;
    f[0][0] = 0;
    for(i=1; str[i]; i++) {
        for(int j=0; j<top; j++) {
            if(f[i-1][j] != -1) {
                for(int k=0; k<4; k++) {
                    v = trie[j].nxt[k];
                    if(trie[v].danger == 0) {
                        f[i][v] = min(f[i][v], f[i-1][j] + (k != idx(str[i])));
                    }
                }
            }
        }
    }
    return i-1;
}
int main() {
    int n,ca=1;
    while(EOF != scanf("%d",&n) && n) {
        ini();
        while(n --) {
            scanf("%s",s);
            ins(s);
        }
        ac();

        scanf("%s",str+1);

        int ans = -1,len=dp(str);

        for(int j=0; j<top; j++) {
            if(!trie[j].danger) ans = min(ans,f[len][j]);
        }
        printf("Case %d: %d\n",ca++,ans);
    }
    return 0;
}
