/**
题目描述：假设整个货架上从左到右摆放了N种商品,并且依次编号为1到N,每次小Hi给出一段区间,小Ho要做的是选出这个区间内的所有商品重量最轻的一种,
并且告诉小Hi这个商品的重量,但是在这个过程中,可能会因为其它人的各种行为,对某些位置上的商品的重量产生改变(如更换了其它种类的商品)
输入:
第1行为N:商品数量
第2行为N个整数:分别描述每种商品的重量,其中第i个整数表示标号为i的商品的重量weight_i
第3行为整数Q:表示小Hi查询的次数与商品的重量被更改的次数之和
接下来Q行表示Q次操作：
	开头为0表示一个查询,接下来是两个整数L,R
	开头为1表示一个修改,表示编号位置为Pi的商品重量变更为Wi
对于100%的数据，满足N<=10^4，Q<=10^4, 1<=Li<=Ri<=N，1<=Pi<=N, 0<weight_i, Wi<=10^4。
输出:
	对于每个小Hi的查询,输出查询结果,标号在[L,R]中的所有商品中重量最轻的商品重量

样例输入
10
618 5122 1923 8934 2518 6024 5406 1020 8291 2647
6
0 3 6
1 2 2009
0 2 2
0 2 10
1 1 5284
0 2 5
样例输出
1923
2009
1020
1923
*/

#include<bits/stdc++.h>

using namespace std;
const int maxn=1e4+5;
const int inf=0x3f3f3f3f;
int minv[maxn<<2];


void pushUp(int o){
	minv[o]=min(minv[o<<1], minv[o<<1|1]);
}
void build(int o,int l,int r){
//l==r说明到叶子结点,叶子节点区间的最小值即为自身
	if(l==r){
		scanf("%d",&minv[o]);
		return;
	}
	int m=(l+r)>>1;
	build(o<<1,l, m);
	build(o<<1 | 1, m+1,r);
//构建完左右子树,便可以根据左右子树pushUp,得到总的区间的最小值
	pushUp(o);
}
int x,v;
void modify_point(int o,int l, int r){
	if(l==r){
        //l==r==x
		minv[o]=v;
		return ;
	}
	int m=(l+r)>>1;
	if(x<=m){
		modify_point(o<<1,l,m);
	}else{
		modify_point(o<<1|1, m+1,r);
	}
//修改完之后需要pushUp
	pushUp(o);
}
int ql,qr;
int query(int o, int l,int r){
// ql  l  r  qr
	if(ql<=l && r<=qr){
		return minv[o];
	}
	int m=(l+r)>>1;
	int ret=inf;
	if(ql<=m){
		ret=min(ret, query(o<<1,l,m));
	}
	if(m<qr){
		ret=min(ret, query(o<<1|1, m+1, r));
	}
	return ret;
}
int N,Q;


int main(){
	freopen("1.txt","r",stdin);
	while(scanf("%d",&N) !=EOF){
		build(1,1,N);
		scanf("%d",&Q);
		int op;
		for(int i=1;i<=Q;i++){
			scanf("%d",&op);
			if(op==0){
				scanf("%d%d",&ql,&qr);
				printf("%d\n",query(1,1,N));
			}else{
				scanf("%d%d",&x,&v);
				modify_point(1,1,N);
			}
		}
	}
	return 0;
}
