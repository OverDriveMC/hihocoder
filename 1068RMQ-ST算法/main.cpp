/**
题目描述：假设整个货架上从左到右摆放了N种商品,并且依次标号为1到N,每次小Hi都给出一段区间[L,R],小Ho要做的是选出标号在这个区间内所有商品质量最轻的一种,
并且告诉小Hi这个商品的重量
输入：
第一行为N,
第2行为N个整数,描述商品重量,第i个整数表示标号为i的商品重量weight_i
第三行为Q:表示小Hi总共询问的次数
接下来Q行,每行代表一个询问[L,R]
对于100%的数据，满足N<=10^6，Q<=10^6, 1<=Li<=Ri<=N，0<weight_i<=10^4。
输出：
标号在区间[Li, Ri]中的所有商品中重量最轻的商品的重量。
样例输入
10
7334 1556 8286 1640 2699 4807 8068 981 4120 2179
5
3 4
2 8
2 4
6 8
7 10
样例输出
1640
981
1556
981
981
*/



/**
RMQ-ST(区间最值查询的在线算法)
利用线段树减少复杂度——预先计算一些区间的最小值,然后把每个询问都拆成若干个计算了最小值的区间,并且统计这些区间的最小值的最小值,从而得出答案
那么其实可以将区间这样规定——统计所有长度为2的非负整数次幂的区间

用pre_calc[L,len]表示左边界为L,长度为len的区间中的最小值
那么对于一个询问[Li,Ri],只要找到小于这个区间长度的最大的2的非负整数次幂——T,那么
这个区间中的最小值就是 min{pre_calc[Li,T],pre_calc[Ri-T+1, T]}   (区间可能有重叠)

对于所有的i满足1<=i<=N, pre_calc[i,1]就是代表标号为i的物品重量为weight_i, 那么对于所有的i,j满足
1<=i<=N, 1<x^j<=N,  pre_calc[i,2^j] = min{pre_calc[i,2^(j-1)],pre_calc[ i+ 2^(j-1) , 2^(j-1)] }
即 [i,i+2^j-1]  ===========>[i,i+2^(j-1)-1]    [i+2^(j-1) ,i+2^(j-1)+2^(j-1)-1 ======i+2^j-1   ]
在记录pre_calc的时候没必要直接存储pre_calc[i,2^j],这样空间会很大,直接存储pre_calc[i,j]即可
*/

#include<bits/stdc++.h>

using namespace std;
const int maxn=1e6+5;
int N,Q,L,R;
int pre_calc[maxn][20];

void RMQ_ST(){
	int l=(int)(log(N)/log(2))+1;
	//第2维j代表2^j
	for(int j=1;j<=l;j++){
		for(int i=1;i+(1<<j)-1 <=N;i++){
			// [i, i+2^j-1]  ======> [i, i+2^(j-1)-1] , [i+2^(j-1) , i+2^(j-1)+2^(j-1)-1]
			pre_calc[i][j] = min( pre_calc[i][j-1], pre_calc[i+ (1<<j-1) ][ j-1]  );
		}
	}
}

int main(){
    //freopen("1.txt","r",stdin);
	while(scanf("%d",&N)!=EOF ){
		for(int i=1;i<=N;i++){
			scanf("%d",&pre_calc[i][0]);
		}
		RMQ_ST();
		scanf("%d",&Q);
		for(int i=1;i<=Q;i++){
			scanf("%d%d",&L,&R);
			//找到小于区间长度的最大的2的非负整数次幂
			int mi=(int)(log(R-L+1) /log(2.0)   );
			printf("%d\n", min(pre_calc[L][mi] ,pre_calc[R-( 1<<mi  )+1  ][mi] ) );

		}
	}
	return 0;
}
