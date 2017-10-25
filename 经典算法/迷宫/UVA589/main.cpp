#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;


///北 南  东  西
const int d[4][2]={{-1,0},{1,0},{0,1},{0,-1}};
const char s1[10]="NSEW";
const char s2[10]="nsew";

const int N=25;
int r,c,push_num;
char g[N][N];

string ans;
map<int,bool>vis[20][20][20][20];
typedef pair<int,int>pi;
pi s,b,t;

struct State{
    int sx,sy,bx,by,num;
    string path;
    State(){}
    State(int sx,int sy,int bx,int by,int num):
        sx(sx),sy(sy),bx(bx),by(by),num(num){
        path="";
    }
    friend bool operator<(State a,State b){
        if(a.num!=b.num)
            return a.num>b.num;
        return a.path.length() > b.path.length();
    }
};

void init(){
    ans="";
    push_num=INF;
    for(int i=0;i<r;i++){
        scanf("%s",g[i]);
        for(int j=0;j<c;j++){
            if(g[i][j]=='S'){
                s=make_pair(i,j);
            }else if(g[i][j]=='B'){
                b=make_pair(i,j);
            }else if(g[i][j]=='T'){
                t=make_pair(i,j);
            }
            if(g[i][j]!='#'){
                g[i][j]='.';
            }
            for(int k=0;k<r;k++){
                for(int l=0;l<c;l++){
                    vis[i][j][k][l].clear();
                }
            }
        }
    }

}

bool check(int x,int y){
    if(x<0 || x>=r || y<0 || y>=c || g[x][y]!='.'){
        return false;
    }
    return true;
}

void solve(){
    priority_queue<State>Q;
    vis[s.first][s.second][b.first][b.second][0]=1;
    Q.push(State(s.first,s.second,b.first,b.second,0));
    while(!Q.empty()){
        State p=Q.top();
        Q.pop();
        if(p.bx==t.first && p.by==t.second){
            if(push_num>p.num){
                ans=p.path;
                push_num=p.num;
            }else if(push_num==p.num){
                if(ans.length()>p.path.length()){
                    ans=p.path;
                }
            }else{
                ///因为是根据p.num排序的优先队列,假如p.num>push_num了
                ///那么之后的操作数必然都是大于push_num的,所以可以break退出了
                break;
            }
            continue;
        }
        for(int i=0;i<4;i++){
            State q=p;
            q.sx+=d[i][0];
            q.sy+=d[i][1];
            if(!check(q.sx,q.sy)){
                continue;
            }
            q.path+=s2[i];
            if(q.sx==q.bx && q.sy==q.by){
                q.bx+=d[i][0];
                q.by+=d[i][1];
                if(!check(q.bx,q.by)){
                    continue;
                }
                q.num++;
                if(q.num>push_num){
                    continue;
                }
                ///覆盖掉之前的小写字母,说明是带着箱子走的
                q.path[q.path.length()-1]=s1[i];
            }
			///之前不用判是否走过,在最后统一判断即可
            ///在同一个位置(人,箱子),但是走的长度可能不同,所以需要第五维
			///注意第五维是ans,而不是q.path,使用q.path可能会出现先往南走,在往北走,其实这是同一种状态
			///所以需要根据ans判重
            if(vis[q.sx][q.sy][q.bx][q.by][ans.length()]){
                continue;
            }
            vis[q.sx][q.sy][q.bx][q.by][ans.length()]=1;
            Q.push(q);
        }
    }
}


int main(){
    //freopen("1.txt","r",stdin);
    int cas=0;
    while(scanf("%d%d",&r,&c)!=EOF){
        if(r==0 && c==0){
            break;
        }
        init();
        printf("Maze #%d\n",++cas);
        solve();
        if(ans.length()){
            printf("%s\n",ans.c_str());
        }else{
            printf("Impossible.\n");
        }
        printf("\n");
    }
    return 0;
}

