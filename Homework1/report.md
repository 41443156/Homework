## 41443156
___
作業一
## 解題說明 
___
### 問題與描述

1. Problem1 :
是關於阿克曼函數的公式
·A(m,n)=n+1 m=0
·A(m,n)=A(m-1,1) n=0
·A(m,n)=A(m-1,A(m,n-1)) m!=0,n!=0
規定需要完成使用*遞迴函式*跟*非遞迴函式*兩個Ackermann函式來設計。

2. Problem2 :
是關於Powerset，如果S是一個n個元素集合，Powerset(S)是S所有可能的子集合。
例如：S={a,b,c} Powerset(s)={{},{a},{b},{c},{a,b},{a,c},{b,c},{a,b,c}}
題目規定要使用遞迴函式來計算Powerset，找出所有可能的子集合。

### 解題策略：

*Problem1*
**遞迴函式:**
1.首先先判斷m是否等於0，是的話執行 n+1並把值回傳
2.如果m不等於0，但是n等於0，呼叫A(m-1,1)
3.最後m、n都不等於0的話用公式A(m-1,A(m,n-1))

**非遞迴函式：**
1.因為不能使用遞迴，所以使用陣列來模擬Stack
2.把資料放進去stack[top]後面讓top+1，取出資料後先讓top-1，再取出stack[top]。
3.使用top紀錄目前Stack的位置
4.再依照Ackermann的三個條件判斷下一步要處理的資料
5.一直處理到Stack裡沒有資料為止，最後回傳n的值

*Problem2*
1.先建立一個陣列s存放原本的集合
2.使用current陣列紀錄目前選到的元素
3.每處理一個元素時，都分成「選擇」跟「不選擇」兩種情況
4.如果不選擇目前元素，就直接繼續處理下一個元素
5.如果選擇目前元素，就先把元素放進current，再繼續處理下一個元素
6.當所有元素都處理完後，就把current裡面的元素輸出

## 程式實作
___
以下為主要程式碼：
*Problem1*
```cpp
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
int Ackermannnonrecursive(int m, int n) {//Ackermannnonrecursive函數定義
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
    while(scanf("%d %d",&a,&b)==2){//可以連續輸入多組a,b，並且確定輸入是兩個數字才會執行
	printf("Ackermann:%d\n", Ackermann(a, b));//將輸入得數值a,b帶回Ackermann函數，輸出結果
    printf("Ackermannnonrecursive:%d\n", Ackermannnonrecursive(a, b));//將輸入的數值a,b帶回Ackermannonrecursive函數，輸出結果
    }
	return 0;
}
```
*Problem2*
```cpp
#include<stdio.h>
void  powerset(char s[],char current[],int n,int index,int count){//宣告powerset函數 s是集合，current是目前選到的元素，n是有幾個元素，index是正在處理到第幾個元素，count是選了幾個元素
    if (index==n){//如果index=n代表全部元素處理完了
        printf("{");//因為完整輸出是{}所以要先輸出{
        for (int i=0;i<count;i++){
            printf ("%c",current[i]);//印出目前元素
            if (i<count-1){//代表還有元素還要處理
                printf(",");//不只輸出一個元素要用『,』隔開
            }
        }
        printf("}\n");//最後都處理完後輸出}
    }
    else{//代表還有沒處理完的元素
        powerset(s,current,n,index+1,count);//不選擇現在這個元素
        current[count]=s[index];//把目前的元素放入current
        powerset(s,current,n,index+1,count+1);//繼續處理下一個沒處理的元素
        }
    }
int main(){
    char s[]={'a','b','c'},current[10];//宣告s＝a,b,c current=10保留10個空間
    powerset(s,current,3,0,0);//呼叫s,current,3=三個元素,從第0個開始,現在選擇地0個元素
}
```

## 效能分析
___
*Problem1*
1. 時間複雜度：Ackermann函數會產生大量遞迴或Stack操作，隨著m、n增加，計算的量也會增加，因此用O(A(m,n))表示成長情況。
2. 空間複雜度：遞迴版本需要用函式呼叫堆疊；而非遞迴函式版本使用stack[1000]模擬Stack，因此目前程式固定陣列大小可視為O(1)。
*Problem2*
3. 時間複雜度：每個元素都有「選」跟「不選」兩種情況，所以共有2^n個子集合元素輸出，而且要將每個子集合中元素輸出，所以是O(n × 2^n)。
4. 空間複雜度：current陣列和遞迴函式跟n最相關，所以是O(n)。
___
## 測試與驗證
___
### 測試案例
*Problem1*

| 測試案例 | 輸入 m, n | 遞迴版本 | 非遞迴版本 |
| :--- | :-----: | :--: | :---: |
| 測試一  | m=1 n=1 |  3   |   3   |
| 測試二  | m=0 n=5 |  6   |   6   |
| 測試三  | m=1 n=0 |  2   |   2   |
| 測試四  | m=2 n=2 |  7   |   7   |


```text
1 1
Ackermann:3
Ackermannnonrecursive:3

0 5
Ackermann:6
Ackermannnonrecursive:6

1 0
Ackermann:2
Ackermannnonrecursive:2

2 2
Ackermann:7
Ackermannnonrecursive:7
```
測試解果可以看到，遞迴本版跟非遞迴版本的輸出結果是一樣的。

*Problem2*

| **測試案例** | **輸入集合**  | **預期子集合數量** | **實際子集合數量** |
| -------- | --------- | ----------: | ----------: |
| 測試一      | `{a,b,c}` |           8 |           8 |
```text
{}
{c}
{b}
{b,c}
{a}
{a,c}
{a,b}
{a,b,c}
```
因為輸入集合共有3個元素，所以Powerset應該有2^3 個子集合，實際輸出後也得到8個子集合，而且所有可能組合都有出現。

## 申論及開發報告
---
**Problem1:Ackermann**
剛開始做Ackermann遞迴版本時，用到了基本的if 、else if、else對我來說比較簡單，但是在做非遞迴函式時，遇到的問題是不知道不使用遞迴後，要怎麼保存還沒處理的資料，之後發現可以使用陣列來模擬Stack，再用top紀錄目前位置，讓資料去按照Stack方式放入跟取出。
測試非遞迴版本時，我用m=1、n=1測試，一開始遞迴版本的結果是3，非遞迴版本結果是2。之後我一個一個去看m、n、Stack的資料，發現n == 0的時候，m-1之後還需要把新的m放回Stack裡面，不然後面資料就不會繼續處理了。

**Problem2:Powerset**
在做Powerset時，第一個遇到的問題是要如何把Powerset(S,n-1)算出來的結果留給下一步使用，也不知道要怎麼記錄目前到底選了哪些元素。
例如 :處理a,b,c時，如果選a、不選b、選c，最後current裡面會是{a,c}，處理完所有元素後把current裡面的內容印出來，就可以得到其中一個子集合。
在理解提要求後，發現題目本身可以一直分成「選」和「不選」兩種情況，所以使遞迴來處理，比較容易找到的所有可能子集合。
Problem1 的非遞迴版本使用陣列來模擬Stack，因為原本地回在執行時會使用Call Stack，所以使用Stack可以保存沒有處理完的資料，讓非遞迴版本可以按照原本地回方式處理。
Problem2 使用地回來處理，因為每個元素都有「選」跟「不選」兩種情況，可以一直分成兩條路來找出所有可能的子集合。使用current陣列則是紀錄目前選到的元素，最後再輸出。
