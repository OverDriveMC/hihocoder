#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;
/**
总的状态有2^20 * 6种,其中2^20为矩阵最多有的状态,6是buffer:0-5  6种状态
对于矩阵(最大有20格子),每个格子有2两种选择:揭开了还是没有揭开
所以可以将揭开的格子设置为'D',然后计算目前格子对应的状态值
dp[i][j]代表在i状态,剩余j个buffer,最少需要多少hp才能杀死所有monster
最后结果就是HP-dp[initstate][5]

*/
class Monster{

public:
    int x,y;
    int hp,ap;
    Monster(){

    }

    Monster(int x,int y,int hp, int ap):
        x(x),y(y),hp(hp),ap(ap){}
};

int N,M;
char maze[25][25];
int HP,AP;
map<pair<int,int>,Monster>monsters;

const int MAX_State=(1<<20);
const int BUFFER=5;
int dp[MAX_State+1][BUFFER+1];

int killMonster( char maze[][25], int buffer);


int main(){
   // freopen("1.txt","r",stdin);
    scanf("%d%d",&N,&M);
    for(int i=0;i<N;i++){
        scanf("%s",maze[i]);
    }
    int index=0;
    int hp,ap;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(maze[i][j]=='S' || maze[i][j]=='M'){
                scanf("%d%d",&hp,&ap);
                monsters[make_pair(i,j) ]=Monster(i,j,hp,ap);
            }
        }
    }

    scanf("%d%d",&HP,&AP);

    memset(dp,INF,sizeof(dp));
    int remainHP=HP-killMonster(maze,BUFFER);
    if(remainHP<=0){
        printf("DEAD\n");
    }else{
        printf("%d\n",remainHP);
    }

    return 0;
}

/**
* 每个函数返回的是dp[state][buffer]
*一定不能修改这个buffer
*/
int killMonster(char maze[][25], int buffer){
    int state=0;
    int remainMonster=0;
    set<pair<int,int> >candidates;
    /**
    *  状态一共有1<<20 * BUFFER个状态
    *  一个格子两种状态 D:0   非D:1
    */

    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            state<<=1;
            if(maze[i][j]!='D'){
                state+=1;

                if(maze[i][j]=='S' || maze[i][j]=='M'){
                    remainMonster++;
                }
                ///判断四周是不是'D',可以作为下一步走的位置
                if((i-1>=0 && maze[i-1][j]=='D' ) || (j-1>=0 && maze[i][j-1]=='D' ) ||
                   (i+1<N && maze[i+1][j]=='D' ) || (j+1<M && maze[i][j+1]=='D') ){
                    candidates.insert(make_pair(i,j));
                }
            }
        }
    }

/*
    char strings[25];
    itoa(state,strings,2);
    printf("state:%s   %d\n",strings,buffer);
    for(int i=0;i<N;i++){
        printf("%s\n",maze[i]);
    }
    */

    if(remainMonster==0){
        return 0;
    }
    if(dp[state][buffer]!=INF){
        return dp[state][buffer];
    }
    ///初始化当前状态需要血量为HP
    dp[state][buffer]=HP;
    for(set<pair<int,int> >::iterator iter=candidates.begin(); iter!=candidates.end(); ++iter){
        int needHP=0;
        /**
        *   需要定义个curbuffer去修改,因为这一轮求得是state buffer的状态值
        * 不能直接修改原有buffer的值
        */
        ///这个需要放在里面
        int curbuffer=buffer;
        curbuffer--;
        if(maze[iter->first][iter->second]=='S' ||  maze[iter->first][iter->second]=='M'){
            int monsterHP=monsters[*iter].hp;
            int monsterAP=monsters[*iter].ap;
            while(monsterHP>0){
                if(curbuffer>0){
                    curbuffer--;
                }else{
                    needHP+=monsterAP;
                }
                monsterHP-=AP;
            }

            if(maze[iter->first][iter->second]=='S'){
                curbuffer=BUFFER;
            }


        }
        if(curbuffer<0){
            curbuffer=0;
        }

        if(needHP>HP){
            continue;
        }

        char curmaze=maze[iter->first][iter->second];
        ///将当前位置修改为D
        maze[iter->first][iter->second]='D';
        int minHP=killMonster(maze,curbuffer);
        ///重置当前位置
        maze[iter->first][iter->second]=curmaze;
        if(minHP> HP){
            continue;
        }

        dp[state][buffer]=min(dp[state][buffer], minHP+needHP);
    }

    return dp[state][buffer];
}
