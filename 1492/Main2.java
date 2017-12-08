import java.util.*;
import java.io.*;


class Main2{
	private static final int MOD=(int)1e9+7;
	public static void main(String[]args){
		Scanner stdin=new Scanner(System.in);
		String line=stdin.next();
		Map<String,Integer>res=new HashMap<>();
		res=solve(line);
		int need1=res.get("need");
		int method1=res.get("method");
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
		List<Integer>least=new ArrayList<Integer>();
		List<Integer>tmpLeast=new ArrayList<Integer>();
		int need=0;
		int left=0,right=0;
		for(int i=0;i<line.length();i++){
			if(line.charAt(i)=='('){
				left++;
			}else{
				right++;
				if(right-left>need){
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
		Map<String,Integer>map=new HashMap<>();
		map.put("need",need);
		if(need==0){
			map.put("method",1);
			return map;
		}
		///这里会自动初始化为0
		int dp[]=new int[need+1];
		dp[0]=1;
		int presum[]=new int[need+1];
		for(int i=0;i<least.size();i++){
			presum[0]=dp[0];
			/**
			* 构建一个前缀和,presum 计算dp[i-1][j]的前缀和
			* i代表位置, j代表插入的括号数
			*/
			for(int j=1;j<=need;j++){
				presum[j]=(presum[j-1]+dp[j])%MOD;
			}
			for(int j=0;j<=need;j++){
				if(j<least.get(i)){
					dp[j]=0;
				}else{
					dp[j]=presum[j];
				}
			}
		}
		//System.out.println("res:"+dp[need]);
		map.put("method",dp[need]);
		return map;
	}
	
}