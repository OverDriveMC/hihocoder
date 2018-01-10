import java.util.*;

/**
四个方向挨个统计一遍
分别统计 在同一行的个数、在同一列的个数、同一对角线的个数、同一反对角线的个数
定义四个map即可
最后  分别计算pairs   (count-1)*(count)/2
*/

public class Main{
	public static void main(String[]args){
		Map<Integer,Integer>rows=new HashMap<>();
		Map<Integer,Integer>columns=new HashMap<>();
		Map<Integer,Integer>diagonals=new HashMap<>();
		Map<Integer,Integer>reverses=new HashMap<>();
		
		Scanner stdin=new Scanner(System.in);
		int N=stdin.nextInt();
		for(int i=0;i<N;i++){
			int x=stdin.nextInt();
			int y=stdin.nextInt();
			
			add(rows,x);
			add(columns,y);
			add(diagonals,x-y);
			add(reverses,y+x);
		}
		System.out.println(calc(rows)+calc(columns)+calc(diagonals)+calc(reverses));
	}
	public static void add(Map<Integer,Integer>map,int val){
		if(map.get(val)==null){
			map.put(val,1);
		}else{
			map.put(val,map.get(val)+1);
		}
	}
	public static int calc(Map<Integer,Integer>map){
		int result=0;
		for(Map.Entry<Integer,Integer>me : map.entrySet()){
			result+=(me.getValue()- 1) * (me.getValue())/2;
		}
		return result;
	}
}
