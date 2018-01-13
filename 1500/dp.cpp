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
/*
	if(g[id].size()==0){
		return node[id].cost;
	}
*/
	LL dp[20005];
	memset(dp,inf,sizeof(dp));
	dp[0]=0;
	for(int i=0;i<g[id].size();i++){
		LL tmp=dfs(g[id][i]);
		for(int j=node[id].info;j>=0;j--){
			dp[j]=min(dp[max(j-node[g[id][i] ].ip ,0 ) ] +tmp + node[g[id][i]  ].cost ,dp[j]);
		}
	}
	return dp[node[id].info ];

}

int main(){
   // freopen("1.txt","r",stdin);
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
	    printf("%lld\n",result+node[parent].cost);
	}
}
