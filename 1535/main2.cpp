#include <bits/stdc++.h>

using namespace std;

char ch1[44], ch2[44];
int sit1[44], sit2[44];

int gao(int n) {
/*
    for(int i=0;i<n;i++){
        printf("%c",sit1[i]+'a');
    }
    printf("\n");
    for(int i=0;i<n;i++){
        printf("%c",sit2[i]+'a');
    }
    printf("\n");
*/
    map<int, int> mp;
    for (int i = 0; i < n; i ++) {
        mp[sit1[i]] = i;
    }
    int b[44];
    for (int i = 0; i < n; i ++) {
        b[i] = mp[sit2[i]];
    }
    bool vis[44] = {0};
    int res = 0;
    for (int i = 0; i < n; i ++) {
        if (vis[i]) continue;
        int now = i, cnt = 0;
        while (!vis[now]) {
            cnt ++;
            vis[now] = true;
            now = b[now];
        }
        res += cnt - 1;
    }
    return res;
}

int main() {
    freopen("1.txt","r",stdin);
    int T;
    scanf("%d", &T);
    while (T --) {
        scanf("%s%s", ch1, ch2);
        int n = strlen(ch1);
        int cnt[33] = {0};
        for (int i = 0; i < n; ++i) {
            cnt[ch1[i] - 'a'] ++;
            sit1[i] = ch1[i] - 'a';
        }
        for (int i = 0; i < n; ++i) {
            sit2[i] = ch2[i] - 'a';
        }
        int num = 0;
        vector<char> vec;
        if (cnt['m' - 'a'] == 2) vec.push_back('m'), num ++;
        if (cnt['s' - 'a'] == 2) vec.push_back('s'), num ++;
        if (cnt['f' - 'a'] == 2) vec.push_back('f'), num ++;
        if (cnt['t' - 'a'] == 2) vec.push_back('t'), num ++;
        int ans = n;
        if (num == 0) ans = min(ans, gao(n));
        printf("num:%d\n",num);
        for (int i = 0; i < (1<<(num+num)); i ++) {
            for (int j = 0; j < num; j ++) {
                int tmp = 0;
                int cc1 = (i>>j) & 1;
                int cc2 = (i>>(j+num)) & 1;

                printf("i:%d j:%d  cc1:%d  %d  cc2:%d  %d\n",i,j,(i>>j),cc1,(i>>(j+num)),cc2);
                for (int k = 0; k < n; k ++) {
                    if (ch1[k] == vec[j]) {
                        if (cc1 == 0) sit1[k] += 26;
                        cc1 --;
                    }
                    if (ch2[k] == vec[j]) {
                        if (cc2 == 0) sit2[k] += 26;
                        cc2 --;
                    }
                }
            }
            printf("gao\n");
            ans = min(ans, gao(n));
            for (int j = 0; j < num; j ++) {
                int tmp = 0;
                int cc1 = (i>>j) & 1;
                int cc2 = (i>>(j+num)) & 1;
                for (int k = 0; k < n; k ++) {
                    if (ch1[k] == vec[j]) {
                        if (cc1 == 0) sit1[k] -= 26;
                        cc1 --;
                    }
                    if (ch2[k] == vec[j]) {
                        if (cc2 == 0) sit2[k] -= 26;
                        cc2 --;
                    }
                }
            }
        }
        printf("%d\n", ans);

    }
    return 0;
}
