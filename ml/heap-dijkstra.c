#include<cstdio>
#include<queue>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100 + 5,
          maxm = maxn * maxn;

struct HeapDijkstra {

    // node for heap
    struct Qnode{
      int dis,index;
    };
    // cmp for priority_queue
    struct cmp {
      bool operator () (Qnode A,Qnode B) {
        return A.dis > B.dis;
      }
    };

    // nodeCnt edgeCnt
    int n, m;
    
    // edges
    int from[maxm],
        to[maxm],
        cost[maxm],
        nxt[maxm];
    
    // nodes
    int fst[maxn],
        dis[maxn];
    
    // init dij
    void init (int n) {
        // clear fst
        memset(fst,0,sizeof(int)*(n+1));
        this->n = n;
        m=0;
    }
    
    // add an edge
    void addedge (int f, int t, int c){
        int ne=++m;
        from[ne] = f;
        to[ne] = t;
        cost[ne] = c;
        nxt[ne] = fst[f];
        fst[f] = ne;
    }

    void Dijkstra(int s) {
        memset(dis,0x7f, sizeof(int)*(n+1));           // set INF
        dis[s] = 0;
        priority_queue<Qnode,vector<Qnode>,cmp>heap;
        heap.push((Qnode){dis[s],s});                 // start push
        
        // heap Dij
        for (int i = 1;i <= n;i ++) {
            int x=heap.top().index;
            heap.pop();
            
            for(int j=fst[x];j;j=nxt[j]){//out edge
                int tn=to[j];
                if(dis[tn]>dis[x]+cost[j]){//refresh
                    dis[tn]=dis[x]+cost[j];
                    heap.push((Qnode){dis[tn],tn});
                }
            }
        }
    }
} dij;

// for question
int main () {
    int N,
        M;
    // for all query
    while(scanf("%d%d",&N,&M) &&N &&M) {
        // init dij
        dij.init(N);
        // input edges
        for(int i=1;i<=M;i++){
            int A,B,C;scanf("%d%d%d",&A,&B,&C);
            dij.addedge(A,B,C);dij.addedge(B,A,C);
        }
        
        dij.Dijkstra(1);            // solve shortest path
        printf("%d\n",dij.dis[N]);  // output ans
    }
    
    return 0;
}
