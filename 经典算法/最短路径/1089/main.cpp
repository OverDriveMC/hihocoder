#include<bits/stdc++.h>

using namespace std;
const int inf=0x3f3f3f3f;
const int maxn=105;
int N,M;
int dis[maxn][maxn];


int main(){
   // freopen("1.txt","r",stdin);
	scanf("%d%d",&N,&M);
	memset(dis,inf,sizeof(dis));
	int x,y,length;
	for(int i=0;i<M;i++){
		scanf("%d%d%d",&x,&y,&length);
		dis[x-1][y-1]=min(dis[x-1][y-1],length);
		dis[y-1][x-1]=min(dis[y-1][x-1],length);
	}
	for(int i=0;i<N;i++){
		dis[i][i]=0;
	}
	/**
	*首先，最开始的时候，MinDistance(i, j)——即从第i个点到第j个点的最短路径的长度，拥有一个限制：这条路径不能经过任何节点。
	*限制，变为：这条路径仅允许经过1号节点。
	           对于两个节点i, j，我只需要比较MinDistance(i, j)原来的值和MinDistance(i, 1)+MinDistance(1, j)的值，
			   取较小的一个作为新的MinDistance(i, j)
	 将限制继续放宽——路径仅允许经过1、2号节点:
			对于两个节点i, j，我只需要比较MinDistance(i, j)原来的值和MinDistance(i, 2)+MinDistance(2, j)的值，
			取较小的一个作为新的MinDistance(i, j)，之所以可以这样是因为，原来的MinDistance都是在限制“仅允许经过1号节点”下，求出来的，
			所以新求出来的MinDistance(i, j)也只有可能经过1、2号节点！	
	*每放开一个新的节点k允许作为路径中的节点，就对于任意的i, j，用MinDistance(i, k)+MinDistance(k, j)去更新MinDistance(i, j)，
	*直到1..N号节点都被添加进限制，此时也就等于没有限制了，那么这个时候的MinDistance(i, j)就是我们所想要求的值
	*/
	for(int k=0;k<N;k++){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			}
		}
	}
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			printf("%d ",dis[i][j]);
		}
		printf("\n");
	}
	return 0;
}
