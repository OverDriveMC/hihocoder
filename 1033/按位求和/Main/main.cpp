#include <bits/stdc++.h>


using namespace std;
typedef  long long LL;

/**
* n为自由位个数,k为进制
* 计算0-(k^n-1)之间各数位的和
*/
LL getsum1(int n,int k){
    LL b=1;
    for(int i=0;i<n;i++){
        b*=k;
    }
    return b*n*(k-1)/2;
}

LL check(int n,int k){
    LL ret=0;
    for(int i=1;i<=n;i++){
        int t=i;
        while(t){
            ret+=t%k;
            t/=k;
        }
    }
    return ret;
}
/**
*prefixsum为公共前缀数字和
*n为自由位长度
*k为进制
*/
LL getsum2(int prefixsum,int n,int k){
    LL B=getsum1(n,k);
    LL C=prefixsum;
    for(int i=0;i<n;i++){
        C*=k;
    }
    return B+C;
}
/**
* 计算带有前缀的0-N的数字和之和
* k为进制
* prefixsum为前缀和
*/
LL getsum3(int prefixsum,LL N,int k){
    cout<<"N:"<<N<<endl;
    ///递归函数,注意边界
    if(N<k){
        cout<<"prefixsum:"<<prefixsum<<endl;
        LL ret=0;
        ///11 12 13
        ///0+(1+1)=2
        ///2+(1+2)=5
        ///5+(1+3)=9
        for(int i=0;i<=N;i++){
            ret+=prefixsum+i;
        }
        return ret;
    }

    LL t=1,tn=N;
    int d=0;

    while(tn>=k){
        d++;
        t*=k;
        tn/=k;
    }
    cout<<"tn:"<<tn<<"   d:"<<d<<"   t:"<<t<<endl;

    LL ret=0;
    for(int i=0;i<tn;i++){
        ret+=getsum2(prefixsum+i,d,k);
    }

    ret+=getsum3(prefixsum+tn,N-t*tn,k);
    return ret;
}

int main()
{
    cout<<getsum3(0,54321,10)<<endl;
    cout<<check(54321,10)<<endl;
    return 0;
}
