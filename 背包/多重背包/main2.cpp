
#include<bits/stdc++.h>

using namespace std;
const int maxn=1e3+5;
int num[100],c[100],d[100];
int dp[maxn];
int N,M,a,b;



int main(){
	//freopen("1.txt","r",stdin);
	while(scanf("%d%d%d%d",&N,&M,&c[0],&d[0]) !=EOF){
		num[0]=0x3f3f3f3f;
		for(int i=1;i<=M;i++){
			scanf("%d%d%d%d",&a,&b,&c[i],&d[i]);
			num[i]=a/b;
		}
		/**
		滚动数组,这个j要倒着写
		*/
		memset(dp,0,sizeof(dp));
		for(int i=0;i<=M;i++){
			for(int j=N;j>=c[i];j--){
			    for(int k=0;k<=num[i];k++){
                    if(j>=k*c[i]){
                        dp[j] = max(dp[j], dp[j- k*c[i] ]+k*d[i] );
                    }else{
                        break;
                    }
			    }
			}
		}
		printf("%d\n",dp[N]);
	}
	return 0;
}
