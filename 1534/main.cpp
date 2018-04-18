/**
A1 A2 ... Ap |  A(p+1)...A(q) | A(q+1)...A(N)
S1= A1+A2+...+Ap
S2=A(P+1)+...+A(q)
S3=A(q+1)+...+A(N)
每个划分保证|S1-S2| |S2-S3| |S3-S1|不超过1
计算划分的个数
*/

#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

map<LL,LL>mp;
int N;
LL A[100005];
LL sum[100005];

int main(){
    freopen("1.txt","r",stdin);
	scanf("%d",&N);
	memset(sum,0,sizeof(sum));
	for(int i=1;i<=N;i++){
		scanf("%lld",&A[i]);
		sum[i]=sum[i-1]+A[i];
		mp[sum[i]]++;
	}
	LL result=0;
	///第二个划分位置不能在最后一位,这样只能划分出来两个部分,所以sum[n]的个数需要-1
	mp[sum[N]]--;
	//枚举第一个划分位置,第一个划分位置一定要在N-1前面
	for(int i=1;i<N-1;i++){
		///第二个划分位置一定要在第一个划分位置前面,所以每次枚举的当前的前缀和个数都要-1
		///这样便能保证不统计第二个划分位置在第一个划分位置前面
		mp[sum[i] ]--;
		int a=sum[i];
		for(int y=-1;y<=1;y++){
			int b=a+y;
			int z=sum[N]-a-b;
			//printf("%d  %d  %d\n",a,b,z);
			if(abs(z-a)<=1 && abs(z-b)<=1){
				result+=mp[b+a] ;
			}
		}
	}
	printf("%lld\n",result);
	return 0;
}
