#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
const int maxn=105;
int parent[maxn];
int dis[maxn][maxn];
bool isleaf[maxn];
vector<int>leaf;

int N,depth,leafNum;
int layernum[maxn];
int layer[maxn][maxn];
/**
总体思路:从叶子结点开始计算,对于距离矩阵,扩展到N*N,需要计算每个节点之间的距离.
如果同行相邻的节点之间的距离大于2,说明他们不是同一个父节点,那么上一层对应的父节点的坐标需要后移,
在得到当前节点的父节点后,需要更新父节点到其它节点之间的距离(父节点和除子树外各节点的距离，其实是子节点和它们距离 - 1),
因为父节点后续会成为子节点,需要它和它相邻结点的距离。
如果上层结点是叶子结点,则跳过。
*/
int main() {
    //freopen("1.txt","r",stdin);
    //freopen("2.txt","w",stdout);
    scanf("%d%d%d",&N,&depth,&leafNum);
    for(int i=0; i<depth; i++) {
        scanf("%d",&layernum[i]);
    }
    for(int i=0; i<depth; i++) {
        for(int j=0; j<layernum[i]; j++) {
            scanf("%d",&layer[i][j]);
        }
    }
    memset(isleaf,0,sizeof(isleaf));
    int tmp;
    for(int i=0; i<leafNum; i++) {
        scanf("%d",&tmp);
        isleaf[tmp]=1;
        leaf.push_back(tmp);
    }

    memset(dis,inf,sizeof(dis));
    for(int i=0; i<leafNum; i++) {
        for(int j=0; j<leafNum; j++) {
            scanf("%d",&dis[leaf[i] ][leaf[j] ]);
        }
    }
    memset(parent,0,sizeof(parent));

    //printf("begin calc\n");
    for(int i=depth-1; i>=1; i--) {
        int pos=0;
        for(int j=0; j<layernum[i]; j++) {
            if(parent[layer[i][j]  ]!=0) {
                continue;
            }
			///找到下一个不是叶子节点的结点可以作为父节点
            while(isleaf[layer[i-1][pos ]]) {
                pos++;
            }
            parent[layer[i][j] ] =layer[i-1][pos ];
            for(int k=1; k<=N; k++) {
                if(dis[layer[i][j] ][k]==2) {
                    parent[k]=layer[i-1][pos ];
                } else if(parent[k]==0){
					/**
					* 注意这里必须得是没有标记过的才更新,防止
					*            1
					*      2     3      4
					*    5   6         7 8
					*逐渐更新之后,1-8的距离也是2
					*所以这里为了防止误判,必须是parent还没有标记的,即必须得在当前层或者当前层以上的叶子节点
					*/
                    dis[layer[i-1][pos ] ][k]=dis[layer[i][j] ][k]-1;
					//两边都要更新,这样更新k的父亲的距离的时候,才能到layer[i][j]父亲的距离为2(假如在同一层的话)
                    dis[k ][layer[i-1][pos ] ]=dis[layer[i][j] ][k]-1;
                }
            }
			///说明接下来的都不是同一棵子树,所以父节点后移
            pos++;

            /*
            printf("--------------------------\n");
            for(int m=1; m<=N; m++) {
                for(int n=1; n<=N; n++) {
                    printf("%d ",dis[m][n]);
                }
                printf("\n");
            }
            printf("--------------------------\n");
            */
        }


    }
    bool first=true;
    for(int i=1; i<=N; i++) {
        if(first){
            printf("%d",parent[i]);
            first=false;
        }else{
            printf(" %d",parent[i]);
        }
    }
    printf("\n");
    return 0;
}
