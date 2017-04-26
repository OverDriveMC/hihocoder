#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

char mo[10005];
char str[1000005];
int N;

int main() {
    //freopen("1.txt","r",stdin);
    scanf("%d", &N);
    while(N--) {
        scanf("%s %s", mo, str);
        int next[10005] = {-1};
        int i = 0, j = -1, len = strlen(mo);
        while(i < len) {     //获得next函数
            if(j == -1 || mo[i] == mo[j]) next[++i] = ++j;
            else j = next[j];
        }
//        printf("%s\n",mo);
//        for(int i=0;i<len;i++){
//            printf("%d ",next[i]);
//        }
//        printf("\n");


        int ans = 0, len1 = strlen(str);
        i = j = 0;
        while(i < len1) {        //求模式串在原串中出现的次数
            if(j == -1 || str[i] == mo[j]) ++i, ++j;
            else j = next[j];
            if(j == len) ans++;
        }

        printf("%d\n", ans);
    }
    return 0;
}
