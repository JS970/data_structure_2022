// 소스 코드4.2: Circular Linked List - template 버젼으로 전환하기 
// head node를 갖고 circular list로서   class List{ private: Node *last;}로 구현하기
// 난수가 입력되면 정렬된 list를 만든다.
// 두개의 list를 merge하여 정렬된 list를 만든다.
// 출력은 iterator를 사용한다.
// class Node, List, ListIterator
#include <iostream>
using namespace std;

template <class T>
class List;

template <class T>
class Node 
{
	friend class List<T>;
	friend class ListIterator<T>;
	friend class CircularList<T>;
public:
	Node(T, Node*);
	~Node();
private:
	T data;
	Node* link;
};

template <class T>
class List 
{
	friend class ListIterator;
	friend class CircularList;
public:
	List();
	List(Node<T> *, Node<T> *);
	~List();
	virtual void Add(T&);
	virtual void Delete(T&);//주어진 x 값을 갖는 노드를 삭제
	virtual void Show();
	//int Length( ); //count the number of nodes in a list
	void Merge(List&, List&); //the merged nodes in a sequential order
private:
	Node<T>* first;
	Node<T>* last; // added
};

template <class T>
class ListIterator 
{
public:
	ListIterator(const List& lst)
	{
		list = lst;
		current = lst.first;
		cout << "List Iterator is constructed" << endl;
	}
	~ListIterator();
	bool NotNull();
	bool NextNotNull();
	T* First();
	T* Next();
	T& GetCurrent();
	ListIterator& operator++(); //Next( )
	ListIterator operator ++(T);
	T& operator*() const;
	T* operator->()const;
	bool operator != (const ListIterator) const;
	bool operator == (const ListIterator) const;
private:
	Node<T>* current; //pointer to nodes
	const List<T>& list;//existing list
};

template <class T>
class CircularList : public List<T> // List class를 CircularList class의 public member로 사용하겠다는 선언 
{
public:
	CircularList();
	~CircularList();
	void Add(T&);
	void Delete(T&);
	void DeleteData(T& x);
	void Show();
};

template <class T>
Node<T>::Node(T element, Node* next) 
{
	data = element;
	link = next;
}

template <class T>
Node<T>::~Node() 
{
	delete current;
}

template <class T>
List<T>::List()
{
	first = 0;
	last = 0;
}

template <class T>
List<T>::List(Node<T>* fst, Node<T>* lst) 
{
	first = fst;
	last = lst;
}

template <class T>
List<T>::~List() 
{
	delete first;
	delete last;
}

template <class T>
void List<T>::Add(T& x)
{
	if (!first) // empty list
	{
		first = new Node<T>(x);
		first->link = 0;
		last->link = 0; // 리스트에 노드가 하나밖에 없으므로 시작이자 끝.
	}
	else 
	{
		Node<T>* n = new Node<T>(x);
		ListIterator<T> iter(this);
		while (iter.GetCurrent() <= x && iter.NextNotNull()) iter++;
		if (iter.NextNotNull())
		{
			iter++->link = n;
			n->link = ++iter;
		}
		else
		{
			iter++->link = n;
			n->link = 0;
			last = n;
		}
		delete iter;
	}
}

template <class T>
void List<T>::Delete(T& x) {
	if (first == NULL) cout << " List is empty" << endl;
	else
	{
		// body of delete
		// Listiterator사용해서 x탐색 후 삭제...?
	}
	return;

}

template <class T>
void List<T>::Show() {
	Node<T>* current;
	current = first;
	if (first)
	{
		while (current)
		{
			cout << current->data << " ";
			current = current->link;
		}
		cout << endl;
	}
	else cout << "List is empty" << endl;
}

template <class T>
void List<T>::Merge(List& l1, List& l2)
{
	// TODO implement
}

/*
ListIterator::ListIterator(Node *ll){
}
*/


// ListIterator(const List& lst);
/* template <class T>
ListIterator<T>::ListIterator(const List& lst)
{
	list = lst;
	current = lst.first;
	cout << "List Iterator is constructed" << endl;
}
*/

template <class T>
ListIterator<T>::~ListIterator()
{

}

template <class T>
bool ListIterator<T>::NotNull() {
	if (list.first == 0) return false;
}

template <class T>
bool ListIterator<T>::NextNotNull() {
	if (current->link != 0) return true;
	else return false;
}

template <class T>
T* ListIterator<T>::First() {
	return &list.first->data;
}

template <class T>
T* ListIterator<T>::Next() {
	current = current->link;
	cout << "current = " << current->data;
	return &current->data;
}

template <class T>
T& ListIterator<T>::GetCurrent() 
{
	return &current->data;
}

template <class T>
ListIterator<T>& ListIterator<T>::operator++()
{
	ListIterator old = *this;
	current = current->link;
	return old;
}

template <class T>
ListIterator<T> ListIterator<T>::operator ++(T)
{
	current = current->link;
	return *this;
}

template <class T>
T& ListIterator<T>::operator*() const 
{
	return current->data;
}

template <class T>
T* ListIterator<T>::operator->()const 
{
	return &current->data;
}

template <class T>
bool ListIterator<T>::operator != (const ListIterator right) const 
{
	return current != right.current;
}

template <class T>
bool ListIterator<T>::operator == (const ListIterator right) const 
{
	return current == right.current;
}

template <class T>
CircularList<T>::CircularList() : List() 
{

}

template <class T>
CircularList<T>::~CircularList() 
{

}

template <class T>
void CircularList<T>::Add(T& x) 
{
	Node<T>* newNode = new Node(x);
	if (first) { //nonempty list
		newNode->link = first->link;
		first->link = newNode;
	}
	else { //empty list
		first = newNode;
		newNode->link = newNode;
	}
}

