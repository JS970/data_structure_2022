//소스 코드4.1: Linked List
/*
template 사용 시에는 클래스 멤버 함수의 정의와 구현부를 *.h 파일과 *.cpp 파일로 분리할 수 없음. 하나의 file로 처리
- class Chain, class ChainIterator에 함수 추가하는 코딩 연습 필요
- template chain으로 circular list로서 head node가 있는 경우 구현
*/

#include <iostream>
using namespace std;

template<class T> class Chain; //forward declaration
template<class T> class ChainIterator;

template<class T> class ChainNode {
	friend class Chain<T>;
	friend class ChainIterator<T>;
public:
	ChainNode(T element = 0);
private:
	T data;
	ChainNode<T>* link;
};

template<class T> class Chain {
	friend class ChainIterator<T>;
public:
	Chain() { first = 0; };
	void Delete(void); //delete the first element after first
	int Length();
	void Add(const T& element); //add a new node after first
	void Invert();
	void Concatenate(Chain<T> b);
	template <class T>
	friend ostream& operator<<(ostream&, Chain<T>);//template <class T>포함해야 compiler가 처리
	//int Minimum( );
private:
	ChainNode<T>* first;
};

template<class T>
class ChainIterator {
public:
	ChainIterator(const Chain<T>& l) :list(l), current(l.first) { };
	//dereferencing operators
	T& operator *() const { return current->data; }
	T* operator->()const { return &current->data; }
	//increment
	ChainIterator<T>& operator ++(); //preincrement
	ChainIterator<T> operator ++(int); //post increment
	bool NotNull(); //check the current element in list is non-null
	bool NextNotNull();//check the next element in list is non-null

	T* First();     //return a pointer to the first element of list
	T* Next();  //return a pointer to the next element of list
private:
	const Chain<T>& list; //refers to an existing list
	ChainNode<T>* current; //points to a node in list
};

template<class T>
ChainNode<T>::ChainNode(T element)
{
	data = element;
	link = 0;
}

template<class T>
void Chain<T>::Delete(void) //delete the first element after first
{
	ChainNode<T>* current, * next;
	if (first != nullptr) //non-empty list
	{
		ChainNode<T>* temp = first;
		first = first->link;
		delete temp;
	}
	else
		cout << "Error - Empty List. not deleted" << endl;
}

/*
template<class T>
void Chain<T>::Add(const T& element) //add a new node after first
{
	ChainNode<T>* newnode = new ChainNode<T>(element);
	if (!first) //insert into empty list
	{
		first = newnode;
		return;
	}
	//insert a new node after first
	newnode->link = first;
	first = newnode;
}
*/

template <class T>
void Chain<T>::Add(const T& element)
{
	ChainNode<T>* newnode = new ChainNode<T>(element);
	if (!first)
	{
		first = newnode;
		return;
	}
	ChainNode<T>* p = first;
	if (p->link)
	{
		while (element < p->link->data && !(p->link)) p = p->link;
		if (element > p->link->data)
		{
			newnode->link = 0;
			p->link = newnode;
		}
		else
		{
			newnode->link = p->link;
			p->link = newnode;
		}
	}
	else
	{
		if (first->data < element)
		{
			first->link = newnode;
			newnode->link = 0;
		}
		else
		{
			newnode->link = first;
			first = newnode;
		}
	}
}
template<class T>
void Chain<T>::Invert() {
	ChainNode<T>* p = first, * q = 0; //q trails p
	while (p) {
		ChainNode<T>* r = q; q = p; //r trails q
		p = p->link; //p moves to next node
		q->link = r; //link q to preceding node
	}
	first = q;
}

template<class T>
void  Chain<T>::Concatenate(Chain<T> b) {
	ChainNode<T>* p;
	if (!first) { first = b.first; return; }
	if (b.first) {
		// No loop body in this for loop. It just moves the pointer 'p' to the end of the A chain.
		for (p = first; p->link; p = p->link);

		p->link = b.first;
	}
}

// pre-increment
template<class T>
ChainIterator<T>& ChainIterator<T>::  operator ++()
{
	current = current->link;
	return *this;
}

//post increment
template<class T>
ChainIterator<T> ChainIterator<T>:: operator ++(int)
{
	ChainIterator<T> old = *this;
	current = current->link;
	return old;
}

//check the current element in list is non-null
template<class T>
bool  ChainIterator<T>::NotNull() {
	if (current) return 1;
	else return 0;
}

//check the next element in list is non-null
template<class T>
bool   ChainIterator<T>::NextNotNull() {
	if (current && current->link) return 1;
	else return 0;
}

//return a pointer to the first element of list
template<class T>
T* ChainIterator<T>::First() {
	if (list.first) return &list.first->data;
	else return 0;
}

//return a pointer to the next element of list
template<class T>
T* ChainIterator<T>::Next() {
	if (current) {
		current = current->link;
		return &current->data;
	}
	else return 0;
}

/* chainiterator.cpp - iterator class를 사용하는 실습
 - template 사용시에 chain.h, chain.cpp => 바인딩 처리가 안됨 - visual studio2019의 문제
 - template 사용시에 하나의 file로 처리
 Chain iterator 실습 - TODO로 주석처리 되어 있는 부분을 직접 실습해 볼 것.
최대, 최소, 평균 등을 구하는 함수 작성 능력
*/


