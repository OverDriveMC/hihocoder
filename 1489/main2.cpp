#include<bits/stdc++.h>

using namespace std;

int main(){
	int P,Q,N;
	scanf("%d%d%d",&P,&Q,&N);
	double f[101];
	f[100]=1;
	for(int i=99;i>=0;i--){
		int j=min(i+Q,100);
		/**
		* 计算出 起始概率为0-100的期望保存在f中
		* f[i]的期望为:
		*       当前以i%概率直接获得传奇物品
		*       以(1-i%)概率没有获得传奇物品,然后以j%的概率获得传奇物品(多了一次)
		*/
		f[i]= i*0.01 + (1-i*0.01)*(f[j]+1);
	}
	double res=0;
	int index= min(N,8);
	int pow=1;
	for(int i=1;i<=index;i++){
        ///P为每次的起始概率
		res+=f[P];
		P/=2;
	}
	res+=(N-index)*f[0];
	printf("%.2lf\n",res);
	return 0;
}
