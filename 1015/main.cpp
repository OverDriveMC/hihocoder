#include<bits/stdc++.h>

using namespace std;
const int len1=1e4+5;
const int len2=1e6+5;

char pattern[len1];
char original[len2];
int N;
int pnext[len1];

///初始化next数组
void init(char*pattern,int plen){
    pnext[0]=0;
    int k=0,pos=1;
    while(pos<plen){
        while(k>0 && pattern[k]!=pattern[pos] ){
            k=pnext[k-1];
        }
        if(pattern[k]==pattern[pos]){
            k++;
        }
        pnext[pos]=k;
        pos++;
    }
}

int kmp(char*pattern,int plen,char*original,int olen){
    init(pattern,plen);
//    printf("%s\n",pattern);
//    for(int i=0;i<plen;i++){
//        printf("%d ",next[i]);
//    }
//    printf("\n");

	int cnt=0;
    int k=0,pos=0;
    while(pos<olen){
        while(k>0 && original[pos]!=pattern[k]){
            k=pnext[k-1];
        }
        ///这里只有两种情况,一种是相等,另一种是不相等并且k=0,说明当前位置必然不匹配
        if(pattern[k]==original[pos]){
            k++;
        }
        ///说明匹配成功
        if(k==plen){
            cnt++;
            ///因为[0,next[k]-1]与[k-next[k]+1,k]相等
            ///直接将[0,next[k]-1]拉过来,匹配下一个,即next[k]
            ///找plen-1的下一个实际是,k会多加一个
            k=pnext[k-1];
            //cout<<"匹配位置:"<<pos<<" next:k:"<<k<<endl;
        }

        ///无论匹配不匹配,pos都要往后加
        pos++;
    }
	return cnt;
}

int main(){
	//freopen("1.txt","r",stdin);
	scanf("%d",&N);
	for(int i=0;i<N;i++){
		scanf("%s%s",pattern,original);
		int res=kmp(pattern,strlen(pattern),original,strlen(original));
		printf("%d\n",res);
	}
	return 0;
}
