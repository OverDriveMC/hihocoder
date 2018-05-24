/**
题目描述：假设货架上从左到右摆放了N种商品,并且依次标号为1到N,其中标号为i的商品的价格为Pi.
小Hi的每次操作分为两种可能：
第一种操作是修改价格——小Hi给出一段区间[L,R]和一个新的价格NewP,所有标号在这段区间中的商品价格都变成NewP.
第二种操作是询问——小Hi给出一段区间[L,R],而小Ho要做的便是计算出所有标号在这段区间中的商品的总价格,然后告诉小Hi.

输入：
第一行为整数N,
第二行为N个整数,分别描述每种商品的重量，其中第i个整数表示标号为i的商品的重量Pi。
第3行为一个整数Q，表示小Hi进行的操作数。
接下来Q行,每行代表一个操作,
	0开头表示一次询问,后面跟着两个整数L,R,代表查询区间[L,R]
	1开头表示商品价格的更改,接下来跟着三个整数L,R,newP

输出：
	输出查询的结果,标号在区间[L, R]中的所有商品的价格之和。
*/

#include<bits/stdc++.h>

using namespace std;
const int maxn=1e5+5;

int sumv[maxn<<2],setv[maxn<<2];

int N,Q;
int L,R,op,val;

void pushup(int o,int l,int r){
	sumv[o]=sumv[o<<1]+ sumv[o<<1|1];
}
void build(int o,int l,int r){
	setv[o]=0;
	if(l==r){
		scanf("%d",&sumv[o]);
		return ;
	}
	int mid=(l+r)>>1;
	build(o<<1,l,mid);
	build(o<<1|1,mid+1,r);
	pushup(o,l,r);
}

void pushDown(int o,int l,int r){
	if(setv[o]){
        int mid=(l+r)>>1;
        sumv[o<<1]=(mid-l+1)*setv[o];
		sumv[o<<1|1]=(r-mid)*setv[o];

		setv[o<<1]=setv[o];
		setv[o<<1|1]=setv[o];
		setv[o]=0;
	}
}

void modify(int o,int l,int r){
	if(L<=l && r<=R){
		sumv[o]=val*(r-l+1) ;
		setv[o]=val;
		return ;
	}
	pushDown(o,l,r);
	int mid=(l+r)>>1;
	if(L<=mid){
		modify(o<<1,l,mid);
	}
	if(R>mid){
		modify(o<<1|1,mid+1,r);
	}
	pushup(o,l,r);
}
int query(int o,int l,int r){
	if(L<=l && r<=R){
		return sumv[o];
	}
	pushDown(o,l,r);
	int mid=(l+r)>>1;
	int ret=0;
	if(L<=mid){
		ret+=query(o<<1,l,mid);
	}
	if(mid<R){
		ret+=query(o<<1|1,mid+1,r);
	}
	return ret;
}



int main(){
	//freopen("1.txt","r",stdin);
	while(scanf("%d",&N)!=EOF){
		build(1,1,N);
		scanf("%d",&Q);
		for(int i=1;i<=Q;i++){
			scanf("%d",&op);
			if(op==0){
				scanf("%d%d",&L,&R);
				printf("%d\n",query(1,1,N));
			}else{
				scanf("%d%d%d",&L,&R,&val);
				modify(1,1,N);
			}
		}
	}
	return 0;
}
