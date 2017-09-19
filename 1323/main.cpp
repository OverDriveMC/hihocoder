#include <bits/stdc++.h>

using namespace std;

const int maxn=105;
int dp[maxn][maxn];
char s[maxn];

//假设f[s[1...n]]表示把长度为n的字符串s改写成回文串需要的操作
int solve(int start,int  last){
    if(start>last){
        return 0x7fffffff;
    }
    if(start==last){
        return 0;
    }
    if(dp[start][last]!=-1){
        return dp[start][last];
    }
    ///假如s[start]==s[last],那么f(s[start...last])=f(s[start+1...last-1])
    if(s[start]==s[last]){
        return dp[start][last]=solve(start+1,last-1);
    }else{
        ///否则,是以下三种情况的最小值
        dp[start+1][last]=solve(start+1,last);
        dp[start][last-1]=solve(start,last-1);
        dp[start+1][last-1]=solve(start+1,last-1);
        //cout<<dp[start+1][last]<<"   "<<dp[start][last-1]<<"  "<<dp[start+1][last-1]<<endl;
        return min(min(dp[start+1][last],dp[start][last-1]),dp[start+1][last-1])+1;
    }

}

int main(){
   // freopen("1.txt","r",stdin);
    while(scanf("%s",s)!=EOF){
        memset(dp,-1,sizeof(dp));
        int len=strlen(s);
        ///初始化相邻相等的情况
        ///否则如AA
        ///solve(0,1)=solve(1,0),所以需要初始化
        for(int i=0;i<len-1;i++){
            if(s[i]==s[i+1]){
                dp[i][i+1]=0;
            }
        }
        int result=solve(0,len-1);
        printf("%d\n",result);
    }
    return 0;
}
