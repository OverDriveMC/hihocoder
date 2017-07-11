#include <bits/stdc++.h>

using namespace std;

#define Debug

///魔法单位的数目最大为N
const int N=1e5+5;
typedef long long LL;
///a初始法力值,m最大法力上限,r每秒钟法力回复
int a[N],m[N],r[N],bit2[N<<2];


/**
* 增加的时间间隔为 +
* 删除的时间间隔为 -
* b里面维护了所有的增加的时间间隔
*/
vector<int>Lt[N],Rt[N], op[N], b;

///维护遭受收割的时间序列
map<int,int>s;
LL bit[N<<2];
int lowbit(int x){
    return x&(-x);
}

void add(int x,int v,int n){
    for(; x<=n; bit[x] +=v,x+=lowbit(x) );
}
LL sum(int x){
    LL res=0;
    for(;x;res+=bit[x],x-=lowbit(x));
    return res;
}

void Add(int x,int v,int n){
    for(;x<=n;bit2[x]+=v,x+=lowbit(x));
}
int Sum(int x){
    int res=0;
    for(;x;res+=bit2[x],x-=lowbit(x));
    return res;
}




int main()
{

    freopen("1.txt","r",stdin);
    ///q操作的数目
    int n,q;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",a+i,m+i,r+i);
    }
    scanf("%d",&q);
    for(int l,r,t;q--;){
        scanf("%d%d%d",&t,&l,&r);
        ///t 时刻对 [l,r]区间内的魔法单位进行收割操作
        Lt[l].push_back(t);
        Rt[r].push_back(t);
    }
    s[0]++;

    LL ans=0;

/**
*T:魔法单位i法力回满所需时间
*对于每个魔法单位我们只要知道其遭遇收割的时间间隔(以下简称"时间间隔")中,
*大于等于T的时间间隔的个数以及小于T的时间间隔的总和
*对每个魔法单位，我们可以用map来维护其遭受收割的时间序列，用树状数组来维护时间间隔之和与时间间隔的数量之和。
*
*对每个魔法单位都按上述方式做一遍,时间上不能承受。同时应当注意到相邻魔法单位的时间序列是有联系的,可以动态维护
*假设现在已经维护好了第i个魔法单位的时间序列和时间间隔,在此基础上去掉所有以i为区间右端点的收割时刻,
*再插入所有以i+1为区间左端点的收割时刻，就得到了第i+1个魔法单位的时间序列。
(假如不是以i结尾,那么对i更新时的肯定包含了对i+1的更新,同时加上以i+1为区间的开始的,就是所有涉及i+1的操作)
*删除一个时刻ti意味着删除了两个时间间隔ti − ti−1和ti+1−ti,新增了一个时间间隔ti+1 − ti−1;插入一个时刻ti的作用恰好相反。
*/

