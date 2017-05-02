#include<bits/stdc++.h>

using namespace std;
///f[len][i]  长度为len以i开头的有多少个
const int maxn=7;
int f[maxn][10];
void init(){
    memset(f,0,sizeof(f));
    f[0][0]=1;
    ///枚举长度
    for(int len=1;len<maxn;len++){
        ///枚举长度为len,以i开头的
        for(int i=0;i<=9;i++){
                ///枚举长度为len-1,以j开头的
            for(int j=0;j<=9;j++){
                if(i!=4  && !(i==6 && j==2)){
                    f[len][i]+=f[len-1][j];
                }
            }
        }
    }
}

int digits[maxn+5];
int solve(int m){
    memset(digits,0,sizeof(digits));
    if(m<0){
        return 0;
    }
    int len=0;
    while(m){
        digits[len++]=m%10;
        m=m/10;
    }
    int result=0;
    ///当i<len时,实际统计的都是以 digits[len-1]开头的数
    for(int i=len;i>0;i--){
        ///从0开始不会重,00x即统计个位的
        for(int j=0;j<digits[i-1];j++){
            if(j!=4 && !(j==2 && digits[i]==6  )){
               // cout<<i<<"  "<<j<<"  "<<f[i][j]<<endl;
                result+=f[i][j];
            }
        }
        ///当i<len之后,这里都是digits[len-1]开头的数
        if(digits[i-1]==4 || (digits[i-1]==2 && digits[i]==6)){
            break;
        }
    }
    return result;
}
int main(){
    //freopen("1.txt","r",stdin);
    int n,m;
    init();
    while(scanf("%d%d",&n,&m)!=EOF){
        if(n==0 && m==0){
            break;
        }
        ///solve计算的是[0,m)的,所以需要+1
        int res=solve(m+1)-solve(n);
        printf("%d\n",res);
    }
    return 0;
}