/* template function */
template <class T>
int Show(const Chain<T>& l) {
	ChainIterator<T> li(l); //li is associated with list l
	if (!li.NotNull()) return 0; //empty list, return 0
	T retvalue = *li.First();//get first element
	cout << retvalue;
	while (li.NextNotNull()) //make sure that next element exists 
	{
		retvalue = *li.Next();
		cout << " -> " << retvalue;
	}
	return retvalue;
}

template <class T>
int sum(const Chain<T>& l) {
	ChainIterator<T> li(l);    //li is associated with list l
	if (!li.NotNull()) return 0; //empty list, return 0
	T retvalue = *li.First();    //get first element
	while (li.NextNotNull())  //make sure that next element exists
		retvalue += *li.Next();
	return retvalue;
}

template <class T>
int SumProductFifth(const Chain<T>& l) {
	// sum(Xi * Xi+5)
	return 0;
}

template <class T>
int Length(const Chain<T>& l) {
	// list의 갯수
	return 0;
}

template <class T>
int Maximum(const Chain<T>& l) {
	// list에서 최대값
	return 0;
}

template <class T>
int Minimum(const Chain<T>& l) {
	// list에서 최소값
	return 0;
}

template <class T>
int MakeArray(const Chain<T>& l, int[]) {
	//list 원소를 읽어 배열에 저장
	return 0;
}

int main(void) {
	int select;
	//ChainNode<int> nd;
	Chain<int> a, b;
	int value;
	cin >> value;
	a.Add(value);
	cin >> value;
	a.Add(value);
	cin >> value;
	a.Add(value);
	cin >> value;
	a.Add(value);
	cin >> value;
	a.Add(value);
	ChainIterator<int> cit(a);
	cout << "a.first : " << *cit.First() << endl;
	Show(a);
	/*
	do
	{
		cout		<< "1. Add new value to chain 'A'" << endl << "2. Add new value to chain 'B'"
			<< endl << "3. Print all chains" << endl << "4. Invert chain"
			<< endl << "5. Concatenate A and B" << endl << "6. Delete first node in chain"
			<< endl << "7. Get Sum of the chain" << endl << "8. Get length of the chain"
			<< endl << "9. Get maximum value in chain" << endl << "10. Quit" << endl << endl;
		cout << "Select command (1~10) : ";
		cin >> select;
		switch (select)
		{
			// Case 1 : Add new value to chain 'A'
		case 1:
			cout << "Add a new value: ";
			cin >> value;
			a.Add(value);
			break;

			// Case 2 : Add new value to chain 'B'
		case 2:
			cout << "Add a new value: ";
			cin >> value;
			b.Add(value);
			break;

			// Case 3 : Print all chains
		case 3:
			cout << "Chain A : ";
			Show(a);
			cout << endl;
			cout << "Chain B : ";
			Show(b);
			cout << endl;
			break;

			// Case 4 : Invert chain
		case 4:
			cout << endl << "Which chain will you invert?" << endl << "1. Chain A" << endl << "2. Chain B" << endl << endl << "Select command (1~2) : ";
			cin >> value;
			if (value == 1)
				a.Invert();
			else if (value == 2)
				b.Invert();
			else
				cout << "Invalid value! Return to menu..." << endl;
			break;

			// Case 5 : Concatenate A and B
		case 5:
			cout << endl << "Concatenated chain" << endl;
			a.Concatenate(b);
			Show(a);
			cout << endl;
			break;

			// Case 6 : Delete first node in chain
		case 6:
			cout << endl << "Which chain will you delete?" << endl << "[1] Chain A" << endl << "[2] Chain B" << endl << endl << "Select command (1~2) : ";
			cin >> value;

			if (value == 1)
				a.Delete();
			else if (value == 2)
				b.Delete();
			else
				cout << "Invalid value! Return to menu..." << endl;
			break;

			// Case 7 : Get Sum of the chain
		case 7:
			cout << endl << "Which chain will you sum?" << endl << "1. Chain A" << endl << "2. Chain B" << endl << endl << "Select command (1~2) : ";
			cin >> value;

			if (value == 1)
				cout << sum(a) << endl;
			else if (value == 2)
				cout << sum(b) << endl;
			else
				cout << "Invalid value! Return to menu..." << endl;
			break;

			// Case 8 : Get length of the chain
		case 8:
			// TODO : Counting the number of nodes by using iterator class
			cout << endl << "Which chain's length do you want?" << endl << "[1] Chain A" << endl << "[2] Chain B" << endl << endl << "Select command (1~2) : ";
			cin >> value;

			if (value == 1)
				cout << Length(a) << endl;
			else if (value == 2)
				cout << Length(b) << endl;
			else
				cout << "Invalid value! Return to menu..." << endl;
			break;
			// Case 9 : Get maximum value in chain
		case 9:
			// TODO : Find node with maximum value by using iterator class
			cout << endl << "Which chain's max-value do you want?" << endl << "[1] Chain A" << endl << "[2] Chain B" << endl << endl << "Select command (1~2) : ";
			cin >> value;

			if (value == 1)
				cout << Maximum(a) << endl;
			else if (value == 2)
				cout << Maximum(b) << endl;
			else
				cout << "Invalid value! Return to menu..." << endl;
			break;

			// Case q : Quit the program
		case 10:
			cout << "Quit the program..." << endl;
			break;
		default:
			cout << "WRONG INPUT" << endl;
		}
	} while (select != 10);
	*/
	system("pause");
	return 0;
}