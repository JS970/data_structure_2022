//22.10.20 �߰����: Head Node�� ������� �ʴ� circularChain�� ����
/*
- head node�� ������� �ʴ´�
- circular chain�� ���鶧 �Է½ÿ� ����: ���� �������� �����Ѵ�
- 2���� ����Ʈ�� merge�� �� ���ο� list�� ����� �պ�
- ����� operator<<()�� ����Ͽ� ����: ��� ����� "list1 = [<k9,2000>, < ?, ?>, ....]"���� ����Ѵ�.
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
	friend ostream& operator<<<T>(ostream&, CircularChain<T>&); //List ���
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
	// c = a + b => c = a.Merge(b)�� �����ϴ� �Լ�
	//void Merge(CircularChain<T> b);
	CircularChain<T> mlist;


	return mlist;
}

template <class T>
int CircularChain<T>::Add(const T& element)
{
	ChainNode<T>* newnode = new ChainNode<T>(element);
	//circular list�� ���Ͽ� ���� �������� �����ϴ� �ڵ带 �ۼ�
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
	while (i < sz) {//�迭 ���� ��ŭ loop
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
		cout << endl << "Select command:1: list a�� �Է�,2: list b�� �Է�, 3: ���, 4: merge sort, 5: Merge ���, 6: quit" << endl;
		cin >> select;
		switch (select)
		{
		case '1':
			cout << "����Ʈ a �Է�: ";
			count = sizeof pdt1 / sizeof pdt1[0];
			a.GetData(pdt1, count);//�Է½ÿ� Name���� �����Ѵ�.
			break;
		case '2':
			cout << "����Ʈ b �Է�: ";
			count = sizeof pdt2 / sizeof pdt2[0];
			b.GetData(pdt2, count);//�Է½ÿ� Name���� �����Ѵ�.
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
			c = a.Merge(b);//merge ����� Name���� ������ �Ǿ�� �Ѵ�.
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
