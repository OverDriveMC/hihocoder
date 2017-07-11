#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
const LL mod=1e9+7;

LL l,r;
int k;


struct node{
    ///s��¼����λ�����,n��¼���������ĸ���
    ///(��ΪҪ���� digit*10^len��Ҫ�Ӷ��ٴ�,������Ҫ��¼n)
    LL s,n;
};

/**
* ��һά  ����
* �ڶ�ά  ��ͷ������
* ����ά  ������λ��+200
* dp[i][dig][sum]  ����Ϊi����dig��ͷ�Ľ�����λ��Ϊsum���������ĺ�
*/
node dp[20][20][400];
///������,������ʮ����1 10 100 1000
LL base[20];
///ά��ÿ������ÿһλ
///����12345,��ô����Ϊ5 4 3 2 1
int bits[20];

///����[0,n] ��λ��Ϊk �ĺ�
LL solve(LL n);
node dfs(int len,int dig,bool begin_zero,bool limit,int sum);
void init();

LL check(){
    LL res=0;
    for(LL i=l;i<=r;i++){
        LL d=i;
        int t=1;
        int sum=0;
        while(d>0){
            sum+=d%10 *t;
            d/=10;
            t=-t;
        }
        sum=sum*(-t);
        if(sum==k){
            res+=i;
        }
    }
    printf("check:%lld\n",(res%mod) );
    return res;
}

int main()
{
    //freopen("1.txt","r",stdin);
    while(scanf("%lld%lld%d",&l,&r,&k)!=EOF){
       // check();
        init();
        LL res=(solve(r)-solve(l-1) +mod) % mod;
        printf("%lld\n",res);
    }
    return 0;
}
void init(){
    base[0]=1;
    for(int i=1;i<20;i++){
        base[i]=base[i-1]*10%mod;
    }
    for(int i=0;i<20;i++){
        for(int j=0;j<20;j++){
            for(int k=0;k<400;k++){
                dp[i][j][k].n=-1;
                dp[i][j][k].s=0;
            }
        }
    }
}

LL solve(LL n){
    if(n<k || n<0){
        return 0;
    }
    int cnt=0;
    LL temp=n;
    while(temp>0){
        bits[cnt++]=temp%10;
        temp/=10;
    }
    ///�ӳ���+1��ʼ,��n�ĳ��ȴ�1,����len+1λ����λ0,�����߽���lenλ��<lenλͳһ����,���㴦��
    node res=dfs(cnt+1,0,true,true,k);
    return res.s;
}

node dfs(int len,int dig,bool begin_zero,bool limit,int sum){
    ///���糤��ֻ��1λ,�Ͳ���Ҫ����ö��,ֱ�ӷ��ؽ������
    node res;
    res.n=0;
    res.s=0;
    if( len==1  ){
        if(dig==sum){
            res.n=1;
            res.s=dig;
        }
        return res;
    }
    ///���仯����,�鿴��ֵ�Ƿ��Ѿ���¼
    ///ע��,һ��Ҫдlimit,
    ///���� 253 �ڼ��� 1��ͷ��ʱ��,dp[2][1][xxx]��ʱ����û�����Ƶ�,���ʱ��Ͳ���-1��
    ///�����ڼ���2��ͷ��ʱ��� dp[2][2][xxx]��ʼ��������,���Բ���ֱ����֮ǰ�Ľ��
    if(!limit &&  dp[len][dig +(begin_zero ?0 :10)][sum+200].n!=-1){
        //cout<<"limit:"<<limit<<"  "<<len<<"  "<<(begin_zero ?0 :10)<<"  "<<sum<<"   "<<dp[len][dig +(begin_zero ?0 :10)][sum+200].n<<endl;
        return dp[len][dig +(begin_zero ?0 :10)][sum+200];
    }
    ///��һλ���ֵ����ֵ
    int end=limit ?  bits[len-2]  :9;
    /**
    * abcde   sum
    * a-(b-c+d-e) =sum  =>a-b+c-d+e=sum   =>newsum=b-c+d-e=a-sum
    * b-(c-d+e)  =newsum => b-c+d-e=newsum
    * ͬʱע��,ǰ��0��λ��,ֻ�п�ʼλ�ò���0��ʱ��ſ�����ô��,
    * ����Ҫ����begin_zero�����־λ�ж�
    */
    int newsum=dig-sum;

    for(int i=0;i<=end;i++){
        node tmp;
        if(begin_zero){
            ///���ԭ��limit������,���� i��û�����������Ƶ��Ǹ�ֵ,��ô���൱��û������
            tmp=dfs(len-1,i,i==0, limit&& (i==end)   ,sum);
        }else{
            tmp=dfs(len-1,i,false,limit&& (i==end)   ,newsum);
        }
        res.n+=tmp.n;
		///ע��,���������tmp.n*dig,Ȼ��ȡģ,�����Խ��
        res.s=( (res.s+tmp.s)%mod+ (tmp.n * dig %mod) *base[len-1]%mod ) %mod;
    }
    if(!limit){
        dp[len][dig +(begin_zero ?0 :10) ][sum+200]=res;
    }

    return res;
}
