/**
一共有n个面团 和m种不同的材料以及食品
每种食品有 ai种材料, 需要花费bi种材料以及ci个面团才能做成,每种售价di

还有一种食品不需要材料,只需要c0个面团 每种售价d0
求最大利润

输入:  n m c0 d0
ai bi ci di
Examples
input
10 2 2 1
7 3 2 100
12 3 1 10
output
241
input
100 1 25 50
15 5 20 10
output
200

The first line contains 4 integers n, m, c0 and d0 (1≤n≤1000, 1≤m≤10, 1≤c0,d0≤100).
 Each of the following m lines contains 4 integers. The i-th line contains numbers ai, bi, ci and di (1 ≤ ai, bi, ci, di ≤ 100).
*/

#include<bits/stdc++.h>

using namespace std;
const int maxn=1e3+5;
int num[100],c[100],d[100];
int dp[100][maxn];
int N,M,a,b;

/**

dp[i][j]=max(dp[i-1][j- c[i] *k ] +k *d[i] )   0<=k<=num[i]
*/

int main(){
	//freopen("1.txt","r",stdin);
	while(scanf("%d%d%d%d",&N,&M,&c[0],&d[0]) !=EOF){
		num[0]=0x3f3f3f3f;
		for(int i=1;i<=M;i++){
			scanf("%d%d%d%d",&a,&b,&c[i],&d[i]);
			num[i]=a/b;
		}
		memset(dp,0,sizeof(dp));
		for(int i=0;i<=N;i++){
			if(c[0]<=i){
				dp[0][i]=i/c[0] * d[0];
			}
		}
		for(int i=1;i<=M;i++){
			for(int j=0;j<=N;j++){
				/**
				一开始初始化为dp[i-1][j]
				即第i件物品一次都不选
				*/
                dp[i][j] =dp[i-1][j];
			    for(int k=0;k<=num[i];k++){
                    if(j>=k*c[i]){
						/**
						之后开始枚举,第i件物品选多少次,从0-num[i]次
						注意每次比较的是dp[i][j](因为每次可能dp[i][j]已经更新为最大的,一开始初始化为dp[i-1][j])
						所以包含了所有的0-num[j]的情况的比较
						
						同时是dp[i-1][ j- k*c[i]] +k*d[i]
						直接枚举的是第i个选k个,并不需要之间的dp[i][~]的结果
						*/
                        dp[i][j] = max(dp[i][j], dp[i-1][j- k*c[i] ]+k*d[i] );
                    }else{
                        break;
                    }
			    }
			}
		}
/*
		for(int i=0;i<=M;i++){
            for(int j=0;j<=N;j++){
                cout<<i<<"  "<<j<<"  "<<dp[i][j]<<endl;
            }
		}
*/
		printf("%d\n",dp[M][N]);
	}
	return 0;
}
