#include<bits/stdc++.h>

using namespace std;
int P,Q,N;
double f[105];

int main(){
    freopen("1.txt","r",stdin);
	scanf("%d%d%d",&P,&Q,&N);
	int pow=1;
	for(int i=1;i<=8;i++){
		int curp=P/pow;
		double resp=1;
		pow*=2;
		double exp=0;
		for(int j=1;j<=100;j++){
			exp=exp+ 0.01*curp*resp*j;
			if(curp==100){
				f[i]=exp;
				break;
			}
			resp*=(100-curp)*0.01;
			curp=curp+Q;
            curp =curp>=100 ? 100 : curp;
		}
	}
	double res=0;
	for(int i=1;i<=N;i++){
		int index=i>8 ? 8: i;
		res+=f[index];
		//printf("%d  %.2lf\n",i,f[index]);
	}
	printf("%.2lf\n",res);
	return 0;
}




