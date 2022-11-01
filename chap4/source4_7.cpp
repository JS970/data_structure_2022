//소스코드4.7: Doubly Linked List - 교재 소스코드 

//12.Doubly Linked List Implementation with C++
//circular doubly lists with head node 구현- 이코드를 수정하여 사용, 두개의 list를 만들고 list node에 정수 값이 sorted된 상태로 입력되게 하고, 두개의 list를 merge하여 합친 결과도 sorted list되게 한다.
#include <iostream>
using namespace std;
template<class T> class CircularDoublyList;
template<class T> class CircularDoublyListIterator;
template<class T>
class DoublyListNode {
	friend class CircularDoublyList<T>;
	friend class CircularDoublyListIterator<T>;
	DoublyListNode();
	~DoublyListNode();
private:
	T data; //T를 term으로 사용 => coef, exp, variabl로 표현할 수 있을 것
	DoublyListNode<T>* llink, * rlink;
};
template<class T>
class CircularDoublyList {
	friend class CircularDoublyListIterator<T>;
public:
	// Head node를 사용하는 CircularDoublyList의 constructor
	CircularDoublyList() { first = new DoublyListNode<T>; last = first;  first->rlink = last; last->llink = first; first->data = -1; }
	CircularDoublyList(const CircularDoublyList<T>&);
	~CircularDoublyList();
	int Size()const;
	bool Empty()const;
	void Attach(T);
	void Delete(DoublyListNode<T>*);
	// void Insert(DoublyListNode<T>*, DoublyListNode<T>*); // node값 insert => 본 수업에서는 안쓰니까 지운다.
	void Insert(T); // 정수값 insert
	void Merge(CircularDoublyList<T>&);
	bool Delete(T);
	template<class T>
	friend ostream& operator<<(ostream&, CircularDoublyList<T>&);
private:
	int n; //number of items
	DoublyListNode<T>* first;
	DoublyListNode<T>* last;
	static DoublyListNode<T>* av;
};
template<class T>
class CircularDoublyListIterator {
public:
	CircularDoublyListIterator(const CircularDoublyList<T>& l) : list(l)
	{
		current = l.first->rlink;
	}
	T* Next();
	T* First();
	bool NotNull();
	bool NextNotNull();
	bool NotHead();
	bool NextNotHead();
private:
	const CircularDoublyList<T>& list;
	DoublyListNode<T>* current;
};

template<class T>
DoublyListNode<T>* CircularDoublyList<T>::av = 0;

template <class T>
DoublyListNode<T>::DoublyListNode(){ }

template <class T>
DoublyListNode<T>::~DoublyListNode() { }


template<class T>
void CircularDoublyList<T>::Delete(DoublyListNode<T>* x)
{
	if (x == first) cerr << "Deletion of head node not permitted" << endl;
	else {
		x->llink->rlink = x->rlink;
		x->rlink->llink = x->llink;
		delete x;
	}
}
/*
template<class T>
void CircularDoublyList<T>::Insert(DoublyListNode<T>* p, DoublyListNode<T>* x)
//insert node p to the right of node x
{
	p->llink = x;
	p->rlink = x->rlink;
	x->rlink->llink = p;
	x->rlink = p;
}
*/
// first 를 NULL로 설정하면 Insert에서 계속 first가 NULL인지 확인해야 하므로
// 첫 번째 노드 생성 시 first는 last를 last는 first를 가리키도록 한다.
// Insert function에 대해서 연습할 것
template<class T>
void CircularDoublyList<T>::Insert(T x) {
	DoublyListNode<T>* p, * temp = new DoublyListNode<T>();
	temp->data = x;
	p = first;

	while (true) {
		if (x < p->rlink->data)
		{
			temp->llink = p; temp->rlink = p->rlink;
			p->rlink->llink = temp; p->rlink = temp;
			break;
		}
		else if (p->rlink->data != -1)
			p = p->rlink;
		else {
			temp->llink = p; temp->rlink = p->rlink;
			p->rlink->llink = temp; p->rlink = temp;
			break;
		}
	}
	// Increase the number of nodes
	n++;
}
template<class T>
void CircularDoublyList<T>::Merge(CircularDoublyList<T>& b)
{
	CircularDoublyListIterator<T> it = CircularDoublyListIterator<T>(b);
	T tmp;
	// while (it.NextNotHead()) it.Next();
	this->Insert(*it.First());
	do
	{
		tmp = *it.Next();
		this->Insert(tmp);
	} while (it.NextNotHead());

	/*
	auto current = b.first->rlink;
	while (current != b.first)
	{
		this->Insert(current->data);
		current = current->rlink;

		if (current->llink != b.first)
			b.Delete(current->llink);
	}
	*/
}
template<class T>
bool CircularDoublyList<T>::Delete(T _data)
{
	for (DoublyListNode<T>* current = first; current->rlink->data != -1; current = current->rlink)
	{
		if (current->data == _data)
		{
			Delete(current);
			return true;
		}
	}
	return false;
}
template<class T>
int CircularDoublyList<T>::Size() const {
	return((first->data == -1) ? 0 : n);
}
template<class T>
bool CircularDoublyList<T>::Empty() const {
	return((first->data == -1) ? 1 : 0);
}

