/**
N种奖励  M种抽奖券
每种奖励需要的抽奖券   奖励金额


输出：
获取的最高金额


样例输入
5 1000
144 990
487 436
210 673
567 58
1056 897
样例输出
5940

*/

#include<bits/stdc++.h>

using namespace std;



const int maxn=2e5+5;
int a[maxn],val[maxn];
int dp[maxn];
int N,M;
int main(){
    freopen("1.txt","r",stdin);
    scanf("%d%d",&N,&M);
    for(int i=0;i<N;i++){
        scanf("%d%d",&a[i],&val[i]);
    }
    memset(dp,0,sizeof(dp));
    for(int i=0;i<N;i++){
        for(int j=a[i];j<=M;j++){
            dp[j] =max(dp[j],dp[j-a[i]]+val[i] );
        }
    }
    printf("%d\n",dp[M]);

    return 0;
}
