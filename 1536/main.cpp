#include<bits/stdc++.h>

using namespace std;
const int maxn=5005;

pair<int,int>P[maxn];
int A[maxn];
int T,N,R;

int dp[maxn][maxn];

int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&N,&R);
        for(int i=1;i<=N;i++){
            scanf("%d",&A[i]);
        }
        int temp;
        for(int i=1;i<=N;i++){
            scanf("%d",&temp);
            P[i]=make_pair(A[i],temp);
        }
        sort(P+1,P+N+1);
        memset(dp,0,sizeof(dp));
        dp[1][1]=P[1].second;
        int ans=P[N].second;
        for(int i=2;i<=N;i++){
            /**
            *  直接放到前一个最大的旁边。于是作用就是次大的失效,最大的生效
            */
            for(int j=1;j<=i;j++){
                dp[i][j]=max(dp[i][j],dp[i-1][j]-P[i-1].second+P[i].second);
            }
			/**
			*	考虑最大的和次大的"同时"生效。于是,可以设置dp状态为dp[i][j]。表示放第i大数时,有效数字是指
			*被统计在答案中,并且无效数字均在最大数字(第i个数的右边),且未被统计。于是新加的数Ai可以考虑为与Ai-1相隔了
			*r个数字
			*每r+1个数字选1个,j是被统计在答案中的数字,不是选了几个数字
			*/
            for(int j=0;j<=i;j++){
                int left=max(0,i-R-1-j );
                int right=min(i,left+R+1);
                dp[i][right]=max(dp[i][right],dp[i-1][left] + P[i].second);
            }
            for(int j=1;j<=i;j++){
                dp[i][j]=max(dp[i][j],dp[i][j-1]);
            }

        }
        ans=max(ans,dp[N][N]);
        printf("%d\n",ans);
    }
    return 0;
}
