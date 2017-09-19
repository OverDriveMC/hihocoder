#include <bits/stdc++.h>

using namespace std;
//#define Debug

typedef long long LL;



const int maxn=1e6+5;
/**
* G 维护边,next指向下一个共父的结点
*/
struct G{
    int v,w1,w2,next;
}E[maxn*2];
/**
* p[i]维护i结点的第一条边在G中的位置下标
* 例如p[2]=4,说明结点2与G[4].v 有边,权重分别为G[4].w1,G[4].w2
* 2的下一条边在G中的下标为G[4].next
* 知道G[j].next=-1说明是最后一条边
*/
int p[maxn],T;
bool vis[maxn];
LL dp[maxn][5];
int si[maxn];


void add(int u,int v,int w1,int w2){
    E[T].v=v;
    E[T].w1=w1;
    E[T].w2=w2;
    E[T].next=p[u];
    p[u]=T++;

    E[T].v=u;
    E[T].w1=w1;
    E[T].w2=w2;
    E[T].next=p[v];
    p[v]=T++;
}
/**
j==0：人去，不管人是否回来
j==1：人去，人一定要回来
j==2：人车都去，人车都要回来
j==3：人车都去，人一定要回来，车不管
j==4：人车都去，不管人车最后是否回来。
*/
void dfs(int u,int fa){

}

int main()
{
    freopen("1.txt","r",stdin);
    int n,m,u,v,w1,w2;
    while(scanf("%d",&n)!=EOF){
        memset(p,-1,sizeof(p));
        T=0;
        memset(vis,false,sizeof(vis));

        for(int i=1;i<n;i++){
            scanf("%d%d%d%d",&u,&v,&w1,&w2);
            add(u,v,w1,w2);
        }

        scanf("%d",&m);
        for(int i=1;i<=m;i++){
            scanf("%d",&u);
            vis[u]=true;
        }
#ifdef Debug
        for(int i=0;i<T;i++){
            cout<<i<<"  "<<E[i].v<<"   next:"<<E[i].next<<endl;
        }
        for(int i=0;i<10;i++){
            cout<<i<<"   "<<p[i]<<endl;
        }

#endif // Debug

        dfs(1,-1);

        cout<<min(dp[1][0],dp[1][4])<<endl;
    }
    return 0;
}
