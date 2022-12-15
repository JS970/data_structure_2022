//소스 코드4.2: Circular Linked List - template 버젼으로 전환하기 
//head node를 갖고 circular list로서   class List{ private: Node *last;}로 구현하기
//난수가 입력되면 정렬된 list를 만든다.
//두개의 list를 merge하여 정렬된 list를 만든다.
// 출력은 iterator를 사용한다.
// class Node, List, ListIterator
#include <iostream>
#include <stdlib.h>
#include "time.h"
using namespace std;

template <class T>
class List;

template <class T>
class CircularListIterator;

template <class T>
class CircularList;

template <class T>
class Node
{
	friend List<T>;
	friend CircularListIterator<T>;
	friend CircularList<T>;
public:
	Node(T, Node*);
	~Node();
private:
	T data;
	Node* link;
};

template <class T>
Node<T>::Node(T element, Node* next)
{
	data = element;
	link = next;
}

template <class T>
Node<T>::~Node() {}

template <class T>
class CircularListIterator
{
public:
	CircularListIterator(const CircularList<T>& lst);
	~CircularListIterator();
	bool NotNull();
	bool NextNotNull();
	Node<T>* First();
	Node<T>* Next();
	Node<T>* Current();
	T* operator *() const;
	T& operator ->() const;
	CircularListIterator<T>& operator ++();
	CircularListIterator<T> operator ++(int);
	bool operator != (const CircularListIterator<T>) const;
	bool operator == (const CircularListIterator<T>) const;
	T GetCurrent();
private:
	Node<T>* current;
	const CircularList<T>& list;
};


template <class T>
T* CircularListIterator<T>::operator * () const
{
	return &(current->data);
}

template <class T>
T& CircularListIterator<T>::operator -> () const
{
	return current->data;
}

template <class T>
CircularListIterator<T>& CircularListIterator<T>::operator ++ ()
{
	current = current->link;
	return *this;
}

template <class T>
CircularListIterator<T> CircularListIterator<T>::operator ++ (int)
{
	CircularListIterator<T> old = *this;
	current = current->link;
	return old;
}

template <class T>
bool CircularListIterator<T>::operator != (const CircularListIterator<T>) const
{
	return current != right.current;
}

template <class T>
bool CircularListIterator<T>::operator == (const CircularListIterator<T>) const
{
	return current == right.current;
}

template <class T>
CircularListIterator<T>::CircularListIterator(const CircularList<T>& lst)
	: list(lst), current(lst.first)
{

}

template <class T>
bool CircularListIterator<T>::NotNull()
{
	if (list.first == 0) return false;
	else return true;
}

template <class T>
bool CircularListIterator<T>::NextNotNull()
{
	if (current->link != 0) return true;
	else return false;
}

template <class T>
Node<T>* CircularListIterator<T>::First()
{
	return list.first;
}

template <class T>
Node<T>* CircularListIterator<T>::Next()
{
	return current->link;
}

template <class T>
Node<T>* CircularListIterator<T>::Current()
{
	return current;
}

template <class T>
T CircularListIterator<T>::GetCurrent()
{
	return current->data;
}

template <class T>
class CircularList
{
	friend CircularListIterator<T>;
public:
	CircularList();
	~CircularList();
	virtual void Add(T&);
	virtual void Delete(T&);
	virtual void Show();
	virtual void DeleteData(T& x);
	void Merge(CircularList<T>&, CircularList<T>&);
	void Print_List();
private:
	Node<T>* first;
	Node<T>* last;
};

template <class T>
CircularList<T>::CircularList()
{
	first = 0;
	last = 0;
}

template <class T>
CircularList<T>::~CircularList()
{
	delete first;
	delete last;
}

template <class T>
void CircularList<T>::Add(T& x)
{
	// immediate sorting when add elements
	Node<T>* newNode = new Node<T>(x, 0);
	CircularListIterator<T>* itr = new CircularListIterator<T>(*this);
	if (first)
	{
		while (itr->Next()->data < x && (itr->Next() != itr->First())) ++(*itr);
		if (x < first->data) // new input number is smallest number in list
		{
			newNode->link = first;
			first = newNode;
			last->link = first;
		}
		else if (itr->Next() == last->link) // new input number is largest number in list
		{
			newNode->link = first;
			last->link = newNode;
			last = newNode;
		}
		else // new input number is going to insert between numbers in list
		{
			newNode->link = itr->Next();
			itr->Current()->link = newNode;
		}
	}
	else
	{
		first = newNode;
		last = newNode;
		newNode->link = first;
	}
}

