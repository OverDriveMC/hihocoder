#include<bits/stdc++.h>

using namespace std;
struct Node{
    int cnt=0;
    Node* node[26];
	/**
	*构造的时候初始化为空,表示该单词还未存在
	*/
    Node(){
        for(int i=0;i<26;i++){
            node[i]=NULL;
        }
    }
};
Node *root=new Node();
void insert(char*str,int len){
    Node* p=root;
    for(int i=0;i<len;i++){
        if(p->node[str[i]-'a']==NULL){
            p->node[str[i]-'a']=new Node();
        }
        p=p->node[str[i]-'a'];
        p->cnt++;
    }
}
int query(char*str,int len){
    Node* p=root;
    for(int i=0;i<len;i++){
        if(p->node[str[i]-'a']!=NULL){
            p=p->node[str[i]-'a'];
        }else{
            ///假如不匹配返回0
            return 0;
        }
    }
    return p->cnt;
}

int main(){
    //freopen("1.txt","r",stdin);
    int n,m;
    scanf("%d",&n);
    char str[30];
    for(int i=0;i<n;i++){
        scanf("%s",str);
        insert(str,strlen(str));
    }

    scanf("%d",&m);
    for(int i=0;i<m;i++){
        scanf("%s",str);
        int cnt=query(str,strlen(str));
        printf("%d\n",cnt);
    }
    return 0;
}
