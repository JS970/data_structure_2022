//소스 코드2.5: Polynomial 클래스
//template으로 구현하고 +, -, *, <<, >> operator를 사용한 버젼으로 구현한다.

#include <vector>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include "time.h"
using namespace std;

template <class T> class Polynomial;

template <class T>
class Term
{
	friend Polynomial<T>;
	template <class T>
	friend ostream& operator <<(ostream&, Polynomial<T>&);
private:
	T coef;
	int exp;
};

template <class T>
class Polynomial {
public:
	Polynomial();
	//construct the polynomial p(x) = 0;
	Polynomial Add(Polynomial b);
	void Substract(Polynomial a, Polynomial b);
	void Mult(Polynomial a, Polynomial b);

	Polynomial<T> operator+(Polynomial<T>& b)
	{
		Polynomial c;
		int aPos = start, bPos = b.start;
		c.start = free;
		while ((aPos <= finish) && (bPos <= b.finish))
			if ((termArray[aPos].exp == b.termArray[bPos].exp))
			{
				float t = termArray[aPos].coef + b.termArray[bPos].coef;
				if (t) c.NewTerm(t, termArray[aPos].exp);
				aPos++; bPos++;
			}
			else if ((termArray[aPos].exp < b.termArray[bPos].exp))
			{
				c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
				bPos++;
			}
			else
			{
				c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
				aPos++;
			}
		for (; aPos < finish; aPos++)
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
		for (; bPos < b.finish; bPos++)
			c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
		c.finish = free - 1;
		return c;
	}

	Polynomial operator - (Polynomial& b)
	{
		Polynomial c;
		int aPos = start, bPos = b.start;
		c.start = free;
		while ((aPos <= finish) && (bPos <= b.finish))
			if ((termArray[aPos].exp == b.termArray[bPos].exp))
			{
				float t = termArray[aPos].coef - b.termArray[bPos].coef;
				if (t) c.NewTerm(t, termArray[aPos].exp);
				aPos++; bPos++;
			}
			else if ((termArray[aPos].exp < b.termArray[bPos].exp))
			{
				c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
				bPos++;
			}
			else
			{
				c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
				aPos++;
			}
		for (; aPos < finish; aPos++)
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
		for (; bPos < b.finish; bPos++)
			c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
		c.finish = free - 1;
		return c;
	}
	Polynomial operator * (Polynomial& b)
	{
		Polynomial c;
		int aDeg = terms - 1; int bDeg = b.terms - 1;
		int aPos = start, bPos = b.start;
		float coef; int exp;
		c.start = free;
		int* tmp = new int[aDeg + bDeg + 1];
		for (int i = aDeg + bDeg; i >= 0; i--)
			tmp[i] = 0;
		for (int i = aDeg; i >= 0; i--)
		{
			bPos = b.start;
			for (int j = bDeg; j >= 0; j--)
				tmp[i + j] += termArray[aPos].coef * b.termArray[bPos++].coef;
			aPos++;
		}
		for (int i = aDeg + bDeg; i >= 0; i--)
			c.NewTerm(tmp[i], i);
		c.finish = free - 1;
		delete[] tmp;

		return c;
	}
	// Polynomial operator = (Polynomial&);
	//return the sum of the polynomials *this and b
	//Polynomial Mult(Polynomial b);
	//return the product of the polynomials *this and b
	//float Eval(float f);
	//evaluate the polynomial *this at f and return the result
	void NewTerm(const float theCoeff, const int theExp);
	int Display();
	int GetData();
	float Eval(float in);
	template <class T>
	friend ostream& operator <<(ostream&, Polynomial<T>&);
	template <class T>
	friend void operator >>(istream&, Polynomial<T>&);
private:
	static Term<T>* termArray;
	static int capacity;
	static int free;
	int start, finish;
	int terms;
};
template <class T>
Polynomial<T>::Polynomial()
{
	start = -1;
	finish = -1;
	terms = 0;
}

