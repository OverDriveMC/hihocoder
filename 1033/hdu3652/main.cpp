#include<bits/stdc++.h>

using namespace std;
/**
*dp[i][j][k][l]
*i:长度
*j:以j开头
*k:是否已经包含13
*l:模13余数为l的数的个数
*/
int dp[10][10][2][15];
int power[9];
void init(){
    power[0]=1;
    for(int i=1;i<9;i++){
        power[i]*=10;
    }
    memset(dp,0,sizeof(dp));
    ///枚举长度
   dp[2][1][1][0]=1;
   for(int i=1;i<9;i++){
        ///枚举第i位以j开头
        for(int j=0;j<=9;j++){
            ///枚举第i-1位以x开头
            for(int x=0;x<=9;x++){
                ///枚举余数为l
                for(int l=0;l<=12;l++){
                    ///k==1
                    dp[i][j][1][l]+=dp[i-1][j][1][(l+13-j*power[i-1]%13)%13];
                    if(j==1 && x==3){
                        dp[i][j][1][l]+=dp[i-1][x][0][(l+13-j*power[i-1]%13)%13];
                    }else{
                        ///k==0
                        dp[i][j][0][l]+=dp[i-1][x][0][(l+13-j*power[i-1]%13)%13];
                    }

                }
            }
        }
   }
}

int digits[10];

int solve(int n){
    int len=0;
    memset(digits,0,sizeof(digits));
    while(n){
        digits[len++]=n%10;
        n/=10;
    }
    int res=0;
    int t=0;
    for(int i=len,mod=0;i>0;--i){
        for(int j=0;j<digits[i-1];j++){
            res+=dp[i][j][1][mod];
            if(t || (j==3 && digits[i]==1)){
                res+=dp[i][j][0][mod];
            }
        }
        if(digits[i]==1 && digits[i-1]==3){
            t=1;
        }

        mod=(mod+13-digits[i-1]*power[i-1]%13)%13;
    }
    return res;
}

int main(){
    freopen("1.txt","r",stdin);
    int n;
    init();
    while(scanf("%d",&n)!=EOF){
        int res=solve(n+1);
        printf("%d\n",res);
    }
}


