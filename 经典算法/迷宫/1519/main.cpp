#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
int N,M;
const int maxn=505;
bool vis[maxn][maxn];
struct Node{
    int x,y,step;
    Node(int x,int y,int step=0):
        x(x),y(y),step(step){}

};
int dir[4][2]={{1,0},{-1,0},{0,-1},{0,1}};
int sx,sy,tx,ty;
char g[maxn][maxn];
int ans;

bool check(int x,int y){
    if(x<0 || x>=N || y<0 || y>=M || g[x][y]=='#'){
        return false;
    }
    return true;
}

void solve(){
    queue<Node>Q;
    Q.push(Node(sx,sy,0));
    vis[sx][sy]=1;
    while(!Q.empty()){
        Node node=Q.front();
        Q.pop();
        for(int i=0;i<4;i++){
            int nx=node.x;
            int ny=node.y;
            while(check(nx+dir[i][0],ny+dir[i][1])){
                nx+=dir[i][0];
                ny+=dir[i][1];
                ///直接在循环里面判断已经到达终点
                ///不能再外面判,会多一次
                if(nx==tx && ny==ty){
                    ans=node.step;
                    return ;
                }
            }
            ///只需要判断下标是否走过即可
            if(!vis[nx][ny]){
                //printf("%d  %d  %d\n",nx,ny,node.step+1);
                Q.push(Node(nx,ny,node.step+1));
                vis[nx][ny]=1;
            }
        }
    }

}
int main()
{
    //freopen("1.txt","r",stdin);
    while(scanf("%d%d",&N,&M)!=EOF){
        for(int i=0;i<N;i++){
            scanf("%s",g[i]);
            for(int j=0;j<M;j++){
                if(g[i][j]=='S'){
                    sx=i;
                    sy=j;
                }else if(g[i][j]=='T'){
                    tx=i;
                    ty=j;
                }
            }
        }
        memset(vis,0,sizeof(vis));
        ans=INF;
        solve();
        if(ans==INF){
            printf("-1\n");
        }else{
            printf("%d\n",ans);
        }
    }
    return 0;
}
