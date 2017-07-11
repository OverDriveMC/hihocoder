#include <bits/stdc++.h>

using namespace std;
typedef long long LL;
const LL mod=1e9+7;

LL l,r;
int k;


struct node{
    ///s记录各数位交错和,n记录满足条件的个数
    ///(因为要计算 digit*10^len需要加多少次,所以需要记录n)
    LL s,n;
};

/**
* 第一维  长度
* 第二维  开头的数字
* 第三维  交错数位和+200
* dp[i][dig][sum]  长度为i的以dig开头的交错数位和为sum的所有数的和
*/
node dp[20][20][400];
///进制数,假如是十进制1 10 100 1000
LL base[20];
///维护每个数的每一位
///例如12345,那么数组为5 4 3 2 1
int bits[20];

///计算[0,n] 数位和为k 的和
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
    ///从长度+1开始,比n的长度大1,并且len+1位数置位0,这样边将第len位和<len位统一起来,方便处理
    node res=dfs(cnt+1,0,true,true,k);
    return res.s;
}

node dfs(int len,int dig,bool begin_zero,bool limit,int sum){
    ///假如长度只有1位,就不需要继续枚举,直接返回结果即可
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
    ///记忆化搜索,查看该值是否已经记录
    ///注意,一定要写limit,
    ///例如 253 在计算 1开头的时候,dp[2][1][xxx]的时候是没有限制的,这个时候就不是-1了
    ///但是在计算2开头的时候后 dp[2][2][xxx]开始有限制了,所以不能直接用之前的结果
    if(!limit &&  dp[len][dig +(begin_zero ?0 :10)][sum+200].n!=-1){
        //cout<<"limit:"<<limit<<"  "<<len<<"  "<<(begin_zero ?0 :10)<<"  "<<sum<<"   "<<dp[len][dig +(begin_zero ?0 :10)][sum+200].n<<endl;
        return dp[len][dig +(begin_zero ?0 :10)][sum+200];
    }
    ///下一位数字的最大值
    int end=limit ?  bits[len-2]  :9;
    /**
    * abcde   sum
    * a-(b-c+d-e) =sum  =>a-b+c-d+e=sum   =>newsum=b-c+d-e=a-sum
    * b-(c-d+e)  =newsum => b-c+d-e=newsum
    * 同时注意,前导0的位置,只有开始位置不是0的时候才可以这么算,
    * 所以要加入begin_zero这个标志位判断
    */
    int newsum=dig-sum;

    for(int i=0;i<=end;i++){
        node tmp;
        if(begin_zero){
            ///如果原来limit有限制,但是 i还没有上升到限制的那个值,那么就相当于没有限制
            tmp=dfs(len-1,i,i==0, limit&& (i==end)   ,sum);
        }else{
            tmp=dfs(len-1,i,false,limit&& (i==end)   ,newsum);
        }
        res.n+=tmp.n;
		///注意,这里必须先tmp.n*dig,然后取模,否则会越界
        res.s=( (res.s+tmp.s)%mod+ (tmp.n * dig %mod) *base[len-1]%mod ) %mod;
    }
    if(!limit){
        dp[len][dig +(begin_zero ?0 :10) ][sum+200]=res;
    }

    return res;
}
