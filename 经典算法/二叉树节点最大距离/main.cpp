#include<bits/stdc++.h>

using namespace std;
/**
* 计算一个二叉树的最大距离有两个情况:
*   情况A:路径经过左子树的最深结点,通过根节点,再到右子树的最深节点
*   情况B:路径不穿过根节点,而是左子树或右子树的最大距离路径,取其大者
*/
struct Node{
    ///左子树中的最长距离
    int nMaxLeft;
    ///右子树中的最长距离
    int nMaxRight;
    ///左子树
    Node *pLeft;
    ///右子树
    Node *pRight;
};


void Link(Node* root,int parent,int left,int right){
    if(left!=-1){
        root[parent].pLeft=&root[left];
    }
    if(right!=-1){
        root[parent].pRight=&root[right];
    }

}
int nMaxn=0;
void findMax(Node*root){
    ///遍历到叶子结点,返回
    if(root==NULL){
        return ;
    }
    ///假如左子树为空,那么该节点的左边最长距离为0
    if(root->pLeft==NULL){
        root->nMaxLeft=0;
    }
    ///如果右子树为空,那么该节点的右边最长距离为0
    if(root->pRight==NULL){
        root->nMaxRight=0;
    }
    ///如果左子树不为空,递归寻找左子树最长距离
    if(root->pLeft!=NULL){
        findMax(root->pLeft);
    }
    ///如果右子树不为空,递归寻找右子树最长距离
    if(root->pRight!=NULL){
        findMax(root->pRight);
    }
    ///计算左子树最长结点距离
    if(root->pLeft!=NULL){
        if(root->pLeft->nMaxLeft > root->pLeft->nMaxRight){
            root->nMaxLeft=root->pLeft->nMaxLeft+1;
        }else{
            root->nMaxLeft=root->pLeft->nMaxRight+1;
        }
    }
    ///计算右子树最长结点距离
    if(root->pRight!=NULL){
        if(root->pRight->nMaxLeft > root->pRight->nMaxRight){
            root->nMaxRight=root->pRight->nMaxLeft+1;
        }else{
            root->nMaxRight=root->pRight->nMaxRight+1;
        }
    }
    ///更新最长距离
    if(root->nMaxLeft + root->nMaxRight > nMaxn ){
        nMaxn=root->nMaxLeft + root->nMaxRight;
    }
}



int main(){
    Node test1[9]={0};
    Link(test1, 0, 1, 2);
    Link(test1, 1, 3, 4);
    Link(test1, 2, 5, 6);
    Link(test1, 3, 7, -1);
    Link(test1, 5, -1, 8);

    findMax(test1);
    cout<<nMaxn<<endl;

    nMaxn=0;
    Node test2[4] = { 0 };
    Link(test2, 0, 1, 2);
    Link(test2, 1, 3, -1);
    findMax(test2);
    cout << "test2: " << nMaxn << endl;


    nMaxn=0;
    Node test3[9] = { 0 };
    Link(test3, 0, -1, 1);
    Link(test3, 1, 2, 3);
    Link(test3, 2, 4, -1);
    Link(test3, 3, 5, 6);
    Link(test3, 4, 7, -1);
    Link(test3, 5, -1, 8);
    findMax(test3);
    cout << "test3: " << nMaxn << endl;

    nMaxn=0;
    Node test4[9] = { 0 };
    Link(test4, 0, 1, 2);
    Link(test4, 1, 3, 4);
    Link(test4, 3, 5, 6);
    Link(test4, 5, 7, -1);
    Link(test4, 6, -1, 8);
    findMax(test4);
    cout << "test4: " << nMaxn << endl;

    return 0;
}




