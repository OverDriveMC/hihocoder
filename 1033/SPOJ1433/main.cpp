#include <bits/stdc++.h>

using namespace std;

typedef  long long LL;
/**
* n为自由位个数
* k为总位数(k>=n>=1)
*/
LL getsum1(int n,int k){
    ///偶数
    if(k%2==0){
        if(n%2==0) return 0;
        else{
            LL d=-45;
            for(int i=0;i<n-1;i++){
                d*=10;
            }
            return d;
        }
    }else{
        LL d=-1;
        for(int i=0;i<n;i++){
            d*=10;
        }
        return d/2;
    }
}

LL check(int n){
    LL ret=0;
    int t=1,a[10];
    for(int i=1;i<=n;i++){
        int r=0,p=i;
        while(p>0){
            a[r++]=p%10;
            p/=10;
        }
        for(int j=r-1;j>=0;j--){
            ret+=a[j]*t;
            t=-t;
        }
    }
    return ret;
}
/**
*prefix为前缀,n为自由位个数(n>=1,prefix>=1)
*/
LL getsum2(LL prefix,int n){
    int d=0,t=1;
    LL p=prefix,presum=0;
    while(p>0){
        presum+=(p%10)*t;
        p/=10;
        d++;
        t=-t;
    }
    presum*=-t;
    for(int i=0;i<n;i++){
        presum*=10;
    }
    LL ret=getsum1(n,n+d);
    if((d+n)%2==0){
        ret+=presum;
    }
    return ret;
}
///对原问题进行求和[1,n] n>=1
LL getsum3(LL n){
    if(n<10){
        LL ret=0;
        for(int i=0;i<=n;i++){
            if(i%2==0){
                ret-=i;
            }else{
                ret+=i;
            }
        }
        return ret;
    }

    LL tn=n,p=1;
    int d=0;
    while(tn>0){
        d++;
        tn/=10;
    }
    for(int i=1;i<d;i++){
        p*=10;
    }

    LL prefix=0,ret=5;
    for(int j=1;j<d-1;j++){
        for(int i=1;i<=9;i++){
            ret-=getsum2(i,j);
        }
    }
    tn=n;
    while(d>1){
        for(int i=0;i<tn/p;i++){
            if(prefix!=0){
                ret-=getsum2(prefix,d-1);
            }
            prefix++;
        }
        tn%=p;
        p/=10;
        d--;
        prefix*=10;
    }

    cout<<"tn:"<<tn<<"  prefix:"<<prefix<<"  p:"<<p<<endl;
    int a[20],t=-1;
    for(int i=0;i<=tn;i++){
        LL p=prefix+i;
        int r=0;
        while(p>0){
            a[r++]=p%10;
            p/=10;
        }
        for(int j=r-1;j>=0;j--){
            ret+=a[j]*t;
            t=-t;
        }
    }

    return ret;



}


int main()
{
    freopen("1.txt","r",stdin);
    LL n;
    while(true){
        scanf("%lld",&n);
        if(n==0){
            return 0;
        }else{
            LL res=getsum3(n);
            printf("%lld\n",res);
        }
    }
    return 0;
}
