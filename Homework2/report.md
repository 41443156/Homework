## 41443156
___
作業二
## 解題說明 
___
### 問題與描述：
第一題：ADT與私有資料成員實作Polynomial類別
	Polynomial():建構p(x)=0。
	Add:回傳兩個多項式的和。
	Mult:回傳兩個多項式的乘積。
	Eval:代入f求值並回傳結果。
第二題：重載“<<”與“>>”讓多項式可以直接用'cin>>p' 、'cout<<p'輸入和輸出。

### 解題策略：
儲存方式：把每一項係數跟指數放一起，多項式用Term動態陣列termArray儲存，只儲存非零項，然後還要指數由大到小排列。
陣列大小管理：NewTerm新增時，如果發現terms == capacity，就把容量加倍，建立新的陣列，並把舊的陣列裡面的資料複製過去。
Add:Ａ、Ｂ比較指數，指數大的先放入、指數相同係數相加、和為０不存入。
Mult:A的每一項乘Ｂ的每一項（係數相乘、指數相加），每得到一項就用Add，最後同指數自動合併。
Eval:每項迴圈連乘求f的exp次方，在乘以係數並累加。
輸入：先輸入項數n，再輸入n組的係數跟指數，每組呼叫NewTerm加入多項式。
輸出：顯示係數x＾指數，用＋連接。


## 程式實作
___
以下為主要程式碼：
```cpp
#include<iostream>
using namespace std;
class Polynomial; // 前向宣告

class Term {
friend Polynomial;//Polynomial可以存取coef exp
friend ostream& operator<<(ostream& os,const Polynomial& p);
private:
    float coef; // 係數
    int exp;    // 指數
};
class Polynomial {
public:
    Polynomial();//建構多項式 p(x) = 0。
    ~Polynomial();//解構子
    Polynomial(const Polynomial& other);//複製建構子
    Polynomial& operator=(const Polynomial& other);// 賦值運算子
    Polynomial Add(Polynomial poly);// 回傳多項式 *this 與 poly 的和。
    Polynomial Mult(Polynomial poly);// 回傳多項式 *this 與 poly 的乘積。
    float Eval(float f);// 將多項式 *this 代入 f 求值,並回傳結果。
private:
    Term *termArray; // 儲存非零項的陣列
    int capacity;    // termArray 的大小(容量)
    int terms;       // 非零項的個數
    void NewTerm(float c,int e);//在陣列後面加入一項(c,e)，如果不夠就擴充
    friend ostream& operator<<(ostream& os,const Polynomial& p);//允許輸出運算子讀取多項式內部資料
    friend istream& operator>>(istream& is,Polynomial& p);//允許輸入運算子讀取多項式內部資料
};
Polynomial::Polynomial(){//建構子
    terms=0;//預設鈴多項式有幾以個非零項
    capacity=1;//預設初始給一個格子
    termArray=new Term[capacity];//動態配置capacity個Term，
}
Polynomial::~Polynomial(){//解構子
    delete[] termArray;//釋放termArray用的位置
}
Polynomial::Polynomial(const Polynomial& other){//建立一個複製的Polynomial
    terms=other.terms;//複製terms
    capacity=other.capacity;//複製capacity
    termArray=new Term[other.capacity];//新的多項式配置陣列
    for (int i=0;i<terms;i++){//把termArray的係數跟指數複製過來
        termArray[i].coef=other.termArray[i].coef;
        termArray[i].exp=other.termArray[i].exp;
    }
}
void Polynomial::NewTerm(float c,int e){//新增一個多項式
    if (terms==capacity){//如果目前項數＝陣列容量，要擴充空間
        capacity=capacity*2;//容量加倍
        Term *temp=new Term[capacity];//建立新的陣列
        for(int i=0;i<terms;i++){//複製舊的陣列裡面的係數跟指數
            temp[i].coef=termArray[i].coef;
            temp[i].exp=termArray[i].exp;
        }
        delete[] termArray;//刪除就陣列
        termArray=temp;//termArray等於新陣列
    }
        termArray[terms].coef=c;
        termArray[terms].exp=e;
        terms+=1;
}
Polynomial Polynomial::Add(Polynomial b){//加法
    Polynomial c;
    int aPos=0,bPos=0;
    while (aPos<terms &&bPos<b.terms){//先比較兩個的多項跟指數
        if (termArray[aPos].exp>b.termArray[bPos].exp){//Ａ指數大於Ｂ把Ａ的項放入
            c.NewTerm(termArray[aPos].coef ,termArray[aPos].exp);
            aPos++;
        }
        else if (termArray[aPos].exp<b.termArray[bPos].exp){//Ｂ指數大於Ａ把Ｂ的項放入
            c.NewTerm(b.termArray[bPos].coef,b.termArray[bPos].exp);
            bPos++;
        }
        else{//如果ＡＢ指數相同時係數相加
            float sum =termArray[aPos].coef+b.termArray[bPos].coef;
            if (sum!=0){//係數相加不是0
                c.NewTerm(sum,termArray[aPos].exp);
            }
            aPos++;
            bPos++;
        }
    }
        for (;aPos<terms;aPos++){//Ａ剩下的項目加入
            c.NewTerm(termArray[aPos].coef ,termArray[aPos].exp);
        }
        for (;bPos<b.terms;bPos++){//Ｂ剩下的項目加入
            c.NewTerm(b.termArray[bPos].coef,b.termArray[bPos].exp);
        }
        return c;
}
Polynomial& Polynomial::operator=(const Polynomial& other){//賦值運算子多載
    if (this==&other){
        return *this;
    }
    delete[] termArray;//刪除舊的陣列
    capacity=other.capacity;
    terms=other.terms;
    termArray=new Term[capacity];//建立一個新的並且相同大小空間
    for(int i=0;i<terms;i++){//複製所有項目
        termArray[i].coef=other.termArray[i].coef;
        termArray[i].exp=other.termArray[i].exp;
    }
    return *this;
}
Polynomial Polynomial::Mult(Polynomial b){//乘法
    Polynomial result;
    for(int i=0;i<terms;i++){//A的每一項跟B的每一項相乘
        for (int j=0;j<b.terms;j++){
            Polynomial temp;
            float c=termArray[i].coef*b.termArray[j].coef;//係數相乘
            int e=termArray[i].exp+b.termArray[j].exp;//指數相加
            temp.NewTerm(c,e);
            result=result.Add(temp);
        }
    }
    return result;
}
float Polynomial::Eval(float f){//代入X數值求值
    float sum=0;
    for (int i=0;i<terms;i++){
        float p=1;
        for (int k =0;k<termArray[i].exp;k++){//計算f的exp次方
            p=p*f;
        }
        sum=sum+termArray[i].coef*p;
    }
    return sum;
}
ostream& operator<<(ostream& os,const Polynomial& p){//輸出多項式
	if (p.terms==0){//如果是零多項式輸出0
	    os<<"0";
	    return os;
    }
    for (int i=0;i<p.terms;i++){//輸出多項式每一項
        os<<p.termArray[i].coef<<"x^"<<p.termArray[i].exp;
        if (i<p.terms-1){//不是最後一項就顯示＋
            os<<"+";
        }
    }
    return os;
}
istream& operator>>(istream& is,Polynomial& p){//輸入多項式
    int n; 
    is>>n;//輸入項數
    p.terms=0;
    for (int i=0;i<n;i++){//輸入每一項的係數跟指數
        float c;
        int e;
        is>>c>>e;
        p.NewTerm(c,e);//輸入項目加入多項式
    }
    return is;
}
int main(){
    Polynomial a,b;
    float x;
    cin>>a>>b>>x;
    cout<<"A(x)="<<a<<endl;
    cout<<"B(x)="<<b<<endl;
    cout<<"A+B="<<a.Add(b)<<endl;
    cout<<"A*B="<<a.Mult(b)<<endl;
    cout<<"A("<<x<<")="<<a.Eval(x)<<endl;
    return 0;
}
```

