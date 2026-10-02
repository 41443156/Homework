#include<stdio.h>
//遞迴版本
int Ackermann(int m, int n) {//Ackermann函數定義
	if (m == 0) {//如果m=0執行這段程式，如果不是就跳過不執行這段程式
		return n = n + 1;//執行n=n+1並把值傳回
	}
	else if (n == 0) {//如果n=0執行住段程式碼，如果不是就跳過不執行這段程式
		return Ackermann(m - 1, 1);//執行阿克曼函數
	}
	else {//上面兩點m!=0,n!=0的話，執行這段程式碼
		return Ackermann(m - 1, Ackermann(m, n - 1));//公式A(m-1,A(m,n-1))
	}
}
//非遞迴版本
int Ackermannnonrecursive(int m, int n) {//Ackermannnonrecursive非函數定義
	int stack[1000];//用陣列模擬堆疊
	int top = 0;//設定堆疊現在計入位置是在最底層0
	stack[top] = m;//將輸入的m放入堆疊
	top++;//因為第一個位置被放入m了所以要把位置往下一格
	while (top > 0) {//堆疊裡面如果還有數字就要繼續執行
		top--;//位置往回一格
		m = stack[top];//取出存在堆疊裡面的m數值
		if (m == 0) {//如果m=0執行這段程式碼，不是就跳過不執行
			n = n + 1;//執行n=n+1;
		}
		else if (n == 0) {//如果n=0的話執行這段程式，不是就跳過不執行
			m = m - 1;//執行m=m-1;
			n = 1;//把n預設為1
			stack[top] = m;//把新的m數值放回去原來的位置
			top++;//位置往下一格
		}
		else {//如果m!=0,n!=0就執行這段程式
			stack[top] = m-1;//把m-1放入堆疊裡面
			top++;//位置要往下一格
			stack[top] = m;//把m放入堆疊
			top++;//位置往下一格
			n = n - 1;//執行n-1
		}
	}
	return n;//最後把n的值傳回去

}
int main() {
	int a, b;//宣告整數a,b
	scanf("%d %d",&a,&b);//輸入數值a,b
	printf("%d\n", Ackermann(a, b));//將輸入得數值a,b帶回Ackermann函數，最後把結果輸出
	printf("%d\n", Ackermannnonrecursive(a, b));
	return 0;
}