template <class T>
void CircularList<T>::Delete(T& x) 
{
	Node* newNode = new Node(x);
	if (first) { //nonempty list
		Node* Temp = first->link;
		first->link = first->link->link;
		delete Temp;
	}
	else { //empty list
		cout << "empty list" << endl;
	}
}

template <class T>
void CircularList<T>::DeleteData(T& x) 
{
	//Node *newNode = new Node(x);
	//first, medium, last
	if (first) { //nonempty list
		Node* CurrentNode = first;
		Node* PreNode = first;
		bool find = false;

		//while (CurrentNode->link != first || CurrentNode == first)
		while (CurrentNode->link != first)
		{
			if (CurrentNode->num == x)
			{
				find = true;

				if (CurrentNode == first) // first delete case
				{
					Node* Temp = CurrentNode;

					while (CurrentNode->link != first)
					{
						CurrentNode = CurrentNode->link;
					}
					first = first->link;
					delete Temp;

					CurrentNode->link = first;
					break;
				}
				else if (CurrentNode->link != first) // medium delete case
				{
					PreNode->link = CurrentNode->link;
					delete CurrentNode;
					break;
				}
			}

			PreNode = CurrentNode;
			CurrentNode = CurrentNode->link;
		}//while end

		if (find == false)
		{
			if (CurrentNode->num == x) // last Delte Case
			{
				PreNode->link = first;
				delete CurrentNode;
				find = true;
			}

		}
		if (find == false)
			cout << "can't find " << x << endl;
	}
	else { //empty list
		cout << "empty list" << endl;
	}

}

template <class T>
void CircularList<T>::Show() 
{
	Node* np;
	np = first;
	if (np->num > 0)
		do
		{
			cout << np->num << " ";
			np = np->link;
		} while (np != first);
	else cout << "List is empty" << endl;
}

/* listIteratorTest.cpp - List Iterator를 사용
- Add( )에서 학생들이 실습할 코드로
  1) add된 데이터를 last node로 추가하는 코드 작성,
  2) 입력된 값이 sort되도록 add( )를 수정
  3) sum(xi * xi+5)를 구하는 코드 작성



//int printAll(const List& l);//list iterator를 사용하여 작성하는 연습
//int sumProductFifthElement(const List& l);//list iterator를 사용하여 작성하는 연습
int sum(const List& l)
{
	ListIterator li(l);
	if (!li.NotNull()) return 0;
	int retvalue = *li.First();
	while (li.NextNotNull() == true) {
		++li;//current를 증가시킴
		//retvalue = retvalue + *li.Next( );
		retvalue = retvalue + *li.GetCurrent();//현재 current가 가르키는 node의 값을 가져옴
	}
	return retvalue;
}

double avg(const List& l)
{
	ListIterator li(l);
	if (!li.NotNull()) return 0;
	int retvalue = *li.First();
	int count = 1;
	while (li.NextNotNull() == true) {
		++li;
		count++;
		//retvalue = retvalue + *li.Next( );
		retvalue = retvalue + *li.GetCurrent();
	}

	double result = (double)retvalue / count;

	return result;
}

int min(const List& l)
{
	ListIterator li(l);
	if (!li.NotNull()) return -1;
	int minValue = *li.First();

	while (li.NextNotNull() == true) {
		++li;
		if (minValue > *li.GetCurrent())
		{
			minValue = *li.GetCurrent();
		}
	}
	return minValue;
}

int max(const List& l)
{
	ListIterator li(l);
	if (!li.NotNull()) return -1;
	int maxValue = *li.First();

	while (li.NextNotNull() == true) {
		++li;
		if (maxValue < *li.GetCurrent())
		{
			maxValue = *li.GetCurrent();
		}
	}
	return maxValue;
}

void ListTesting() {
	int ch;
	List st;
	while (1)
	{
		cout << "\n1.Add  2.Delete  3.Show  4. sum 5.avg 6.min 7.max 8.exit\nEnter ur choice: ";
		cin >> ch;
		switch (ch)
		{
		case 1:  cout << "enter the element ";
			cin >> ch;
			st.Add(ch);
			break;
		case 2:  st.Delete(ch);  break;
		case 3:  st.Show(); break;
		case 4:  cout << "sum( ) = " << sum(st) << endl; break;
		case 5:  cout << "avg( ) = " << avg(st) << endl; break;
		case 6:  cout << "min( ) = " << min(st) << endl; break;
		case 7:  cout << "max( ) = " << max(st) << endl; break;
		case 8:  return;
		}
	}

	return;
}
*/

void main() {

	List<int> lst;
	int input;
	cin >> input;
	lst.Add(input);
	cin >> input;
	lst.Add(input);
	cin >> input;
	lst.Add(input);
	lst.Show();
	/*
	cout << endl << "List Testing begins: " << endl;
	CircularList<int> st[4];
	
	while (1)
	{
		cout << "\n1.Make_List1  2.Make_List 3.Merge  4.Print_List  5.exit\nEnter ur choice: ";
		cin >> ch;
		switch (ch)
		{
		case 1:
			cout << "Make List1" << endl;
			Make_List(st[0]);
			break;
		case 2:
			cout << "Make List2" << endl;
			Make_List(st[1]);
			break;
		case 3:
			cout << "Merge" << endl;
			st[2] = st[0].Merge(st[1]);
			break;
		case 4:
			cout << "Print list" << endl;
			Print_List(st[0]);
			Print_List(st[1]);
			Print_List(st[3]);
			break;
		case 5:	return;
		}
	}
	*/
	system("Pause");
}