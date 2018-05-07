#include <cstdio>
const int MAXN = 10001,
          nil = 0,
          INF = 0x7fffffff;

# define prompt if(0)

int from[MAXN * MAXN + MAXN],
to[MAXN * MAXN + MAXN],
edgeCnt = 0;

int fstEdge[MAXN],
    nxt[MAXN * MAXN + MAXN],
    cost[MAXN * MAXN + MAXN];

int dis[MAXN],
    pre[MAXN],
    vis[MAXN];

void AddEdge (int From, int To, int Cost) {
  int edgeNum = ++edgeCnt;
  cost[edgeNum] = Cost;
  from[edgeNum] = From;
  to[edgeNum]=To;
  nxt[edgeNum] = fstEdge[From];
  fstEdge[From] = edgeNum;
}

void print (int nodeNum) {
  printf("%d:",nodeNum);
  
  if (dis[nodeNum] == INF) {
    printf("no solution!\n");
    return;
  }

  printf("[%d]\t",dis[nodeNum]);

  for(int i=nodeNum;i!=nil;i=pre[i]) {
    if(i != 1) {
      printf("%d ->", i);
    } else { 
      printf("%d", i);
    }
  }

  printf("\n");
}

int main () {
  freopen("dijkstra.in", "r", stdin);
  freopen("dijkstra.out", "w", stdout);
  int n,m;                      // n:nodeCnt, m:edgeCnt
  prompt printf("input nodeCnt, edgeCnt:");
  scanf("%d%d",&n,&m);
  for (int i = 1; i <= m; i ++) {
    int f,t,c;        // from,to,cost
    prompt printf("input edge[%d] from,to,cost:",i);
    scanf("%d%d%d", &f, &t, &c);
    AddEdge(f, t, c);
    AddEdge(t, f, c);
  }

  for(int i = 2;i <= n;i ++) {
    dis[i]=INF;
  }

  for(int q = 1; q <= n; q ++) {
    int minNode,
        minDis = INF;

    for(int i=1;i <= n;i ++) {
      if (!vis[i] && dis[i]<minDis) {
        minDis=dis[i];minNode=i;
      }
    }

    vis[minNode] = 1;

    for(int i = fstEdge[minNode];i != nil;i = nxt[i]) {
      if(dis[to[i]] > dis[minNode] + cost[i]) {
        pre[to[i]] = minNode;
        dis[to[i]] = dis[minNode] + cost[i];
      }
    }
  }

  prompt printf("Search Start at node[1]:\n");

  for(int i = 2;i <= n; i ++) {
    print(i);
  }

  return 0;
}
