#include <bits/stdc++.h>

using namespace std;
const int maxn=5e4+5;
int a[maxn];
int T,N;

int lowbit(int i){
    return i&(-i);
}
void update(int i,int val){
    while(i<=N){
        a[i]+=val;
        i+=lowbit(i);
    }
}
int sum(int i){
    int res=0;
    while(i>0){
        res+=a[i];
        i-=lowbit(i);
    }
    return res;
}

int l,r;
int pos,val;
int main()
{
    //freopen("1.txt","r",stdin);
    scanf("%d",&T);
    int cnt=1;
    while(T--){
        memset(a,0,sizeof(a));
        scanf("%d",&N);
        for(int i=1;i<=N;i++){
            scanf("%d",&val);
            update(i,val);
        }
        char str[10];
        printf("Case %d:\n",cnt++);
        while(true){
            scanf("%s",str);
            if(str[0]=='Q'){
                scanf("%d%d",&l,&r);
                printf("%d\n",sum(r)-sum(l-1));
            }else if(str[0]=='A'){
                scanf("%d%d",&pos,&val);
                update(pos,val);
            }else if(str[0]=='S'){
                scanf("%d%d",&pos,&val);
                update(pos,-val);
            }else{
                break;
            }
        }
    }
    return 0;
}
