#include<bits/stdc++.h>

using namespace std;
const int maxn=1e3+5;
const int inf=0x3f3f3f3f;
int N,M,S,T;


struct Node{
    int id;
    int val;

    //Node(int id,int val):id(id),val(val){}


    /**
    *首先重载 <  注意末尾的const不能省略
    */
    bool operator<(const struct Node&node)const{
        return val>node.val;
    }
};
struct Edge{
    int to;
    int length;
    Edge(int to,int length):to(to),length(length){}
};
vector<Edge>g[maxn];
Node node[maxn];

int vis[maxn];

int main(){
    //freopen("1.txt","r",stdin);
    scanf("%d%d%d%d",&N,&M,&S,&T);

    for(int i=1;i<=N;i++){
        node[i].id=i;
        node[i].val=inf;
    }
    memset(vis,0,sizeof(vis));
    int from,to,length;
    for(int i=0;i<M;i++){
        scanf("%d%d%d",&from,&to,&length);
        g[from].push_back(Edge(to,length));
        g[to].push_back(Edge(from,length));
    }

    node[S].val=0;
    priority_queue<Node>q;
    q.push(node[S]);
    while(!q.empty()){
        Node n=q.top();
        q.pop();
        if(n.id==T){
            break;
        }

        if(vis[n.id]!=0){
            continue;
        }
        vis[n.id]=1;
        for(int i=0;i<g[n.id ].size();i++){
			/**
			* 松弛操作
			*/
            if(node[g[n.id][i].to ].val > (node[n.id].val + g[n.id][i].length ) ){
                node[g[n.id][i].to ].val =node[n.id].val + g[n.id][i].length;
            }
            q.push(node[ g[n.id][i].to  ]  );
        }
    }
    printf("%d\n",node[T].val);
    return 0;
}
