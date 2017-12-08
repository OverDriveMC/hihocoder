import java.util.*;
import java.io.*;

public class Main {
    public static void main(String[] args) throws Exception{
        //Scanner scanner = new Scanner(new FileInputStream("1.txt"));
		Scanner scanner = new Scanner(System.in);
        String str1 = scanner.nextLine();
        scanner.close();
        Map<String, Integer> part1 = getNeedAndMethods(str1);
        int need1 = part1.get("need"), methods1 = part1.get("methods");
        StringBuffer str2 = new StringBuffer(str1);
        str2.reverse();
        for (int i = 0; i < str2.length(); i++) {
            if (str2.charAt(i) == '(')
                str2.setCharAt(i, ')');
            else
                str2.setCharAt(i, '(');
        }
        Map<String, Integer> part2 = getNeedAndMethods(str2.toString());
        int need2 = part2.get("need"), methods2 = part2.get("methods");
        System.out.println((need1 + need2) + " " + (methods1 * methods2) % 1000000007);
    }

    static Map<String, Integer> getNeedAndMethods(String string) {
		System.out.println(string);
        Map<String, Integer> result = new HashMap<>();
        int left = 0, right = 0, need = 0;
        char[] strs = string.toCharArray();
        List<Integer> least = new ArrayList<>();
		List<Integer> tmpLeast = new ArrayList<>();
        for (char ch : strs) {
            if (ch == '(')
                left++;
            else {
                right++;
                if (right - left > need) {
					/**
					定义tmpLeast的意义在于
					 ()))((()
					只记录 )比 ( 多的情况
					假如少于,则不记录
					*/
                    need = right - left;
                    tmpLeast.add(need);
                    least.addAll(tmpLeast);
                    tmpLeast.clear();
                } else if (right - left > 0)
                    tmpLeast.add(right - left);
                else
                    tmpLeast.add(0);
            }
        }

        result.put("need", need);
        if (need == 0) {
            result.put("methods", 1);
            return result;
        }
		
		/*
			通过least依次记录下每个 ) 的位置之前至少要添加的 (  的数量
		*/
		for(int i=0;i<least.size();i++){
			System.out.println("i:"+i+"   least:"+least.get(i));
		}
		
        int[] dp = new int[need + 1];
        dp[0] = 1;
        for (Integer insert : least) {
            int[] preSum = new int[need + 1];
            preSum[0] = dp[0];
            for (int i = 1; i <= need; i++) {
                preSum[i] = (preSum[i - 1] + dp[i]) % 1000000007;
            }
            for (int i = 0; i <= need; i++) {
                if (i < insert)
                    dp[i] = 0;
                else
                    dp[i] = preSum[i];
            }
        }
        result.put("methods", dp[need]);
		System.out.println("res:"+dp[need]);
        return result;
    }
}