template <class T>
ostream& operator << (ostream& os, Polynomial<T>& a)
{
	int aPos = a.start;
	for (; aPos <= a.finish; aPos++) {
		os << a.termArray[aPos].coef << "x^" << a.termArray[aPos].exp;
		if ((aPos - a.finish) != 0)
			os << " + ";
	}
	os << "\n";
	return os;
}

template <class T>
void operator >> (istream&, Polynomial<T>& a)
{
	int i, degree;
	float coef;
	int expo;
	srand((unsigned int)time(NULL));
	cout << "Enter Degree Of Polynomial:";
	cin >> degree;
	a.start = a.free;
	//coef를 난수를 입력받아 사용하고 화면에서 입력받지 않는 버젼으로 수정한다.
	for (i = degree; i >= 0; i--) {
		// cout << "Enter coefficient of x^" << i << ":";
		expo = i;
		// cout << "Enter exponent of x^" << i << ":";
		coef = rand() % 10;
		a.NewTerm(coef, expo);
	}
	a.finish = a.free - 1;
	a.terms = a.finish - a.start + 1;

}

template <class T>
int Polynomial<T>::Display() {
	int aPos = start;
	for (; aPos <= finish; aPos++) {
		cout << termArray[aPos].coef << "x^" << termArray[aPos].exp;
		if ((aPos - finish) != 0)
			cout << " + ";
	}
	cout << "\n";
	return 0;
}

template <class T>
void Polynomial<T>::NewTerm(const float theCoeff, const int theExp)
{
	if (terms == capacity)
	{
		capacity *= 2;
		Term<T>* temp = new Term<T>[capacity];
		memcpy(temp, termArray, (sizeof(termArray) + sizeof(T) + sizeof(int)));
		delete[] termArray;
		termArray = temp;
	}
	termArray[free].coef = theCoeff;
	termArray[free++].exp = theExp;
}

template <class T>
int Polynomial<T>::GetData() {
	int i, degree;
	float coef;
	int expo;
	srand((unsigned int)time(NULL));
	cout << "Enter Degree Of Polynomial:";
	cin >> degree;
	start = free;
	//coef를 난수를 입력받아 사용하고 화면에서 입력받지 않는 버젼으로 수정한다.
	for (i = degree; i >= 0; i--) {
		// cout << "Enter coefficient of x^" << i << ":";
		expo = i;
		// cout << "Enter exponent of x^" << i << ":";
		coef = rand() % 10;
		NewTerm(coef, expo);
	}
	finish = free - 1;
	terms = finish - start + 1;
	return 0;
}

template <class T>
Polynomial<T> Polynomial<T>::Add(Polynomial b)
{
	Polynomial c;
	int aPos = start, bPos = b.start;
	c.start = free;
	while ((aPos <= finish) && (bPos <= b.finish))
		if ((termArray[aPos].exp == b.termArray[bPos].exp))
		{
			float t = termArray[aPos].coef + b.termArray[bPos].coef;
			if (t) c.NewTerm(t, termArray[aPos].exp);
			aPos++; bPos++;
		}
		else if ((termArray[aPos].exp < b.termArray[bPos].exp))
		{
			c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}
		else
		{
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			aPos++;
		}
	for (; aPos < finish; aPos++)
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	for (; bPos < b.finish; bPos++)
		c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
	c.finish = free - 1;
	return c;
}

template <class T>
void Polynomial<T>::Substract(Polynomial a, Polynomial b)
{
	int aPos = a.start, bPos = b.start;
	start = free;
	while ((aPos <= a.finish) && (bPos <= b.finish))
		if ((a.termArray[aPos].exp == b.termArray[bPos].exp))
		{
			float t = a.termArray[aPos].coef - b.termArray[bPos].coef;
			if (t) NewTerm(t, a.termArray[aPos].exp);
			aPos++; bPos++;
		}
		else if ((a.termArray[aPos].exp < b.termArray[bPos].exp))
		{
			NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			bPos++;
		}
		else
		{
			NewTerm(a.termArray[aPos].coef, a.termArray[aPos].exp);
			aPos++;
		}
	for (; aPos < a.finish; aPos++)
		NewTerm(a.termArray[aPos].coef, a.termArray[aPos].exp);
	for (; bPos < b.finish; bPos++)
		NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
	finish = free - 1;

}

