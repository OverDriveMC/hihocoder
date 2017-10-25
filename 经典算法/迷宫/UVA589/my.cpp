#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;

typedef pair<int,int>ii;
const int N=25;
///北  南  东  西
const int dir[4][2]={{-1,0},{1,0},{0,1},{0,-1} };
char s1[]="NSEW";
char s2[]="nsew";

map<int,bool>vis[N][N][N][N];
char g[N][N];
int r,c;
ii s,b,t;

string ans;
int push_num;

struct Node{
    int sx,sy,bx,by,num;
    string path;

    Node(int sx,int sy,int bx,int by,int num):
        sx(sx),sy(sy),bx(bx),by(by),num(num){
        path="";
    }

    friend bool operator<(Node a,Node b){
        if(a.num!=b.num){
            return a.num>b.num;
        }
        return a.path.length()>b.path.length();
    }

};
bool check(int x,int y){
    if(x<0 || x>=r || y<0 || y>=c || g[x][y]=='#'){
        return false;
    }
    return true;
}

void solve(){
    priority_queue<Node>Q;
    Q.push(Node(s.first,s.second,b.first,b.second,0));
    vis[s.first][s.second][b.first][b.second][0]=1;
    while(!Q.empty()){
        Node node=Q.top();
        Q.pop();
        //cout<<node.sx<<"  "<<node.sy<<"  "<<node.bx<<"   "<<node.by<<endl;
        if(node.bx==t.first && node.by==t.second){
            if(node.num<push_num){
                push_num=node.num;
                ans=node.path;
            }else if(node.num==push_num){
                if(ans.length()>node.path.length()){
                    ans=node.path;
                }

            }else{
                break;
            }
            continue;

        }

        for(int k=0;k<4;k++){
            Node q=node;
            q.sx+=dir[k][0];
            q.sy+=dir[k][1];
            //cout<<"q:"<<q.sx<<"  "<<q.sy<<"  "<<q.bx<<"  "<<q.by<<endl;
            if(!check(q.sx,q.sy)){
                continue;
            }
            q.path+=s2[k];
            if(q.sx==q.bx && q.sy==q.by){
                q.bx+=dir[k][0];
                q.by+=dir[k][1];
                if(!check(q.bx,q.by)){
                    continue;
                }
                q.num++;
                if(q.num>push_num){
                    continue;
                }
                q.path[q.path.length()-1]=s1[k];
            }
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
    int kase=0;
    while(scanf("%d%d",&r,&c)!=EOF){
        if(r==0 || c==0){
            break;
        }
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
        push_num=INF;
        ans="";
        solve();
        printf("Maze #%d\n",++kase);
        if(ans.length()){
            printf("%s\n",ans.c_str());
        }else{
            printf("Impossible.\n");
        }
        printf("\n");

    }

    return 0;

}