## 效能分析
___
時間複雜度：

| 函式              |    時間複雜度    |                          說明                           |
| :-------------- | :---------: | :---------------------------------------------------: |
| NewTerm         |   攤銷O(1)    |        一般情況只需指定係數與指數;容量不足時才加倍擴充並複製資料,攤銷後仍為常數。         |
| Add             |   O(n+m)    |       兩個索引各走一次,每項最多處理一次;結果陣列擴充的成本攤銷後仍為 O(n+m)。        |
| Eval            |    O(nd)    |               每項以迴圈連乘計算 f^exp,最多 d 次乘法。               |
| operator<<      |    O(n)     |                        逐項輸出多項式                        |
| operator>>      |   攤銷O(n)    |                     讀入每一項並加入動態陣列。                     |
| 複製建構子、operator= |    O(n)     |                      依序複製係數跟指數。                       |
| Mult            | 最壞O((nm)^2) | 共nm次項目相乘，每次都呼叫Add()合併而result最壞到nm項，每次O(nm)，共O((nm)^2) |


空間複雜度：

| 函式     | 空間複雜度  | 說明                    |
| :----- | :----: | --------------------- |
| 一個多項式  |  O(n)  | 儲存非零項,容量最多為項數的 2 倍以內。 |
| Add結果  | O(n+m) | 需要額外陣列儲存相加結果。         |
| Mult結果 | O(n＊m) | 結果最多可能有nm個不同指數項目。     |
| 傳值參數   |  O(m)  | 傳值會複製一份Ｂ。             |


___
## 測試與驗證
___
### 測試案例

