#include<cstdio>
#include<queue>

using namespace std;

#define prompt if(0)

const int MAXN = 10001,
          MAXM = MAXN * MAXN + MAXN,
          NIL = 0,
          INF = 0x7fffffff;

int from[MAXM],
    to[MAXM],
    cost[MAXM],
    nxt[MAXM],
    ecnt=0;

int dis[MAXN],
    pre[MAXN],
    fste[MAXN];

bool exist[MAXN];

void addedge (int f,int t,int c) {
    int ne=++ecnt;
    from[ne]=f;to[ne]=t;cost[ne]=c;
    nxt[ne]=fste[from[ne]];
    fste[from[ne]]=ne;
}

void print (int n) {
    printf("[%d]->",n);
    n = pre[n];
    
    while(n!=1 && n!=0) {
        printf("%d->", n);
        n = pre[n];
    }

    if(n) {
      printf("%d\n", n);
    } else {
      printf("no answer!\n", n);
    }
}

queue<int>que;

int main () {
    freopen("SPFA.in", "r", stdin);
    freopen("SPFA.out", "w", stdout);
    prompt printf("input nodeCnt & edgeCnt:");
    
    int n,
        m;
    
    scanf("%d%d",&n,&m);
    for(int i = 1;i <= m; i++) {
        prompt printf("input edge [%d] form to cost:",i);
        int f,
            t,
            c;
        
        scanf("%d%d%d",&f,&t,&c);
        addedge(f,t,c);
        addedge(t,f,c);
    }
    
    for(int i = 2; i <= n; i ++) {
      dis[i]=INF;
    }
    
    exist[1] = 1;
    que.push(1);
    
    while (!que.empty()) {
        int nw = que.front();
        que.pop();
        
        exist[nw] = 0;
        
        for(int i = fste[nw]; i != NIL; i = nxt[i]) {
            if(dis[to[i]] > dis[nw] + cost[i]) {
                dis[to[i]] = dis[nw] + cost[i];
                pre[to[i]] = nw;
                
                if (!exist[to[i]]) {
                    que.push(to[i]);
                    exist[to[i]] = 1;
                }
            }
        }
    }
    
    for (int i = 2; i <= n; i ++) {
        print(i);
    }
    
    return 0;
}
