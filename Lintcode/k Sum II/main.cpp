#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    /*
     * @param A: an integer array
     * @param k: a postive integer <= length(A)
     * @param targer: an integer
     * @return: A list of lists of integer
     */
    vector<vector<int> > kSumII(vector<int> &A, int k, int target) {
        vector<vector<int> >res;
		vector<int>vec;
		sort(A.begin(),A.end());
		dfs(res,A,k,target,0,vec,0);
		return res;
    }
	void dfs(vector<vector<int> >&res,const  vector<int>&A, int k,int target,int start, vector<int>vec,int sum ){
		if(sum==target && k==vec.size()){
			res.push_back(vec);
			return ;
		}

		if(start>=A.size()){
			return ;
		}
		if(vec.size()>k){
			return ;
		}

		dfs(res,A,k,target,start+1, vec,sum );
        vec.push_back(A[start]);
		dfs(res,A,k,target,start+1,vec,sum+A[start] );
	}
};


int main(){
	Solution s;
	vector<int>A;
	A.push_back(1);
	A.push_back(2);
	A.push_back(3);
	A.push_back(4);

	vector<vector<int> >res= s.kSumII(A,2,5);
	for(int i=0;i<res.size();i++){
		for(int j=0;j<res[i].size();j++){
			printf("%d ",res[i][j]);
		}
		printf("\n");
	}

}
