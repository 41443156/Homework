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
    cin>>a>>b;
    cout<<"A(x)="<<a<<endl;
    cout<<"B(x)="<<b<<endl;
    cout<<"A+B="<<a.Add(b)<<endl;
    cout<<"A*B="<<a.Mult(b)<<endl;
    cout<<"A(2)="<<a.Eval(2)<<endl;
    return 0;
}


