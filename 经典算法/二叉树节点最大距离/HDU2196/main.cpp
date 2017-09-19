#include<bits/stdc++.h>

using namespace std;

const int INF=0x3f3f3f3f;
const int maxn=1e4+5;
struct Node{
	int to;
	int w;
	Node(int to,int w):to(to),w(w){}
};

vector<Node>g[maxn];
/**
dp[i][0]:表示顶点为i的子树的,距顶点i的最长距离
dp[i][1]:表示 ( Tree(i的父节点)-Tree(i)  ) 的最长距离 + i与i的父节点距离
计算所有的dp[i][0]很简单,只要直接做DFS求每个节点到叶子节点的最长距离即可
然后求dp[i][1],可以从父节点递推到子节点
假设节点u有n个子节点,分别是v1,v2,...vn
那么分两种情况,假如v2是u最长距离经过的结点:
1:所以计算v1:
	dp[v1][1]=w(u,v1)+max(dp[u][0]+dp[u][1])
  最大距离可能是u-v2的这条距离,或者是经过u在u的父节点k的距离
2:计算v2,因为v2是u最长距离经过的点,那么不能选择dp[u][0],因为这个保存的就是最长距离,
要选择Tree(u)的第二大距离secondDist:
	dp[v2][1]=w(u,v2)+max(secondDist,dp[u][1])

*/
int dp[maxn][2];
bool vis[maxn];
/**
查找顶点为from的,距顶点from的最长距离
*/
int dfs1(int from){
    ///标记走过了
	vis[from]=true;
	dp[from][0]=0;
	for(int i=0;i<g[from].size();i++){
		int v=g[from][i].to;
		int w=g[from][i].w;
		if(vis[v]){
			continue;
		}
		///查找最大的
		///DFS找子树
		dp[from][0]=max(dp[from][0], w+dfs1(v) );
	}
	return dp[from][0];
}

void dfs2(int from){
	vis[from]=true;
	int max1=0,v1=1,max2=0,v2=1;
	for(int i=0;i<g[from].size();i++){
		int v=g[from][i].to;
		int w=g[from][i].w;
		if(vis[v]){
			continue;
		}
        ///找到顶点from最长的距离和次长的距离
        ///=子树最长的距离  +w(from,v)
		int cost=dp[v][0]+w;
		if(cost>max1){
			max2=max1;
			v2=v1;

			max1=cost;
			v1=v;
		}else if(cost>max2){
			max2=cost;
			v2=v;
		}
	}
	for(int i=0;i<g[from].size();i++){
		int v=g[from][i].to;
		int w=g[from][i].w;

		if(vis[v]){
			continue;
		}
		///假如是最长的,那么使用次长的距离
		if(v==v1){
			dp[v][1]=w+max(dp[from][1],max2);
		}else{
			dp[v][1]=w+max(dp[from][1],max1);
		}

		dfs2(v);
	}


}


int main(){


    freopen("1.txt","r",stdin);
	int n;
	while(scanf("%d",&n)!=EOF){
		for(int i=1;i<=n;i++){
			g[i].clear();
		}
		int to,w;
		for(int i=2;i<=n;i++){
			scanf("%d%d",&to,&w);
			g[i].push_back(Node(to,w));
			g[to].push_back(Node(i,w));
		}
		memset(dp,0,sizeof(dp));
		memset(vis,0,sizeof(vis));
		dfs1(1);

		memset(vis,0,sizeof(vis));
		dfs2(1);
		for(int i=1;i<=n;i++){
			printf("%d\n",max(dp[i][0],dp[i][1]) );
		}
	}
}

