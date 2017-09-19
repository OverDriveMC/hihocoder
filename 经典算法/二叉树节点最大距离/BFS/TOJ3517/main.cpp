#include<bits/stdc++.h>

using namespace std;
const int maxn=2048;

struct Edge{
    int to;
    int len;
    Edge(int to,int len):to(to),len(len){}
};
vector<Edge>G[maxn];
bool vis[maxn];
int mincost[maxn];

const int INF=0x7fffffff;
int n;


/**
* 求from到其它所有点的距离(最短路)中的最大值和 距离最大的点
* first 点   second 值
*/
pair<int,int>dijkstra(int from){
    fill(mincost,mincost+n+1,INF);
    memset(vis,0,sizeof(vis));
    mincost[from]=0;
    priority_queue<int>q;
    q.push(from);
    int maxLen=0;
    int index=from;
    while(!q.empty()){
        int top=q.top();
        vis[top]=1;
        q.pop();
        if(mincost[top] >maxLen){
            index=top;
            maxLen=mincost[top];
        }
        for(int i=0;i<G[top].size();i++){
            if(vis[G[top][i].to ]){
                continue;
            }
            ///松弛操作
            mincost[ G[top][i].to ] =min(mincost[ G[top][i].to ],
                        mincost[top]+G[top][i].len   );
            q.push(G[top][i].to);
        }

    }
    return make_pair(index,maxLen);
}


int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            G[i].clear();
        }
        int from,to,len;
        for(int i=1;i<n;i++){
            scanf("%d%d%d",&from,&to,&len);
            G[from].push_back(Edge(to,len));
            G[to].push_back(Edge(from,len));
        }
        pair<int,int>a=dijkstra(1);
        printf("%d\n",dijkstra(a.first).second);
    }
    return 0;
}
