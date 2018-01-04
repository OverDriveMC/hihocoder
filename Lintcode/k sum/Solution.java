/*
dp[i][j][t]:表示前i个数中,挑出t个数,组成和为j有多少种方案
dp[i][j][t]=dp[i-1][j-A[i]][t-1] +dp[i-1][j][t] 
 第i个数选或者不选
dp[i][0][0]=1
dp[0][A[0]][1]=1
初始化,将所有for循环没有考虑的条件初始化即可
最后返回:dp[n][target][k]

*/

public class Solution {
    /*
     * @param A: An integer array
     * @param k: A positive integer (k <= length(A))
     * @param target: An integer
     * @return: An integer
     */
    public int kSum(int[] A, int k, int target) {
        int dp[][][]=new int[A.length][target+1][k+1];
		for(int i=0;i<A.length;i++){
			dp[i][0][0]=1;
		}
		if(A[0]<=target){
			dp[0][ A[0] ][ 1]=1;
		}
		for(int i=1;i<A.length;i++){
			for(int j=0;j<=target;j++){
				for(int m=1;m<=k;m++){
					if(j >=A[i] ){
						dp[i][j][m]=Math.max(dp[i][j][m] , dp[i-1][j][m] + dp[i-1][j-A[i]][m-1] );
						//System.out.println("i:"+i+"  j:"+j+"  m:"+m+"   dp:"+dp[i][j][m]);
					}else{
						dp[i][j][m]=Math.max(dp[i][j][m] ,dp[i-1][j][m]);
					}
				}
			}
		}
		return dp[A.length-1][target][k];
    }
	/*
	public static void main(String[]args){
		Solution s=new Solution();
		int A[]={1,2,3,4};
		System.out.println(s.kSum(A,2,5) );
	}
	*/
}