/**
给定字符串，求它的回文子序列个数。
例如字符串aba中，回文子序列为"a", "a", "aa", "b", "aba"，共5个。
内容相同位置不同的子序列算不同的子序列。

dp[i][j]:从i开始到j截止的回文串个数

dp[i][j]=
	dp[i][j-1]+dp[i+1][j] - dp[i+1][j-1] + dp[i+1][j-1] + 1   s[i]==s[j]
		因为dp[i][j-1]+dp[i+1][j]会多算一次dp[i+1][j-1],但是  每个dp[i+1][j-1]中的字符串都能和s[i] s[j]组成一个新的回文串,同时s[i]s[j]两个也能组成
		一个新的回文串
	dp[i][j-1]+dp[i+1][j] - dp[i+1][j-1]  s[i]!=s[j]
		当s[i]!=s[j]时就正常会多算一次dp[i+1][j-1],不会有额外的回文串添加

区间dp,枚举长度
*/
#include<bits/stdc++.h>

using namespace std;
const int maxn=1005;
const int mod=100007;
int dp[maxn][maxn];
char str[maxn];

int main(){
	int T;
	scanf("%d",&T);
	int cnt=1;
	while(T--){
		scanf("%s",str);
		int slen=strlen(str);
		memset(dp,0,sizeof(dp));
		for(int i=0;i<slen;i++){
			dp[i][i]=1;
		}
		for(int len=2;len<=slen;len++){
			for(int i=0;i<=slen-len;i++){
				//这里的具体能不能等于,可以列出公式之后再推一下
				int j=i+len-1;
				if(str[i]==str[j] ){
					/**
					显然i与j之间所有是回文串的子序列可以用s[i],s[j]包裹成为新的子序列，所以重复部分不需要减去了，
					还需要加上1是因为s[i]s[j]两个单独一起也可以作为一个回文子序列。
					*/
					dp[i][j]=(dp[i][j-1]+dp[i+1][j]+1)%mod;
				}else{
					//注意这里可能减出来负值,所以需要+mod然后在取模
					dp[i][j]=(dp[i][j-1]+dp[i+1][j]-dp[i+1][j-1]+mod)%mod;
				}
				
			}
		}
		printf("Case #%d: %d\n",cnt++,dp[0][slen-1]);
	}
	return 0;
}