/**
*对每个魔法单位,先维护出以其为左端点和右端点的收割操作.然后从左到右动态维护各个魔法单位的时间序列,
*同时记录下相应的时间间隔的插入与删除操作.
*对涉及到的所有时间间隔进行离散化.然后对每个魔法单位,先将其对应的(或称"贡献的")时间间隔的插入与删除操作更新到树状数组中.
*最后查询两类时间间隔贡献的法力加到答案中
*/
    for(int i=1;i<=n;i++){
        ///假设现在已经维护好了第i-1个魔法单位的时间序列和时间间隔,在此基础上去掉所有以i为区间右端点的收割时刻,
        for(auto & t  : Rt[i-1]){

#ifdef Debug
            cout<<"in RT loop:t="<<t<<"   "<<s[t]<<endl;
#endif // Debug
            if(--s[t]) continue;
            ///返回s中第一个key值大于或等于t值的迭代器<>
            auto p=s.lower_bound(t);
#ifdef Debug
            cout<<"p:"<<p->first<<"  "<<p->second<<endl;
#endif // Debug
            int pre,suc;
            pre=(--p)->first;
            ++p;
            op[i].push_back(pre-t);
#ifdef Debug
            cout<<"pre:"<<pre<<"  "<<pre-t<<endl;
#endif // Debug
            if(++p!=s.end()){
                suc=p->first;
                op[i].push_back(t-suc);
                op[i].push_back(suc-pre);
                b.push_back(suc-pre);
#ifdef Debug
                cout<<"judge suc:"<<suc<<"  "<<t-suc<<"   "<<suc-pre<<endl;
#endif // Debug
            }
            s.erase(--p);
        }
        ///再插入所有以i+1为区间左端点的收割时刻，就得到了第i+1个魔法单位的时间序列。
        for(auto & t : Lt[i]){
#ifdef Debug
            cout<<"in Lt loop:t="<<t<<endl;
            cout<<"s[t]:"<<s[t]<<endl;
#endif // Debug
            ///假如当前的s[t]不为0,说明前面已经计算过t时刻的时间间隔,t时刻重复出现,直接continue
            if(s[t]++) continue;
            auto p=s.lower_bound(t);
#ifdef Debug
            cout<<"p:"<<p->first<<"  "<<p->second<<endl;
#endif // Debug
            int pre,suc;
            pre=(--p)->first;
            ++p;
            op[i].push_back(t-pre);
            b.push_back(t-pre);
            //cout<<s.size()<<endl;
#ifdef Debug
            cout<<"pre:"<<pre<<"  t-pre:"<<t-pre<<endl;
#endif // Debug
            if(++p!=s.end()){
                suc=p->first;
                op[i].push_back(suc-t);
                op[i].push_back(pre-suc);
                b.push_back(suc-t);
#ifdef Debug
                cout<<"judge:"<<suc<<"  suc-t:"<<suc-t<<"    pre-suc:"<<pre-suc<<endl;
#endif // Debug
            }
        }
        ///假如0时刻毁灭者开始吸收魔法值
        if(s[0]>1) ans+=a[i];
        else{
            auto p=s.begin();
            if(++p!=s.end()){
                int t=p->first;
                ///初始法力值可能不为零
                ///毁灭者在每个魔法单位第一次吸收的法力的实际值和假设初始法力为零的情况之差
                ans+=min(a[i]+(LL)t*r[i],(LL)m[i]  ) - min((LL)t*r[i],(LL)m[i] );
            }
        }

    }

    sort(b.begin(),b.end());
    auto e=unique(b.begin(),b.end());
    int size=e-b.begin();

#ifdef Debug
    cout<<"b:"<<endl;
    for(vector<int>::iterator start=b.begin();start!=e;++start){
        cout<<*start<<"  ";
    }
    cout<<endl;
#endif // Debug

    for(int i=1;i<=n;i++){
#ifdef Debug
        cout<<"op[i]:"<<i<<endl;
        for(vector<int>::iterator begin=op[i].begin();begin!=op[i].end();++begin){
            cout<<*begin<<"  ";
        }
        cout<<endl;
#endif // Debug
        for(int &x : op[i]){
            ///被查序列中第一个大于查找值的指针
            int id=upper_bound(b.begin(),e,abs(x))-b.begin();

#ifdef Debug
            cout<<"id:"<<id<<"   x:"<<x<<endl;
#endif // Debug
            add(id,x,size);
            if(x<0){
                Add(id,-1,size);
            }else{
                Add(id,1,size);
            }
        }

        if(m[i]==0 || r[i]==0)
            continue;
        ///魔法单位i法力回满所需时间
        int t=(m[i]-1)/r[i]+1;
        int id=lower_bound(b.begin(),e,t)-b.begin();
        ///大于等于T的时间间隔的个数
        ans+=(LL)(Sum(size)-Sum(id))*m[i];
        ///小于T的时间间隔的总和
        ans+=sum(id)*r[i];

#ifdef Debug
        cout<<"id:"<<id<<endl;
        cout<<"cnt1:"<<(LL)(Sum(size)-Sum(id))<<endl;
        cout<<"cnt2:"<<sum(id)<<endl;
#endif // Debug
    }

    printf("%lld\n",ans);
    return 0;
}
