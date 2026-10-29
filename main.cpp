#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

class Polynomial;
class Term {
    friend class Polynomial;
private:
    float coef;
    int exp;
};

class Polynomial {
private:
    Term* termArray;
    int capacity;
    int terms;
public:
    Polynomial() : capacity(2), terms(0) {
        termArray = new Term[capacity];
    }

    // 補上三法則 (Rule of Three) 宣告，確保動態記憶體安全
    ~Polynomial();
    Polynomial(const Polynomial& h);
    Polynomial& operator=(const Polynomial& h);

    void newTerm(const float theCoef, const int theExp);
    Polynomial Add(const Polynomial& b);
    Polynomial Mult(const Polynomial& b);
    float Eval(float x);

    // 方便觀察結果的列印函數
    void display() const {
        if (terms == 0) {
            cout << "0" << endl;
            return;
        }
        for (int i = 0; i < terms; i++) {
            cout << termArray[i].coef << "x^" << termArray[i].exp;
            if (i < terms - 1) cout << " + ";
        }
        cout << endl;
    }
};

// --- 三法則實作 ---
Polynomial::~Polynomial() {
    delete[] termArray;
}

Polynomial::Polynomial(const Polynomial& h) : capacity(h.capacity), terms(h.terms) {
    termArray = new Term[capacity];
    copy(h.termArray, h.termArray + h.terms, termArray);
}

Polynomial& Polynomial::operator=(const Polynomial& h) {
    if (this != &h) {
        delete[] termArray;
        capacity = h.capacity;
        terms = h.terms;
        termArray = new Term[capacity];
        copy(h.termArray, h.termArray + h.terms, termArray);
    }
    return *this;
}
// -----------------

void Polynomial::newTerm(const float theCoef, const int theExp) {
    if (theCoef == 0) {
        return;
    }
    if (terms == capacity) {
        capacity *= 2;
        Term* temp = new Term[capacity];
        copy(termArray, termArray + terms, temp);
        delete[] termArray;
        termArray = temp;
    }
    termArray[terms].coef = theCoef;
    termArray[terms++].exp = theExp;
}

Polynomial Polynomial::Add(const Polynomial& b) {
    Polynomial c;
    int aPos = 0, bPos = 0;
    while ((aPos < terms) && (bPos < b.terms)) {
        if (termArray[aPos].exp == b.termArray[bPos].exp) {
            float t = termArray[aPos].coef + b.termArray[bPos].coef;
            if (t != 0) c.newTerm(t, termArray[aPos].exp);
            aPos++; bPos++;
        }
        else if (termArray[aPos].exp < b.termArray[bPos].exp) {
            c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        }
        else {
            c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
    }
    for (; aPos < terms; aPos++) {
        c.newTerm(termArray[aPos].coef, termArray[aPos].exp);
    }
    for (; bPos < b.terms; bPos++) {
        c.newTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
    }
    return c;
}

Polynomial Polynomial::Mult(const Polynomial& b) {
    Polynomial c;
    for (int aPos = 0; aPos < terms; aPos++) {
        Polynomial temp;
        for (int bPos = 0; bPos < b.terms; bPos++) {
            float newCoef = termArray[aPos].coef * b.termArray[bPos].coef;
            int newExp = termArray[aPos].exp + b.termArray[bPos].exp;
            temp.newTerm(newCoef, newExp);
        }
        c = c.Add(temp); // 這裡會安全地觸發 operator= 賦值
    }
    return c;
}

float Polynomial::Eval(float x) {
    float sum = 0.0;
    for (int i = 0; i < terms; i++) {
        sum += termArray[i].coef * pow(x, termArray[i].exp);
    }
    return sum;
}

int main() {
    Polynomial p1, p2;

    // p1 = 3x^2 + 2x^1
    p1.newTerm(3, 2);
    p1.newTerm(2, 1);

    // p2 = 1x^1 + 5x^0
    p2.newTerm(1, 1);
    p2.newTerm(5, 0);

    cout << "多項式 p1: "; p1.display();
    cout << "多項式 p2: "; p2.display();
    cout << "---------------------------------------" << endl;

    // 1. 測試相加
    Polynomial p_add = p1.Add(p2);
    cout << "p1 + p2 結果: "; p_add.display();

    // 2. 測試相乘 (3x^2 + 2x)(x + 5) = 3x^3 + 17x^2 + 10x
    Polynomial p_mult = p1.Mult(p2);
    cout << "p1 * p2 結果: "; p_mult.display();

    // 3. 測試求值 (代入 x = 2 到相乘結果中)
    // 3*(8) + 17*(4) + 10*(2) = 24 + 68 + 20 = 112
    cout << "當 x = 2 時，(p1 * p2) 的數值為: " << p_mult.Eval(2) << endl;

    return 0;
}
