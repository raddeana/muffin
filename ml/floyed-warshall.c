#include<cstdio>

const int MAXN=467,
      INF=0x7fffffff;

int dis[MAXN][MAXN];

int min (int a, int b) {
  return a < b ? a : b;
}

int main () {
    int n,
        m;
    scanf("%d%d",&n,&m);
    // n->nodeCnt m->edgeCnt
    for(int i = 1;i <= n;i ++)
        for(int j = 1; j <= n; j ++)
            if(i == j) {
              dis[i][j] = 0;
            } else { 
              dis[i][j] = INF / 3;
            }
    
    for(int i = 1; i <= m; i ++) {
        int from,
            to,
            cost;
        
        scanf("%d%d%d",&from,&to,&cost);
        dis[from][to]=min(dis[from][to],cost);
        dis[to][from]=dis[from][to];
    }
    
    for(int k=1;k<=n;k++) {
        for(int i=1;i<=n;i++) {
            for(int j=1;j<=n;j++) {
                dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
            }
        }
    }
    
    for (int i=1;i<=n;i++) {
        for (int j = 1; j <= n;j ++) {
            printf("dis[%d][%d]=%d ",i,j,dis[i][j]);
        }
        
        printf("\n");
    }
    
    return 0;
}
