#include<bits/stdc++.h>
using namespace std;
char S[100];
char T[100];
int N;

void solve();
void calc();
int minS=0x3f3f3f3f;

int main(){
    //freopen("1.txt","r",stdin);
	scanf("%d",&N);
	while(N--){
		scanf("%s%s",S,T);
		minS=0x3f3f3f3f;
		solve();
		printf("%d\n",minS);
	}

	return 0;
}
void swap(char * str,int x,int y){
    char temp=str[x];
    str[x]=str[y];
    str[y]=temp;
}
/**
计算两个没有重复字符的字符串通过交换变成相同串的最少交换次数
直接每次交换第二个串的相应字符,使每次遍历的位置都是第一个串的字符
例如： msra   asmr
第一次将m a交换： msar
第二次遍历到a的时候：再将a r交换： msra
*/
void calc(){
    //printf("%s   %s\n",S,T);
	int len=strlen(S);

	int pos1[100],pos2[100];
	memset(pos1,-1,sizeof(pos1));
	memset(pos2,-1,sizeof(pos2));

	for(int i=0;i<len;i++){
        pos1[S[i]-'A']=i;
        pos2[T[i]-'A' ]=i;
	}
	int snum=0;
	char tempStr[len];
	memcpy(tempStr,T,len+1);
	for(int i=0;i<len;i++){
		///说明第i位的字母不相同
        if(pos2[S[i]-'A']!=i ){
            //需要交换成相同的
			snum++;
			///将第i 位的字母  与本应在第i位的字母交换位置 
			///S[i]是本应在第i位的字母, pos2[S[i]-'A' ]是它现在在的位置
            swap(tempStr,i, pos2[S[i]-'A']);
			///然后更新被交换字母的位置 pos2[ S[i]-'A' ] 是它被交换后所在的位置
			/// tempStr[ pos2[ S[i]-'A' ]  ] 为获取该字母
			///再取pos2为更新现在的位置
            pos2[ tempStr[ pos2[S[i]-'A' ] ] -'A'] =pos2[S[i]-'A'];
			///应该在第i位的字母,现在在第i位
            pos2[S[i]-'A']= i;

        }
	}
	minS=min(minS,snum);
}

void solve(){
	int len=strlen(S);
	vector<char>vec;
	int cnt[100];
	memset(cnt,0,sizeof(cnt));
	for(int i=0;i<len;i++){
		cnt[S[i]-'a' ]++;
	}
	int num=0;
	if(cnt['m'-'a'] ==2){
		vec.push_back('m');
		num++;
	}
	if(cnt['s'-'a'] ==2){
		vec.push_back('s');
		num++;
	}
	if(cnt['f'-'a'] ==2){
		vec.push_back('f');
		num++;
	}
	if(cnt['t'-'a'] ==2){
		vec.push_back('t');
		num++;
	}
	/**
	* 因为出现两次的字符只有4个,于是考虑2^8枚举两个字符串中替换字符串中重复字符的位置。比如mma可以被替换成Mma或者mMa.
	* 于是拿到的就是两个不含重复字符的串。然后求最少交换次数。
	*/
	/**
	* 使用位运算来分别替换 例如num=3
	* 0-2代表每个字符第一次出现的位置要不要换成大写字母
	* 3-5代表每个字符的第二次出现的位置要不要换成大写字母
	* 假如cc1、cc2的相应位置为0, 那么直接变成大写的(每次通过>>,分别获取i的相应位)
	*/
	for(int i=0;i<(1<<num+num);i++){
		for(int j=0;j<num;j++){
			int cc1= (i>>j) &1;
			int cc2=(i>> (j+num)) &1;
			//printf("num:%d  cc1:%d   cc2:%d  %s\n",num,cc1,cc2,S);
			for(int k=0;k<len;k++){
				if(S[k]==vec[j]){
					if(cc1==0){
						S[k]+=('A'-'a');
					}
					cc1--;
				}
				if(T[k]==vec[j]){
					if(cc2==0){
						T[k]+=('A'-'a');
					}
					cc2--;
				}
			}

		}
		//printf("calc\n");
		calc();
		///将字符串还原回去
		for(int j=0;j<num;j++){
			int cc1= (i>>j) &1;
			int cc2=(i>> (j+num)) &1;
			for(int k=0;k<len;k++){
				if(S[k]<'a'){
                    S[k]-=('A'-'a');
				}
				if(T[k]<'a'){
                    T[k]-=('A'-'a');
				}
			}

		}
	}


}
