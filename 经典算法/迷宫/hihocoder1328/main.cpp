#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
const int MAXN=105;

map<int,bool> vis[MAXN][MAXN];
int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1} };
int ans;

int N,M,K,a,b,c,d;

char g[MAXN][MAXN];


struct Point{
    int x,y;
    Point(){}
    Point(int x,int y):x(x),y(y){}
    bool operator == (const Point & p)const{
        return x==p.x && y==p.y;
    }
    bool operator <(const Point &p)const{
        return x<p.x || (x==p.x && y<p.y);
    }
};
map<Point,int >keys;

struct Node{
    int x,y,num;
    Node(){}
    int keys;
    Node(int x,int y,int num=0,int keys=0):
        x(x),y(y),num(num),keys(keys){
        keys=0;
    }

};


bool check(int x,int y,int keys){
    if(x<0 || x>=N || y<0 || y>=M || g[x][y]=='#'){
        return false;
    }
    if(g[x][y]=='.'){
        return true;
    }
    //cout<<x<<"  "<<y<<"  "<<n.keys<<"   "<<(1<<(g[x][y]-'A') )<<"   "<<( n.keys &(1<<(g[x][y]-'A') )  ) << endl;
    ///判断当前位置是否有钥匙
    if( (keys &(1<<(g[x][y]-'A') ) )==0 ){
        return false;
    }
    return true;
}

void solve(){
    queue<Node>Q;
    Node n=Node(a,b,0);
    if(keys.find(Point(a,b))!=keys.end()){
        n.keys|= keys[Point(a,b) ] ;
    }
    vis[a][b][n.keys]=1;
    Q.push(n);

    while(!Q.empty()){
        Node p=Q.front();
        Q.pop();
       // printf("x=%d  y=%d  num=%d  keys=%d\n",p.x,p.y,p.num,p.keys.size());
        if(p.x==c && p.y==d){
            //cout<<ans<<"  "<<p.num<<"  "<<p.keys<<endl;
            ans=min(ans,p.num);
            return ;
        }
        for(int i=0;i<4;i++){
            int nx=p.x+dir[i][0];
            int ny=p.y+dir[i][1];
            int nkeys=p.keys;
            ///先check能不能走,在添加该地的钥匙
            ///防止钥匙在锁着的门里
            if(!check(nx,ny, nkeys)){
                continue;
            }
            if(keys.find(Point(nx,ny))!=keys.end()){
                nkeys|=keys[Point(nx,ny)];
            }
            if(vis[nx][ny][nkeys ]){
                continue;
            }
            vis[nx][ny][nkeys]=1;
            Q.push(Node(nx,ny,p.num+1,nkeys));
        }

    }
}

int main(){
    //freopen("1.txt","r",stdin);
    while(scanf("%d%d%d%d%d%d%d",&N,&M,&K,&a,&b,&c,&d)!=EOF){
        for(int i=0;i<N;i++){
            scanf("%s",g[i]);
            for(int j=0;j<M;j++){
                vis[i][j].clear();
            }
        }
        keys.clear();
        int x,y;
        for(int i=0;i<K;i++){
            scanf("%d%d",&x,&y);
            /**
            * 采用位运算记录每一个点的钥匙数量
            * 注意:一个位置有多个钥匙的情况
            */
            keys[Point(x,y)] |= (1<<i);
        }
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
