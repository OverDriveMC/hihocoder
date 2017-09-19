#include<bits/stdc++.h>

using namespace std;

const int maxn=1e5+5;
struct Node{
    int to,w;
    Node(int to,int w):to(to),w(w){}
};
///维护子树最长距离,最长距离个数
///次长距离,次长距离个数
///合并之后是最长距离,最长距离个数
struct Info{
    int max1,max2,cnt1,cnt2,m,n;
};

vector<Node>g[maxn];
Info info[maxn];
/**
* 引入fa的目的,而不用vis是因为:
*    找次长的时候,所有子树实际都已经访问完了,
*    所以次长那个循环里所有的都直接continue了
*    那么父亲结点的次长更新不了
*/
void dfs(int from,int fa){

    for(int i=0;i<g[from].size();i++){
        int v=g[from][i].to;
        int w=g[from][i].w;
        if(v==fa){
            continue;
        }
        dfs(v,from);
        int cost=w+info[v].max1;
        if(cost>info[from].max1){
            info[from].max1=cost;
            info[from].cnt1=info[v].cnt1;
            ///等于0的时候,可以标记出来,取最大值的点只有一个
            info[from].n=0;
        }else if(cost==info[from].max1){
            ///当前最长路有3个,现在新的子节点又多了3个,所以 n更新为 n+=3*3
            ///下次再找的时候,最长路已经有6(3+3)条了,使用这6条在于新来的路组合
            info[from].n+=info[from].cnt1*info[v].cnt1;
            info[from].cnt1+=info[v].cnt1;

        }
    }
    ///开始更新次大值
    for(int i=0;i<g[from].size();i++){
        int v=g[from][i].to;
        int w=g[from][i].w;
        if(v==fa){
            continue;
        }
        int cost=w+info[v].max1;
        if(cost == info[from].max1){
            continue;
        }else if(cost > info[from].max2){
            info[from].max2=cost;
            info[from].cnt2=info[v].cnt1;
        }else if(cost==info[from].max2){
            info[from].cnt2+=info[v].cnt1;
        }
    }
    //cout<<"from:"<<from<<"  "<<info[from].max1<<"  "<<info[from].max2<<"  "<<info[from].cnt1<<"  "<<info[from].cnt2<<endl;
    //cout<<"m:"<<info[from].m<<"  "<<info[from].n<<endl;
    ///不能通过max2==0来判断,因为可能就真的只有一条路径可以取到max1,所以必须通过n来判断
    ///cnt2最小为1,所以不会出现乘以0的现象
    if(info[from].n!=0){
        ///多条路的长度都是max1,所以最长为max1*2
        info[from].m=info[from].max1*2;
    }else{
        info[from].m=info[from].max1+info[from].max2;
        info[from].n=info[from].cnt1 * info[from].cnt2;
        if(info[from].m==0){
            info[from].n=0;
        }
    }

}
void initInfo(int index){
    info[index].max1=0;
    info[index].max2=0;
    info[index].cnt1=1;
    info[index].cnt2=1;
    info[index].m=0;
    info[index].n=0;
}


int main(){
   // freopen("1.txt","r",stdin);
    int N;
    while(scanf("%d",&N)!=EOF){
        int from,to,cost;
        for(int i=1;i<=N;i++){
            g[i].clear();
            initInfo(i);
        }
        for(int i=1;i<N;i++){
            scanf("%d%d%d",&from,&to,&cost);
            g[from].push_back(Node(to,cost));
            g[to].push_back(Node(from,cost));
        }
        dfs(1,0);
        int gmax=0,cnt=0;
        for(int i=1;i<=N;i++){
            if(info[i].m>gmax){
                gmax=info[i].m;
                cnt=info[i].n;
            }else if(info[i].m==gmax){
                cnt+=info[i].n;
            }
        }
        printf("%d %d\n",gmax,cnt);
    }


    return 0;
}
