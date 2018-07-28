public class Solution {
    
    public List<String> convertToRPN(String[] expression) {
    	List<String>express=new ArrayList<>();
		Map<String,Integer>level=new HashMap<>();
		/**
		首先为每个操作符设定等级
		*/
		level.put("+",1);
		level.put("-",1);
		level.put("*",2);
		level.put("/",2);
		level.put("(",0);
		
		Stack<String>op=new Stack<>();
		for(String ele: expression){
			//考虑负数
			/**
			遇到数字直接存储
			*/
			if(ele.length()>1 || (ele.charAt(0)>='0' && ele.charAt(0)<='9')){
				express.add(ele);
			}else if(op.empty() || ele.charAt(0)=='('){
				/**
				当栈空或者元素为 ( 的时候直接入栈
				*/
				op.push(ele);
			}else if(ele.charAt(0)==')'){
				/**
				遇到 ) 时,出栈,直到栈顶元素等于 (
				*/
				while(!op.empty() && op.peek().charAt(0)!='('){
					express.add(op.pop());
				}
				//假如栈顶元素不是 (  , 说明有异常
				if(op.empty()){
					throw new RuntimeException();
				}
				op.pop();
			}else{
				/**
				当栈非空  并且栈顶元素的等级  >= 当前元素的等级的时候
				逐渐出栈,加入到后缀表达式中
				*/
				while(!op.empty() && level.get(op.peek() ) >=level.get(ele)  ){
					express.add(op.pop());
				}
				//最后将当前元素添加入栈
				op.push(ele);
			}
		}
		//最后要把栈清空
		while(!op.empty()) {
			express.add(op.pop());
		}
		return express;
    }
}