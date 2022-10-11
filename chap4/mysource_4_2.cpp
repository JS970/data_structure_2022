#include <iostream>
using namespace std;

template <class T>
class List;

template <class T>
class ListIterator;

template <class T>
class CircularList;

template <class T>
class Node
{
	friend List<T>;
	friend ListIterator<T>;
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
	// (int element = 0, Node* next = 0)
	data = element;
	link = next;
}

template <class T>
Node<T>::~Node() {}

template <class T>
class List
{
	friend ListIterator<T>;
	friend CircularList<T>;
public:
	List();
	~List();
	virtual void Add(T);
	virtual void Delete(T&);
	virtual void Show();
	void Merge(List&, List&);
private :
	Node<T>* first;
};

template <class T>
List<T>::List()
{
	first = 0;
}

template <class T>
List<T>::~List()
{
	delete first;
}

template <class T>
void List<T>::Add(T x)
{
	if (!first)
	{
		first = new Node<T>(x, 0);
		first->link = 0;
	}
	else
	{
		Node<T>* n = new Node<T>(x, 0);
		n->link = first;
		first = n;
	}
}

template <class T>
void List<T>::Delete(T& x)
{
	if (first == NULL) cout << "List is empty" << endl;

	// body of Delete
	// TODO IMPLEMENT
}

template <class T>
void List<T>::Show()
{
	Node<T>* current;
	current = first;
	if (first)
		while (current)
		{
			cout << current->data << " ";
			current = current->link;
		}
	else cout << "List is empty" << endl;
}

template <class T>
class ListIterator : public CircularList<T>
{
public:
	ListIterator(const CircularList<T>& lst);
	~ListIterator();
	bool NotNull();
	bool NextNotNull();
	Node<T>* First();
	Node<T>* Next();
	Node<T>* Link();
	T* operator *() const;
	T& operator ->() const;
	ListIterator& operator ++();
	ListIterator operator ++(T);
	bool operator != (const ListIterator) const;
	bool operator == (const ListIterator) const;
	T GetCurrent();
private:
	Node<T>* current;
	const CircularList<T>& list;
};

template <class T>
T* ListIterator<T>::operator * () const
{
	return &current->data;
}

template <class T>
T& ListIterator<T>::operator -> () const
{
	return current->data;
}

template <class T>
ListIterator<T>& ListIterator<T>::operator ++()
{
	ListIterator<T> old = *this;
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
bool ListIterator<T>::operator != (const ListIterator<T>) const
{
	return current != right.current;
}

template <class T>
bool ListIterator<T>::operator == (const ListIterator<T>) const
{
	return current == right.current;
}

template <class T>
ListIterator<T>::ListIterator(const CircularList<T>& lst)
	: list(lst), current(lst.first)
{
	// cout << "CircularList Iterator is constructed" << endl;
}

template <class T>
bool ListIterator<T>::NotNull()
{
	if (list.first == 0) return false;
	else return true;
}

template <class T>
bool ListIterator<T>::NextNotNull()
{
	if (current->link != 0) return true;
	else return false;
}

template <class T>
Node<T>* ListIterator<T>::First()
{
	return list.first;
}

template <class T>
Node<T>* ListIterator<T>::Next()
{
	// cout << "current = " << current->data;
	return &(current->link);
}

template <class T>
Node<T>* ListIterator<T>::Link()
{
	return current->link;
}

template <class T>
T ListIterator<T>::GetCurrent()
{
	return current->data;
}

template <class T>
class CircularList : public List<T>
{
	friend ListIterator<T>;
public:
	CircularList();
	~CircularList();
	virtual void Add(T&);
	virtual void Delete(T&);
	virtual void Show();
	virtual void DeleteData(T& x);
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
	Node<T>* newNode = new Node<T>(x, 0);
	ListIterator<T>* itr = new ListIterator<T>(*this);
	if (first)
	{
		newNode->link = first;
		last->link = newNode;
		last = newNode;
	}
	else
	{
		first = newNode;
		last = newNode;
		newNode->link = newNode;
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

		//while (CurrentNode->link != first || CurrentNode == first)
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
void CircularList<T>::Show()
{
	/*
	Node<T>* np;
	np = first;
	if (np->data > 0)
		do
		{
			cout << np->data << " ";
			np = np->link;
		} while (np != first);
	else cout << "List is empty" << endl;
	*/
	ListIterator<T>* itr = new ListIterator<T>(*this);
	if (itr->GetCurrent() != NULL)
		do
		{
			cout << itr->GetCurrent() << " " << endl;
			itr++;
		} while (itr->Next() != itr->First());
	else cout << "List is empty" << endl;
}

int main()
{
	CircularList<int> lst;
	int input;
	cin >> input;
	lst.Add(input);
	cin >> input;
	lst.Add(input);
	cin >> input;
	lst.Add(input);
	lst.Show();

	return 0;
}