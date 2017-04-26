#include<bits/stdc++.h>

using namespace std;
const int maxn=1e3+5;
char str[maxn];
int N;
///区间dp,dp[i][j]是否为回文串

bool dp[maxn][maxn];

int main(){
    freopen("1.txt","r",stdin);
    scanf("%d",&N);
    while(N--){
        scanf("%s",str);
        memset(dp,0,sizeof(dp));
        int len=strlen(str);
        int maxL=1;
        for(int i=0;i<len;i++){
            dp[i][i]=1;
            if(i<len && str[i]==str[i+1]){
                dp[i][i+1]=1;
                maxL=2;
            }
        }
        for(int l=3;l<=len;l++){
            for(int i=0;i<=len-l;i++){
                if(dp[i+1][i+l-2] && str[i]==str[i+l-1]){
                    dp[i][i+l-1]=1;
                    maxL=l;
                }
            }
        }
        printf("%d\n",maxL);
    }
}
