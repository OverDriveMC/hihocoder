import java.util.*;
public class Main{
	public static void main(String[]args){
		Scanner stdin=new Scanner(System.in);
		long N=stdin.nextLong();
		long Q=stdin.nextLong();
		long M=1;
		long t=0;
		///先找到不要复制之后的数量
		while(N > 2 * Q * M){
			M=M*2;
			t+=Q;
		}
		///复制完成之后,采用M个机器人开始做任务
		t+= N/M;
		///假设不是M的倍数需要+1
		if(N%M!=0){
			t++;
		}
		
		System.out.println(t);
	}
}