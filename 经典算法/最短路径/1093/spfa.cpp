#include<bits/stdc++.h>
using namespace std;

const int inf=0x3f3f3f3f;
const int maxn=1e5+5;

struct Edge{
	int to,val;
	Edge(int to,int val):to(to),val(val){}
};

vector<Edge>g[maxn];
int vis[maxn],cost[maxn];

int N,M,S,T;

/**
适用于稀疏图
SPFA:用来解决给定一个加权有向图G和源点s,对于图G中的任意一点v,求从s到v的最短路径。
SPFA算法是Bellman-Ford算法的一种队列实现,减少了不必要的冗余计算,它的基本算法和Bellman-Ford一样,并且用
如下方法改进：
   1：不是枚举所有节点,而是通过队列来进行优化,设立一个先进先出的队列用来保存待优化的结点,优化时每次取出队首结点u,
       并且用u点当前的最短路径估计值对离开u点所指向的结点v进行松弛操作,如果v点的最短估计值有所调整,且v点不在当前的
	   队列中,就将v点放入队尾。这样不断从队列中取出结点来进行松弛操作,直至队列空为止。
   2：除了判断队列是否为空来结束循环,还可以通过如下方法：判断有无负环:
			如果某个点进入队列的次数超过V次则存在负环(SPFA无法处理带负环的图)
*/
void spfa();

int main(){
	//freopen("1.txt","r",stdin);
	scanf("%d%d%d%d",&N,&M,&S,&T);
	memset(cost,inf,sizeof(cost));
	memset(vis,0,sizeof(vis));

	int from,to,length;
	for(int i=1;i<=M;i++){
		scanf("%d%d%d",&from,&to,&length);
		g[from].push_back(Edge(to,length));
		g[to].push_back(Edge(from,length));
	}

	spfa();
	printf("%d\n",cost[T]);
	return 0;
}
void spfa(){
	queue<int>q;
	vis[S]=1;
	q.push(S);
	cost[S]=0;
	while(!q.empty()){
		int temp=q.front();
		q.pop();
		for(int i=0;i<g[temp].size();i++){
			if(cost[ g[temp][i].to ] > cost[temp] + g[temp][i].val){
				cost[ g[temp][i].to ] = cost[temp] + g[temp][i].val;
				//存在负权的话，就需要创建一个COUNT数组，当某点的入队次数超过顶点数返回。
				if(vis[g[temp][i].to ]==0){
					q.push(g[temp][i].to);
				}
			}
		}
		vis[temp]=0;
	}
}
