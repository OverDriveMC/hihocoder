#include<bits/stdc++.h>

using namespace std;
///f[len][i]  ����Ϊlen��i��ͷ���ж��ٸ�
const int maxn=7;
int f[maxn][10];
void init(){
    memset(f,0,sizeof(f));
    f[0][0]=1;
    ///ö�ٳ���
    for(int len=1;len<maxn;len++){
        ///ö�ٳ���Ϊlen,��i��ͷ��
        for(int i=0;i<=9;i++){
                ///ö�ٳ���Ϊlen-1,��j��ͷ��
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
    ///��i<lenʱ,ʵ��ͳ�ƵĶ����� digits[len-1]��ͷ����
    for(int i=len;i>0;i--){
        ///��0��ʼ������,00x��ͳ�Ƹ�λ��
        for(int j=0;j<digits[i-1];j++){
            if(j!=4 && !(j==2 && digits[i]==6  )){
               // cout<<i<<"  "<<j<<"  "<<f[i][j]<<endl;
                result+=f[i][j];
            }
        }
        ///��i<len֮��,���ﶼ��digits[len-1]��ͷ����
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
        ///solve�������[0,m)��,������Ҫ+1
        int res=solve(m+1)-solve(n);
        printf("%d\n",res);
    }
    return 0;
}
