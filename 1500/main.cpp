#include <bits/stdc++.h>

#define INF 0x3f3f3f3f
using namespace std;

typedef long long LL;
struct Node{
	int f,info,ip;
	LL cost;
	LL totalcost;
};
vector<int> g[2005];
Node node[2005];
int N;



LL getTotalcost(int id);
LL dfs(int id, int start,int last, int info,LL currentcost);


int main(){
    //freopen("1.txt","r",stdin);
	scanf("%d",&N);
	int parent=0;
	for(int i=1;i<=N;i++){
		scanf("%d%d%d%lld",&(node[i].f),&(node[i].info),&(node[i].ip),&(node[i].cost));
		node[i].totalcost=INF;
		if(node[i].f==0){
			parent=i;
		}else{
			g[node[i].f].push_back(i);
		}
	}
	LL res=getTotalcost(parent);
	if(res==INF){
        printf("-1\n");
	}else{
        printf("%lld\n",res);
	}
/*
    for(int i=1;i<=N;i++){
        printf("id=%d  totalcost=%d\n",i,node[i].totalcost);
    }
*/
	return 0;
}

/**
计算使用id号元素使用的代价
*/
LL getTotalcost(int id){

	if(node[id].totalcost!=INF){
		return node[id].totalcost;
	}

	if(g[id].size()==0){
		node[id].totalcost=node[id].cost;
		return node[id].totalcost;
	}
	/**
	*  代价为  凑够info个子孙需要花费的代价  +  自身的代价
	*/
	return dfs(id,0,g[id].size(),node[id].info,node[id].cost);
}
/**
* 空间左闭右开
*/
LL dfs(int id, int start,int last, int info,LL currentcost){
    //printf("id=%d  start=%d  currentcost=%d\n",id,start,currentcost);
	/**
	* 假如info<=0, 说明可以成为当前id的assassinate,可以更新totalcost
	*/
    if(info<=0){
        node[id].totalcost=min(node[id].totalcost,currentcost);
        return node[id].totalcost;
    }

	if(start>=last){
		return INF;
	}
	/**
	*   两种情况,一种是选了当前结点,一种是不选当前结点
	*/
	return min(dfs(id,start+1,last,info,currentcost ), dfs(id,start+1,last,info-node[g[id][start]].ip, currentcost+getTotalcost(g[id][start]) ) );
}