| 測試案例 |                    輸入                     |                                                              輸出                                                               |
| :--- | :---------------------------------------: | :---------------------------------------------------------------------------------------------------------------------------: |
| 測試一  |   A:2 3 5 3 1<br>B:3 12 5 3 3 5 1<br>2    |         A(x)=3x^5+3x^1<br>B(x)=12x^5+3x^3+5x^1<br>A+B=15x^5+3x^3+8x^1<br>A*B=36x^10+9x^8+51x^6+9x^4+15x^2<br>A(2)=102         |
| 測試二  | A:3 2 3 -1 2 5 0<br>B:3 1 3 1 2 -5 0<br>2 |         A(x)=2x^3+-1x^2+5x^0<br>B(x)=1x^3+1x^2+-5x^0<br>A+B=3x^3<br>A*B=2x^6+1x^5+-1x^4+-5x^3+10x^2+-25x^0<br>A(2)=17         |
| 測試三  |         A:0<br>B:2 -2 3 7 1<br>2          |                                A(x)=0<br>B(x)=-2x^3+7x^1<br>A+B=-2x^3+7x^1<br>A*B=0<br>A(2)=0                                 |
| 測試四  |     A:2 3 2 -4 0<br>B:2 -3 2 4 0<br>2     |                      A(x)=3x^2+-4x^0<br>B(x)=-3x^2+4x^0<br>A+B=0<br>A*B=-9x^4+24x^2+-16x^0<br>A(2)=8<br>                      |
| 測試五  |  A:5 1 4 1 3 1 2 1 1 1 0<br>B:1 1 0<br>2  | A(x)=1x^4+1x^3+1x^2+1x^1+1x^0<br>B(x)=1x^0<br>A+B=1x^4+1x^3+1x^2+1x^1+2x^0<br>A*B=1x^4+1x^3+1x^2+1x^1+1x^0<br>A(2)=31<br><br> |

```text
2 3 5 3 1
3 12 5 3 3 5 1
2
A(x)=3x^5+3x^1
B(x)=12x^5+3x^3+5x^1
A+B=15x^5+3x^3+8x^1
A*B=36x^10+9x^8+51x^6+9x^4+15x^2
A(2)=102

3 2 3 -1 2 5 0
3 1 3 1 2 -5 0
2
A(x)=2x^3+-1x^2+5x^0
B(x)=1x^3+1x^2+-5x^0
A+B=3x^3
A*B=2x^6+1x^5+-1x^4+-5x^3+10x^2+-25x^0
A(2)=17

0
2 -2 3 7 1
2
A(x)=0
B(x)=-2x^3+7x^1
A+B=-2x^3+7x^1
A*B=0
A(2)=0

2 3 2 -4 0
2 -3 2 4 0
2
A(x)=3x^2+-4x^0
B(x)=-3x^2+4x^0
A+B=0
A*B=-9x^4+24x^2+-16x^0
A(2)=8

5 1 4 1 3 1 2 1 1 1 0
1 1 0
2
A(x)=1x^4+1x^3+1x^2+1x^1+1x^0
B(x)=1x^0
A+B=1x^4+1x^3+1x^2+1x^1+2x^0
A*B=1x^4+1x^3+1x^2+1x^1+1x^0
A(2)=31


```
### 編譯與執行指令
```text
$ g++ -std=c++17 -o hw2 hw2.cpp 
$ ./hw2
```
### 結論
1. 程式可以正確完成多項式加法、乘法、求值。
2. 測試案例包含負係數、同指數係數相消、零多項式，輸出結果都正確。
3. 使用動態陣列，有完成解構子、複製建構子、賦值運算子。
4. 假設輸入的項指數未由大到小排列，而且沒有重複指數;若輸入為排序，加法和乘法不會正確。
## 申論及開發報告
---
這次作業用到比較多的動態陣列，而在做的時候很常忘記檢查陣列容量是否用滿，一開始在NewTerm()中，條件是寫terms>capacity，但是在terms == capacity時陣列空間就滿了 ，如果再新增一項會寫到’termArray[capacity]‘，改成terms == capacity才是正確的。最後是利用NewTerm()檢查陣列空間，容量不足就新增一個容量加倍的新陣列，並把舊的陣列複製過去。因為這次是用到動態陣列，所以要而外寫出解構子、複製建構子、賦值運算子，避免複製多項式的時候發生記憶體管理出問題。

Add部分是先比較兩個多樣式的指數，將指數叫大項目加入結果；如果指數相同，係數就相加。而在寫程式時return c;不小心放在while 迴圈內，導致迴圈只跑一輪就結束了。

Mult部分是用雙迴圈，將兩個多項式每一項互相相乘，最後用加法合併相同項目。寫程式時我把第二因子寫成‘termArray[j]'，忘記加‘b.’，這會變成B的索引去讀Ａ陣列，這樣會算錯，還會越界。

Eval求值是透過迴圈計算每一次的次方最後將所有結果加總。一開始我把內層次方迴圈條件寫‘k<f'，但迴圈次方數應該是要該項的指數exp，不是帶入f，這樣會多乘或是少乘，這邊我是用迴圈連乘實作。

經過這次的作業，我更加了解如何使用動態陣列以及如何透過類別管理多項式資料。過程中遇到陣列越界、迴圈提早結束、變數錯誤等問題。透過實際除錯我學會更加仔細檢查迴圈條件，陣列索引和程式執行位置，也對動態記憶體管理、運算子多載跟多項式加法與乘法有更深入了解。
