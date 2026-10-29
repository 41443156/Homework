#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
class Polynomial;
class Term {
	friend Polynomial;
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
        ~Polynomial();
		Polynomial() :capacity(2), terms(0) {
			termArray = new Term[capacity];
		}
        void  newTerm(const float theCoef, const int theExp);
		Polynomial Add(const Polynomial& b);
		Polynomial Mult(const Polynomial& b);
		float Eval(float x);
};
void  Polynomial::newTerm(const float theCoef, const int theExp) {
	if (theCoef == 0) {
		return;
	}
	if (terms == capacity) {
		capacity *= 2;
		Term* temp = new Term[capacity];
		copy(termArray, termArray + terms, temp);
		delete []termArray;
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
        c = c.Add(temp);
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

