#include <iostream>
using namespace std;

template <class T> class Chain;

template <class T>
class ChainNode
{
    friend class Chain<T>;
public:
    ChainNode (T element = 0);
private:
    T data;
    ChainNode<T>* link;
};

template <class T>
ChainNode<T>::ChainNode(T element)
{
    data = element;
    link = 0;
}


template <class T>
class Chain
{
public:
    Chain();
    void Delete();
    int Length();
    void Add(const T& element);
    void Invert();
    void Concatenate(Chain<T> b);
    void Display();
private:
    ChainNode<T> *first;
};

template <class T>
Chain<T>::Chain()
{
    first = 0;
}

template <class T>
void Chain<T>::Delete()
{
    ChainNode<T>* tmp = first;
    first = first->link;
    delete tmp;
}

template <class T>
int Chain<T>::Length()
{
    ChainNode<T>* p = first;
    int len = 0;
    while(p->link) 
    {
        p = p->link;
        len++;
    }
    return len+1;
}

template <class T>
void Chain<T>::Add(const T& element)
{
    ChainNode<T>* newnode = new ChainNode<T>(element);
    newnode->link = first;
    first = newnode;
}

template <class T>
void Chain<T>::Invert()
{
    ChainNode<T> *p = first;
    ChainNode<T> *q;
    ChainNode<T> *r = 0;
    while(p)
    {
        q = p;
        p = p->link;
        q->link = r;
        r = q;
    }
    first = q;
}

template <class T>
void Chain<T>::Concatenate(Chain<T> b)
{
    ChainNode<T>* p = first;
    while(p->link) p = p->link;
    p->link = b.first;
}

template <class T>
void Chain<T>::Display()
{
    ChainNode<T>* p = first;
    cout << "elements of linkedlist" << endl;
    while(p)
    {
        cout << p->data << " ";
        p = p->link;
    }
    cout << endl;
}

int main()
{
    cout << "Make Chain" << endl;
    cout << "Add 5 elements" << endl;
    int input;
    Chain<int> c;
    for(int i = 0; i < 5; i++)
    {
        cin >> input;
        c.Add(input);
    }
    c.Display();

    cout << "Make another Chain" << endl;
    cout << "Add 3 elements" << endl;
    Chain<int> c2;
    for(int i = 0; i < 3; i++)
    {
        cin >> input;
        c2.Add(input);
    }
    c2.Display();

    cout << "Concatenate c and c2" << endl;
    c.Concatenate(c2);
    c.Display();

    cout << "Invert Concatenated c(c + c2)" << endl;
    c.Invert();
    c.Display();

    cout << "length of Concatenated c(c + c2)" << endl;
    cout << "length : " << c.Length() << endl;

    return 0;
}