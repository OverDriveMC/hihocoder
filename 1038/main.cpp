#include<bits/stdc++.h>
using namespace std;

const int maxn=1000;
int w[maxn],v[maxn];
int dp[100005];

int main(){
	//freopen("1.txt","r",stdin);
	int N,M;
	while(scanf("%d%d",&N,&M)!=EOF){
		for(int i=0;i<N;i++){
			scanf("%d%d",&w[i],&v[i]);
		}
		memset(dp,0,sizeof(dp));
		for(int i=0;i<N;i++){
			for(int j=M;j>=w[i];j--){
				dp[j]=max(dp[j],dp[j-w[i]]+v[i]);
			}
		}
		printf("%d\n",dp[M]);
	}
	return 0;
}
