#include<bits/stdc++.h>

using namespace std;
typedef long long LL;

const LL inf=0x3f3f3f3f;
struct Node{
	int f,info,ip;
	LL cost;
};
vector<int>g[2005];
Node node[2005];
int N;

LL dfs(int id){

	if(g[id].size()==0){
		return node[id].cost;
	}

	LL dp[20005];
	memset(dp,inf,sizeof(dp));
/**
* 假如info为0,那么代价为0,自身的代价在返回的时候加上
*/
	dp[0]=0;
	for(int i=0;i<g[id].size();i++){
		///tmp代表子节点的代价
		LL tmp=dfs(g[id][i]);
		for(int j=node[id].info;j>=0;j--){
			///01背包,倒着写循环,该节点选与不选
            dp[j]=min(dp[max(j-node[g[id][i] ].ip,0 )] +tmp  ,dp[j]);
		}
	}
/**
* 自身的cost不能放在循环里面加,会重复加很多次
*/
	return dp[node[id].info ]+node[id].cost;

}

int main(){
    freopen("1.txt","r",stdin);
	scanf("%d",&N);
	int parent=0;
	for(int i=1;i<=N;i++){
		scanf("%d%d%d%lld",&node[i].f,&node[i].info,&node[i].ip,&node[i].cost);
		if(node[i].f==0){
			parent=i;
		}
		g[node[i].f ].push_back(i);
	}
	LL result=dfs(parent);
	if(result>=inf){
        printf("-1\n");
	}else{
	    printf("%lld\n",result);
	}
}
