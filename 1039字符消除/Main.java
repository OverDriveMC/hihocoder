/**
http://hihocoder.com/problemset/problem/1039
给定一个只包含大写字母"ABC"的字符串s，消除过程是如下进行的：
1)如果s包含长度超过1的由相同字母组成的子串，那么这些子串会被同时消除，余下的子串拼成新的字符串。
例如"ABCCBCCCAA"中"CC","CCC"和"AA"会被同时消除，余下"AB"和"B"拼成新的字符串"ABB"。
2)上述消除会反复一轮一轮进行，直到新的字符串不包含相邻的相同字符为止。例如”ABCCBCCCAA”经过一轮消除得到"ABB"，
再经过一轮消除得到"A"
游戏中的每一关小Hi都会面对一个字符串s。在消除开始前小Hi有机会在s中任意位置
(第一个字符之前、最后一个字符之后以及相邻两个字符之间)插入任意一个字符('A','B'或者'C')，得到字符串t。
t经过一系列消除后，小Hi的得分是消除掉的字符的总数。
请帮助小Hi计算要如何插入字符，才能获得最高得分。
输入:
	输入第一行是一个整数T(1<=T<=100)，代表测试数据的数量。
	之后T行每行一个由'A''B''C'组成的字符串s，长度不超过100。
输出:
	对于每一行输入的字符串，输出小Hi最高能得到的分数。
样例输入:
	3
	ABCBCCCAA
	AAA
	ABC
样例输出:
	9
	4
	2
*/


import java.util.Scanner;

public class Main {
	public static int getMaxn(String s) {
		int maxn = 0;
		StringBuilder sb = new StringBuilder();
		while (true) {
			int cnt = 0;
			while (cnt < s.length()) {
				int pos = cnt + 1;
				//注意这里可能下标越界
				while (pos<s.length() && s.charAt(pos) == s.charAt(cnt)) {
					pos++;
				}
				//pos记录第一个不重复的位置
				if (pos == cnt + 1) {
					sb.append(s.charAt(cnt));
					cnt++;
				} else {
					maxn += pos - cnt;
					cnt = pos;
				}
			}
			//直到字符不在减少为止
			if (s.length() == sb.length()) {
				break;
			}
			s = sb.toString();
			sb.delete(0, sb.length());
		}
		return maxn;
	}

	public static void main(String[] args) {
		Scanner stdin = new Scanner(System.in);
		int n = stdin.nextInt();
		while (n-- != 0) {
			int maxn = 0;
			String s = stdin.next();
			for (int i = 1; i < s.length(); i++) {
				//分别截取前后子串,同时在中间分别插入A,B,C计算每次消除的长度
				String before = s.substring(0, i + 1);
				String last = s.substring(i + 1);
				for (char mid = 'A'; mid <= 'C'; mid++) {
					maxn = Math.max(maxn, getMaxn(before + mid + last));
				}
			}
			System.out.println(maxn);
		}
	}
}