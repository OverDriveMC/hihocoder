#include<bits/stdc++.h>

using namespace std;

const int maxn=105;
char s[maxn];
int dp[maxn][maxn];

int main(){
    while(scanf("%s",s)!=EOF){
        int len=strlen(s);
        for(int i=0;i<len;i++){
            for(int j=0;j<len;j++){
                dp[i][j]=0x7fffffff;
            }
        }
        for(int i=0;i<len-1;i++){
            dp[i][i]=0;
            if(s[i]==s[i+1]){
                dp[i][i+1]=0;
            }else{
                dp[i][i+1]=1;
            }
        }
        dp[len-1][len-1]=0;

        //区间dp
        for(int l=3;l<=len;l++){
            for(int i=0;i<=len-l;i++){
                int j=i+l-1;
                if(s[i]==s[j]){
                    dp[i][j]=dp[i+1][j-1];
                }else{
                    dp[i][j]=min(min(dp[i+1][j],dp[i][j-1]),dp[i+1][j-1])+1;
                }
            }
        }
        printf("%d\n",dp[0][len-1]);
    }
}
