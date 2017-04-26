#include<bits/stdc++.h>

using namespace std;

const int maxn=1e6+5;

char str[maxn];
char nstr[2*maxn];
///维护回文半径
int f[2*maxn];
///$#a#b#c#c#b#a#  以#为中心的奇数串,去了中心的#正好字母和#成对出现
///$#a#b#c#b#a#   以c为中心的奇数串,去了第一个#之后,字母和#成对出现
///所以最长回文串为f-1
int nlen=0;


///$#a#a#a#a#\0  构成奇数回文串
void initnstr(char* str,int len){
    nstr[0]='$';
    nlen=1;
    for(int i=0;i<len;i++){
        nstr[nlen++]='#';
        nstr[nlen++]=str[i];
    }
    nstr[nlen++]='#';
    nstr[nlen]='\0';
}
int manacher(){
    ///curmaxindex当前到达curmaxcomeindex回文串的中心(并不是最长回文串中心)
    ///curmaxcomeindex当前能延伸到的最后一个位置的下一个
    int curmaxindex=0,curmaxcomeindex=0,maxl=1;
    int pos=1;
    memset(f,0,sizeof(f));
    while(pos<nlen){
        ///判断当前位置是否在边界位置以前
        if(curmaxcomeindex>pos){
            ///假如以5为中心的回文串半径为5,说明  1-4与6-9对应相等
            ///那么在7的位置的回文串至少与  3在边界内是相等的。
            ///假如 3的半径为2   说明 234是回文串,那么 678必然也是回文串(因为2=8 3=7 4=6)
            ///注意必须在该回文串的边界内,假如 >9之后变没有了对应关系
            f[pos]=min(f[curmaxindex*2-pos],curmaxcomeindex-pos);
        }else{
            f[pos]=1;
        }
        ///开头$结尾\0,必然不相等于其它的,所以不用判定边界
        while(nstr[pos+f[pos]]==nstr[pos-f[pos]] ){
            f[pos]++;
        }
        ///判断是否可以延伸到更远的地方
        if(pos+f[pos]>curmaxcomeindex ){
            curmaxcomeindex=pos+f[pos];
            curmaxindex=pos;
        }
        maxl=max(maxl,f[pos]);
        pos++;

    }
    return maxl-1;

}

int main(){
    //freopen("1.txt","r",stdin);
    int N;
    scanf("%d",&N);
    while(N--){
        scanf("%s",str);
        initnstr(str,strlen(str));
        int res=manacher();
        printf("%d\n",res);
    }
}
