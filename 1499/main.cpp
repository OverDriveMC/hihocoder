#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
const int maxn=1e5+5;
int arr[maxn][2];
int N;

int main(){
    scanf("%d",&N);
    int sum=0;
	for(int i=0;i<N;i++){
        for(int j=0;j<2;j++){
            scanf("%d",&arr[i][j]);
			sum+=arr[i][j];
        }
    }
	sum/=(N*2);
	/**
	upper记录上一轮A行多的
	down记录上一轮B行多的
	*/
	LL upper=0;
	LL down=0;
	LL seconds=0;
	for(int i=0;i<N;i++){
		/**
		* 先将upper down加到相应的位置
		*/
		arr[i][0]+=upper;
		arr[i][1]+=down;
		seconds+=abs(upper)+abs(down);
		upper=0;
		down=0;
		/**
		*  分两种情况,一种是当前A行的元素  >=sum (可以考虑往下移动)
		*  一种是当前A行的元素 < sum  (可以考虑将B行元素移回来)
		*/
		if(arr[i][0]>=sum){
			upper=arr[i][0]-sum;
			/**
			*  假如B行元素也大于sum,说明不需要移动,A行B行元素都可以往后移动
			*/
			if(arr[i][1]>=sum){
				down=arr[i][1]-sum;
			}else{
				/**
				假如B行元素小于sum,两种情况:
				一种是将A行多的元素移下来可以填补缺的元素
				一种是A行移下来的元素不够填补
				*/
				if(arr[i][1] + upper >=sum){
					upper-=sum-arr[i][1];
					seconds+=(sum-arr[i][1]);
				}else{
					seconds+=upper;
					down=-(sum-arr[i][1]-upper);
					upper=0;
				}
			}
		}else{
			/**
			* 当A行的元素  小于 sum的时候
			*/
			if(arr[i][1]>=sum){
				/**
				* 假如B行的元素 大于sum，
				*分两种情况：
				*    一种是B行多的元素可以填补A行缺的
				*    一种是B行多的元素不能够填补A行缺的
				*/
				down=arr[i][1]-sum;
				if(arr[i][0]+down <sum){
					upper=-(sum-arr[i][0]-down);
					seconds+=down;
					down=0;
				}else{
					seconds+=(sum-arr[i][0]);
					down-=sum-arr[i][0];
				}
			}else{
				///两行元素大小都  小于 sum
				/// 都需要从后一行搬运元素过来
				upper=arr[i][0]-sum;
				down=arr[i][1]-sum;
			}
		}
	}
	printf("%lld\n",seconds);

    return 0;
}