template<class T>
T* CircularDoublyListIterator<T>::First() {
	if (current != list.first) return &current->data;
	else return 0;
}

template<class T>
T* CircularDoublyListIterator<T>::Next() {
	current = current->rlink;
	if (current != list.first) return &current->data;
	else return 0;
}

template<class T>
bool CircularDoublyListIterator<T>::NotNull()
{
	if (current != list.first) return true;
	else return false;
}

template<class T>
bool CircularDoublyListIterator<T>::NextNotNull()
{
	if (current->rlink != list.first) return true;
	else return false;
}

template <class T>
bool CircularDoublyListIterator<T>::NotHead()
{
	if (current->data == -1) return false;
	else return true;
}

template <class T>
bool CircularDoublyListIterator<T>::NextNotHead()
{
	if (current->rlink->data != -1) return true;
	else return false;
}

template<class T>
CircularDoublyList<T>::CircularDoublyList(const CircularDoublyList<T>& l)
{
	if (l.first == 0) { first = 0; return; }
	first = new DoublyListNode<T>(l.first->data);
	DoublyListNode<T>* newnode = first;
	for (DoublyListNode<T>* current = l.first->link; current != l.first; current = current->link)
	{
		newnode->link = new DoublyListNode<T>(current->data);
		newnode = newnode->link;
	}
	newnode->link = first;
}


template<class T>
CircularDoublyList<T> ::~CircularDoublyList()
{
	if (first)
	{
		DoublyListNode<T>* second = first->rlink;
		first->rlink = av;
		av = second;
		first = 0;
	}
}

template<class T>
ostream& operator<<(ostream& os, CircularDoublyList<T>& l)
{
	CircularDoublyListIterator<T> li(l);
	if (!li.NotNull()) return os;
	os << *li.First();
	while (li.NextNotNull())
		os << " " << *li.Next();
	os << endl;
	return os;
}


template<class T>
void CircularDoublyList<T>::Attach(T k)
{
	DoublyListNode<T>* newnode = new DoublyListNode<T>(k);
	if (first == 0) first = last = newnode;
	else {
		newnode->link = last->link;
		last->link = newnode;
		last = newnode;
	}
}

void GetData(CircularDoublyList<float>& a, int count)
{
	for (int i = 0; i < count; i++)
	{
		a.Insert(rand() % 100);
	}
}

int main()
{
	char select = '0';

	CircularDoublyList<float> a, b;
	CircularDoublyListIterator<float> iter(a);

	float weight;
	while (select != 'q' || select != 'Q')
	{
		cout << endl << "Select command: a: Add to List a, b: Add to List b, d: Delete, m: Merge, p: PrintAll, q: exit" << endl;
		cin >> select;

		switch (select)
		{
		case 'a':
			cout << "List a에 10개의 난수 값을 입력... " << endl;
			// cin >> weight;
			GetData(a, 10);
			// a.Insert(weight);
			break;
		case 'b':
			cout << "List b에 10개의 난수 값을 입력... : " << endl;
			// cin >> weight;
			// b.Insert(weight);
			GetData(b, 10);
			break;
		case 'd':
			cout << "List a와 b에서 삭제할 값을 입력 : " << endl;
			cin >> weight;
			if (a.Delete(weight))
				cout << "List a에서" << weight << "값이 삭제됨." << endl;
			else
				cout << "List a에" << weight << "값이 없음." << endl;
			if (b.Delete(weight))
				cout << "List b에서" << weight << "값이 삭제됨." << endl;
			else
				cout << "List b에" << weight << "값이 없음." << endl;
			break;
		case 'm':
			// TODO : a+b
			cout << "List a와 List b를 Merge하여 List a에 저장..." << endl;
			a.Merge(b);
			break;
		case 'p':
			cout << "List a의 출력: " << endl;
			cout << a << endl;
			cout << "List b의 출력: " << endl;
			cout << b << endl;
			break;
		case 'q':
		case 'Q':
			cout << "Exit program.." << endl;
			system("pause");
			return 0;
		default:
			cout << "WRONG INPUT  " << endl;
			cout << "Re-Enter" << endl;
		}
	}

}

/* generalized linked list */
/*
	책 읽어보고 구현 연습해 볼 것
	꼭 해볼것
	tree구현 실습 이후에 연습해볼 것
*/