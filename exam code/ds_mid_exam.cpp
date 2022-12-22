//22.10.20 중간고사: Head Node를 사용하지 않는 circularChain의 구현
/*
- head node를 사용하지 않는다
- circular chain을 만들때 입력시에 정렬: 내림 차순으로 정렬한다
- 2개의 리스트를 merge할 때 새로운 list를 만들어 합병
- 출력은 operator<<()를 사용하여 구현: 출력 결과는 "list1 = [<k9,2000>, < ?, ?>, ....]"으로 출력한다.
*/


#include <iostream>
#include <string>
using namespace std;

class Product {
private:
	string Name;
	int price;
public:
	Product(string st, int pay) { Name = st; price = pay; }
	string& getname() { return Name; }
};
template<class T> class CircularChain; //forward declaration

template<class T>
class ChainNode {
	friend class CircularChain<T>;
public:
	ChainNode(T element)
	{
		data = element;
		link = 0;
	}
	ostream& operator<<<T>(ostream& os, ChainNode<T>& cn)
	{
		os << "data : " << data << endl;
		return os;
	}
private:
	T data;
	ChainNode<T>* link;
};

template<class T>
class CircularChain {
public:
	CircularChain() { first = 0; };
	~CircularChain();
	bool NotNull();
	bool NextNotNull();
	CircularChain<T>& Merge(CircularChain<T>&);
	void GetData(Product*, int);
	friend ostream& operator<<<T>(ostream&, CircularChain<T>&); //List 출력
private:
	int Add(const T& element); //add a new node after first
	ChainNode<T>* first; //point to the first node
};

template <class T>
bool CircularChain<T>::NotNull()
{
	if (first) return true;
	else return false;
}

template <class T>
bool CircularChain<T>::NextNotNull()
{
	if (first->link) return true;
	else return false;
}


template <class T>
ostream& operator<<(ostream& os, CircularChain<T>& cc) 
{
	ChainNode<T>* p = first;
	while (p->link->link)
	{
		os << p->data << " ";
		p = p->link;
	}
	return os;
}
template <class T>
CircularChain<T>::~CircularChain() { }

template<class T>
CircularChain<T>& CircularChain<T>::Merge(CircularChain<T>& b) {//this.Merge(b)
	// c = a + b => c = a.Merge(b)를 구현하는 함수
	//void Merge(CircularChain<T> b);
	CircularChain<T> mlist;


	return mlist;
}

template <class T>
int CircularChain<T>::Add(const T& element)
{
	ChainNode<T>* newnode = new ChainNode<T>(element);
	//circular list에 대하여 내림 차순으로 정렬하는 코드를 작성
	ChainNode<T>* p = first;
	/
	if (first->data.getname() < element.getname())
	{
		newnode->link = first;
		first = newnode;
		return 1;
	}
	else
	{
		while (element.getname() < p->data.getname() && (p->link)) p = p ->link;
		if (element.getname() < p->data.getname())
		{
			newnode->link = 0;
			p->link = newnode;
		}
		else
		{
			newnode->link = p->link;
			p->link = newnode;
		}
		return 1;
	}
	
	return 0;
}
template <class T>
void CircularChain<T>::GetData(Product* p, int sz) {
	int i = 0;
	while (i < sz) {//배열 갯수 만큼 loop
		Add(p[i++]);
	}
}



int main(void) {
	Product pdt1[] = { Product("K9", 6000),Product("G80", 6500),Product("K5", 4000),Product("SM3", 3000),Product("K8", 4500),Product("K3", 2000),Product("Sonata", 4300) };
	Product pdt2[] = { Product("Volvo", 9000),Product("Toyota", 5500),Product("Honda", 8800), Product("Tesla", 7000),Product("BMW", 7300),Product("Lexus", 6800),Product("Ford", 4900),Product("Lincoln", 12000),Product("Audi", 7700) };
	char select;
	CircularChain<Product> a, b, c;
	int count = 0;
	do {
		cout << endl << "Select command:1: list a의 입력,2: list b의 입력, 3: 출력, 4: merge sort, 5: Merge 출력, 6: quit" << endl;
		cin >> select;
		switch (select)
		{
		case '1':
			cout << "리스트 a 입력: ";
			count = sizeof pdt1 / sizeof pdt1[0];
			a.GetData(pdt1, count);//입력시에 Name으로 정렬한다.
			break;
		case '2':
			cout << "리스트 b 입력: ";
			count = sizeof pdt2 / sizeof pdt2[0];
			b.GetData(pdt2, count);//입력시에 Name으로 정렬한다.
			break;
			// Case 3 : Print all chains
		case '3':
			cout << "Chain A : ";
			if (a.NotNull()) cout << a;
			cout << endl;
			cout << "Chain B : ";
			if (b.NotNull()) cout << b;
			cout << endl;
			break;
		case '4':
			//a = a + b;
			c = a.Merge(b);//merge 결과도 Name으로 정렬이 되어야 한다.
			break;
		case '5':
			cout << "Chain C : ";
			if (c.NotNull()) cout << c;
			break;
		case '6':
			break;
		default:
			cout << "Re-Enter" << endl;
		}
	} while (select != '6');
	system("pause");
	return 0;
}
