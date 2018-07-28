/**
https://www.lintcode.com/problem/expression-evaluation/description
Example
For the expression 2*6-(23+7)/(1+2),
input is

[
  "2", "*", "6", "-", "(",
  "23", "+", "7", ")", "/",
  "(", "1", "+", "2", ")"
],
return 2
*/

public class Solution {
    /**
     * @param expression: a list of strings
     * @return: an integer
     */    
    public int evaluateExpression(String[] expression) {
        /**
		需要先判断表达式是否为空
		*/
        if(expression==null  || expression.length==0){
            return 0;
        }
		//将表达式转为后缀表达式
        List<String>express=trans(expression);
        return eval(express);
    }
    
    private int eval(List<String> express){
        
        Stack<Integer>res=new Stack<>();
        for(String ele: express){
            if(ele.length()>1 ||  (ele.charAt(0) >='0' && ele.charAt(0)<='9'  )  ){
                res.push(Integer.parseInt(ele) );
            }else{
				/**
				遇到表达式,将栈顶的两个元素出栈,做相应操作
				*/
                int second=res.pop();
                int first=res.pop();
                if(ele.charAt(0)=='+' ){
                    res.push(first+second);
                }else if(ele.charAt(0)=='-' ){
                    res.push(first-second);
                }else if(ele.charAt(0)=='*' ){
                    res.push(first*second);
                }else{
                    res.push(first/second);
                }
            }
        }
		//注意：可以栈为空   ((()))
        return res.empty()? 0 : res.pop();
    }
    
    private List<String> trans(String[]expression){
        Map<String,Integer>levels=new HashMap<>();
		/**
		注意 ( 也设上等级
		保证当 ( 为栈顶元素的时候,不会比任何其它的操作符等级高(栈顶元素因为表达式等级 >= 当前元素的时候会逐渐出栈
								最后可能栈顶会是  '('  )
		
		*/
        levels.put("+",1);
        levels.put("-",1);
        levels.put("*",2);
        levels.put("/",2);
        levels.put("(",0);
        
        
        Stack<String>op=new Stack<>();
        List<String>res=new ArrayList<>();
        for(String ele : expression){
        	System.out.println("ele:"+ele+"   op:"+op+"  res:"+res);
			//数字直接丢进结果List里面
            if(ele.length()>1 ||  (ele.charAt(0)>='0' && ele.charAt(0)<='9'  )  ){
                res.add(ele);
            }else if(op.empty() || ele.charAt(0)=='('  ){
				//当栈为空或栈顶元素为 '(' 的时候直接将操作符入栈
                op.push(ele);
            }else if(ele.charAt(0)==')' ){
				//遇到 ')' 时,需要将操作符逐渐出栈,直到遇到 '('
                while(!op.empty() && op.peek().charAt(0)!='('  ){
                    res.add(op.pop()) ;
                }
				//假如为空,说明括号不匹配
                if(op.empty()){
                    throw new RuntimeException("括号不匹配");
                }
				//最后将'('出栈
                op.pop();
            }else{
				//假如栈顶元素的操作符等级 >= 当前元素,那么逐渐出栈,直到 栈空 或栈顶元素操作符等级 < 当前元素
                while(!op.empty() && levels.get( op.peek() ) >= levels.get( ele   )){
                    res.add(op.pop());
                }
				//将当前元素入栈
                op.add(ele);
            }
        }
        while(!op.empty()){
            res.add(op.pop()) ;
        }
        return res;
    }
    
}