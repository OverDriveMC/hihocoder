#include<bits/stdc++.h>

using namespace std;
/**
dp[k][v]表示使用了k个数和为v的方案数,那么对于新加入的一个数a,状态转移方程为:
	dp[k][v]+=dp[k-1][v-a]
注意要倒着写
同时注意vector的写法
*/
class Solution {
public:
    /*
     * @param A: An integer array
     * @param k: A positive integer (k <= length(A))
     * @param target: An integer
     * @return: An integer
     */
    int kSum(vector<int> &A, int k, int target) {
        vector<vector<int> >dp (k+1, vector<int>(target+1,0)) ;
		dp[0][0]=1;
		for(int i=0;i<A.size();i++){
			for(int j=k;j>0;j--){
				for(int m=target;m>=A[i];m--){
                    dp[j ][m]=max(dp[j][m],dp[j][m]+dp[j-1][m-A[i] ] );

				}
			}
		}
		return dp[k][target];
    }
};


int main(){
	Solution s;
	vector<int>A;
	A.push_back(1);
	A.push_back(2);
	A.push_back(3);
	A.push_back(4);
	printf("%d\n",s.kSum(A,2,5));

}