template <class T>
void Polynomial<T>::Mult(Polynomial a, Polynomial b)
{
	int aDeg = a.terms - 1; int bDeg = b.terms - 1;
	int aPos = a.start, bPos = b.start;
	float coef; int exp;
	start = free;
	int* tmp = new int[aDeg + bDeg + 1];
	for (int i = aDeg + bDeg; i >= 0; i--)
		tmp[i] = 0;
	for (int i = aDeg; i >= 0; i--)
	{
		bPos = b.start;
		for (int j = bDeg; j >= 0; j--)
			tmp[i + j] += a.termArray[aPos].coef * b.termArray[bPos++].coef;
		aPos++;
	}
	for (int i = aDeg + bDeg; i >= 0; i--)
		NewTerm(tmp[i], i);
	finish = free - 1;
	delete[] tmp;
}

template <class T>
float Polynomial<T>::Eval(float in)
{
	int Pos = start;
	int pow;
	int sum = 0;
	for (int i = terms; i > 0; i--)
	{
		pow = 1;
		for (int j = 0; j < termArray[Pos].exp; j++)
			pow *= in;
		sum += termArray[Pos++].coef* pow;
	}
	return sum;
}

template <class T>
int Polynomial<T>::capacity = 100;

template <class T>
Term<T>* Polynomial<T>::termArray = new Term<T>[100];

template <class T>
int Polynomial<T>::free = 0;

int main(void) {
	int choice;

	Polynomial<int> P1, P2, P3, P4;
	cout << "Instruction:- \nExample:-\nP(x)=5x^3+3x^1\nEnter the Polynomial like\nP(x)=5x^3+0x^2+3x^1+0x^0\n";
	cout << "Enter Polynomial1:-" << endl;
	// P1.GetData();
	cin >> P1;
	cout << "Enter Polynomial2:-" << endl;
	// P2.GetData();
	cin >> P2;
	cout << "Enter Polynomial3:-" << endl;
	// P3.GetData();
	cin >> P3;
	while (1) {
		cout << "\n****** Menu Selection ******" << endl;
		cout << "1: Addition\n2: Substraction\n3: Multiplication\n4: Evaluation\n0: Exit" << endl;
		cout << "Enter your choice:";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "\n--------------- Addition ---------------\n";
			cout << "Polynomial1:";
			//P1.Display();
			cout << P1;
			cout << "Polynomial2:";
			P2.Display();
			//cout << P2;
			//cout << p3;
			cout << "Polynomial3:";
			// P3.Display();
			// P3 = P1.Add(P2);
			P3 = P1 + P2;
			P3.Display();
			// cout << P4;
			cout << "----------------------------------------\n";
			break;
		case 2:
			cout << "\n------------- Substraction -------------\n";
			cout << "Polynomial1:";
			// P1.Display();
			cout << P1;
			cout << "Polynomial2:";
			// P2.Display();
			cout << P2;
			P3.Substract(P1, P2);
			cout << "Polynomial3:";
			// P3 = P1 - P2;
			cout << P3;
			cout << "----------------------------------------\n";
			break;
		case 3:
			cout << "\n----------- Multiplication -------------\n";
			cout << "Polynomial1:";
			//P1.Display();
			cout << P1;
			cout << "Polynomial2:";
			//P2.Display( );
			cout << P2;
			// P3.Mult(P1, P2);
			P3 = P1 * P2;
			cout << "Polynomial3:";
			cout << P3;
			// P3.Display();
			cout << "----------------------------------------\n";
			break;
		case 4: 

			cout << "\n----------- Evaluation -------------\n";
			cout << "Equation is : ";
			cout << P2;
			cout << "P2.Eval(5) : ";
			cout << P2.Eval(5);
			//cout << P4;
			//P2.Eval(3);
			cout << "\n----------------------------------------\n";
			break;
		case 0:
			cout << "Good Bye...!!!" << endl;
			exit(0);
		}
	}
	system("pause");
	return 0;
}