template <class T>
void CircularList<T>::Delete(T& x)
{
	Node<T>* newNode = new Node<T>(x, 0);
	if (first)
	{
		Node<T>* Temp = first->link;
		first->link = first->link->link;
		delete Temp;
	}
	else
		cout << "empty list" << endl;
}

template <class T>
void CircularList<T>::DeleteData(T& x)
{
	//Node *newNode = new Node(x);
	//first, medium, last
	if (first) { //nonempty list
		Node<T>* CurrentNode = first;
		Node<T>* PreNode = first;
		bool find = false;

		// while (CurrentNode->link != first || CurrentNode == first)
		while (CurrentNode->link != first)
		{
			if (CurrentNode->data == x)
			{
				find = true;

				if (CurrentNode == first) // first delete case
				{
					Node<T>* Temp = CurrentNode;

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
			if (CurrentNode->data == x) // last Delte Case
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
void CircularList<T>::Merge(CircularList<T>& l1, CircularList<T>& l2)
{
	CircularListIterator<T>* itr1 = new CircularListIterator<T>(l1);
	CircularListIterator<T>* itr2 = new CircularListIterator<T>(l2);
	T x;
	bool empty = false;
	// itr2->Current() != l2.last
	while (1)
	{
		l2.first = itr2->Next();
		l2.last->link = l2.first;
		x = itr2->Current()->data;
		while (itr1->Next()->data < x && (itr1->Next() != itr1->First())) ++(*itr1);
		if (x < l1.first->data)
		{
			itr2->Current()->link = l1.first;
			l1.first = itr2->Current();
			l1.last->link = l1.first;
		}
		else if (itr1->Next() == l1.last->link)
		{
			itr2->Current()->link = l1.first;
			l1.last->link = itr2->Current();
			last = itr2->Current();
		}
		else
		{
			itr2->Current()->link = itr1->Next();
			itr1->Current()->link = itr2->Current();
		}
		if (empty)
		{
			l2.first = NULL;
			l2.last = NULL;
			break;
		}
		itr2 = new CircularListIterator<T>(l2);
		if (l2.first == l2.last) empty = true;
	}
}

template <class T>
void CircularList<T>::Print_List()
{
	CircularListIterator<T>* itr = new CircularListIterator<T>(*this);
	if (itr->Current() != NULL)
		do
		{
			cout << itr->GetCurrent() << " ";
			// (*itr)++ // not working
			++(*itr); // working...
		} while (itr->Next() != first->link);
	else cout << "List is empty" << endl;
	cout << endl;
}

template <class T>
void CircularList<T>::Show()
{
	Node<T>* np;
	np = first;
	if (np->data > 0)
		do
		{
			cout << np->data << " ";
			np = np->link;
		} while (np != first);
	else cout << "List is empty" << endl;
}

template <class T>
void Make_List(CircularList<T>& clist, int seed)
{
	srand(seed);
	for (int i = 0; i < 10; i++)
	{
		int tmp = (rand()) % 100;
		cout << "gen number #" << i  << " : "<< tmp << endl;
		clist.Add((T&)tmp);
	}
}

int main()
{
	CircularList<int> lst1;
	cout << "lst1 elements generation..." << endl;
	Make_List(lst1, 100);
	cout << endl;

	cout << "lst2 elements generation..." << endl;
	CircularList<int> lst2;
	Make_List(lst2, 200);
	cout << endl;

	cout << "Ordered CircularList lst1 : " << endl;
	lst1.Print_List();

	cout << endl << "Ordered CircularList lst2 : " << endl;
	lst2.Print_List();

	lst1.Merge(lst1, lst2);
	cout << endl << "Merged CircularList lst1 = lst1 + lst2 : " << endl;
	lst1.Print_List();

	return 0;
}
