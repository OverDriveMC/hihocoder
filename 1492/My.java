import java.util.*;
import java.io.*;


class My{
	private static final int MOD=1000000007;
	public static void main(String[]args){			
		Scanner stdin=new Scanner(System.in);
		String line=stdin.next();
		Map<String,Integer>res=solve(line);
		int need1=res.get("need");
		int method1=res.get("method");
		///将字符串反转,并且将(变成),将)变成(,则是镜像问题
		StringBuilder sb=new StringBuilder(line);
		sb.reverse();
		for(int i=0;i<sb.length();i++){
			if(sb.charAt(i)=='('){
				sb.setCharAt(i,')');
			}else{
				sb.setCharAt(i,'(');
			}
		}
		res=solve(sb.toString());
		int need2=res.get("need");
		int method2=res.get("method");
		System.out.println((need1+need2)+" "+(method1*method2)%MOD);
	}
	public static Map<String,Integer> solve(String line){
		int left=0,right=0,need=0;
		List<Integer>tmpLeast=new ArrayList<Integer>();
		List<Integer>least=new ArrayList<Integer>();
		for(int i=0;i<line.length();i++){
			if(line.charAt(i)=='('){
				left++;
			}else{
				right++;
				if(right-left >need){
					need=right-left;
					tmpLeast.add(need);
					least.addAll(tmpLeast);
					tmpLeast.clear();
				}else if(right-left>0){
					tmpLeast.add(right-left);
				}else{
					tmpLeast.add(0);
				}
			}
		}
		
		Map<String,Integer>res=new HashMap<String,Integer>();
		res.put("need",need);
		if(need==0){
			res.put("method",1);
			return res;
		}
		/*
		for(int i=0;i<least.size();i++){
			System.out.println("i:"+i+"   "+least.get(i));
		}
		System.out.println("need:"+need);
		*/
		/**
		* dp[i][j]代表到i位置为止,最多插入j个(的方法数
		* dp[i][j] = 
		*			0   如果 j<least[i]
		*           dp[i-1][0]+dp[i-1][1]+...dp[i-1][j]
		*           即当前位置放j个,前面放0个的方法数
		*			当前位置放j-1个,前面放1个的方法数
		*           ...
		*           当前位置放0个,前面放j个的方法数
		*/
		int dp[][]=new int[least.size()][need+1];
		for(int i=0;i<=need;i++){
			if(i<least.get(0)){
				dp[0][i]=0;
			}else{
				dp[0][i]=1;
			}
		}
		for(int i=1;i<least.size();i++){
			for(int j=0;j<=need;j++){
				if(j<least.get(i)){
					dp[i][j]=0;
				}else{
					for(int k=0;k<=j;k++){
						dp[i][j]=(dp[i][j]+dp[i-1][k])%MOD;
					}
				}
			}
		}
		res.put("method",dp[least.size()-1][need]);
		//System.out.println("res:"+dp[least.size()-1][need]);
		return res;
	}
	
}
