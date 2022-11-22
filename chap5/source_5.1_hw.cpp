//소스코드 5.1: binary tree
#pragma once
//make a binary tree 
/*
1. preorder, postorder, copy, == (equal)를 test한다.
2. 두개의 binary tree를 만들어 equal 테스트한다.
3. NonrecInorder()를 구현한다
4. class InorderIterator를 구현한다.
5. class Queue를 사용하여 LevelOrder()를 구현한다.

expression = A + B * C –D를 TREE로 만드는 코딩

*/
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

const int DefaultSize = 10;
enum Boolean { FALSE, TRUE };

template <class KeyType>
class Stack
{
public:
	Stack(int MaxStackSize = DefaultSize);

	Boolean IsFull();

	void Add(const KeyType& x);

	Boolean IsEmpty();

	KeyType* Delete(KeyType&);

	void StackEmpty() { cout << "empty" << endl; };
	void StackFull() { cout << "full" << endl; };
	void Output();
private:
	int top;
	KeyType* stack;
	int MaxSize;
};

template <class KeyType>
Stack<KeyType>::Stack(int MaxStackSize) : MaxSize(MaxStackSize)
{
	stack = new KeyType[MaxSize];
	top = -1;
}

template <class KeyType>
inline Boolean  Stack<KeyType>::IsFull()
{
	if (top == MaxSize - 1) return TRUE;
	else return FALSE;
}

template <class KeyType>
inline Boolean  Stack<KeyType>::IsEmpty()
{
	if (top == -1) return TRUE;
	else return FALSE;
}

template <class KeyType>
void Stack<KeyType>::Add(const KeyType& x)
{
	if (IsFull()) StackFull();
	else stack[++top] = x;
}

template <class KeyType>
KeyType* Stack<KeyType>::Delete(KeyType& x)
{
	if (IsEmpty()) { StackEmpty(); return 0; }
	x = stack[top--];
	return &x;
}

template <class KeyType>
void Stack<KeyType>::Output()
{
	cout << "top = " << top << endl;
	for (int i = 0; i <= top; i++)
		cout << i << ":" << stack[i] << endl;
}


template <class KeyType>
class Queue
{
	// \fBobjects\fR: A finite ordered list with zero or more elements.
public:
	Queue(int MaxQueueSize = 5);
	// Create an empty queue whose maximum size is \fIMaxQueueSize\fR

	bool IsFull();
	// if number of elements in the queue is equal to the maximum size of
	//   the queue, return TRUE (1); otherwise, return FALSE (0)

	void Add(const KeyType& x);
	// if IsFull(), then QueueFull(); else insert item into the top of the queue.

	bool IsEmpty();
	// if number of elements in the queue is equal to 0, return TRUE (1) else return FALSE (0).

	KeyType* Delete(KeyType&);
	// if IsEmpty(), then QueueEmpty(); else remove and return the topmost element of the Queue

	void QueueEmpty() { cout << "empty" << endl; };
	void QueueFull() { cout << "full" << endl; };
	void Output();
private:
	int front;
	int rear;
	KeyType* queue;
	int MaxSize;
};

template <class KeyType>
Queue<KeyType>::Queue(int MaxQueueSize) : MaxSize(MaxQueueSize)
{
	queue = new KeyType[MaxSize];
	front = rear = -1;
}

template <class KeyType>
inline bool  Queue<KeyType>::IsFull()
{
	if (rear == MaxSize - 1) return true;
	else return false;
}

template <class KeyType>
inline bool  Queue<KeyType>::IsEmpty()
{
	if (front == rear) return true;
	else return false;
}

template <class KeyType>
void Queue<KeyType>::Add(const KeyType& x)
// add x to the queue
{
	if (IsFull()) QueueFull();
	else queue[++rear] = x;
}

template <class KeyType>
KeyType* Queue<KeyType>::Delete(KeyType& x)
// remove and return front element from queue
{
	if (IsEmpty()) { QueueEmpty(); return 0; }
	x = queue[++front];
	return &x;
}

template <class KeyType>
void Queue<KeyType>::Output()
{
	cout << "front = " << front << "rear = " << rear << endl;
	for (int i = front + 1; i <= rear; i++)
		cout << i << ":" << queue[i] << endl;
}

//make a binary tree 
/*
1. preorder, postorder, copy, == (equal)를 test한다.
2. 두개의 binary tree를 만들어 equal 테스트한다.
3. NonrecInorder()를 구현한다
4. class InorderIterator를 구현한다.
5. class Queue를 사용하여 LevelOrder()를 구현한다.

   expression = A + B * C –D를 TREE로 만드는 코딩
6. template version으로 만드는 것
7. inorder iterator 처럼 level order로 binary tree를 traverse하는 LevelIterator를 구현
8. PostorderIterator 구현
9. count # of of leaf nodes
10. SwapTree(): swap left and right child of every node
*/

//inorder(), postorder(), preorder() -> NonrecInorder() -> class InorderIterator -> Next() -> LevelOrder() -> NoStackInorder() -> Copy() -> equal()

class Tree;

class TreeNode {
	friend class Tree;
	friend class InorderIterator;
	friend int equal(TreeNode*, TreeNode*);
private:
	TreeNode* LeftChild;
	int data;
	TreeNode* RightChild;

	TreeNode() {
		LeftChild = RightChild = 0;
	};

	TreeNode(int ch, TreeNode* Lefty, TreeNode* Righty) {
		data = ch;
		LeftChild = Lefty;
		RightChild = Righty;
	}
};

class Tree {
	friend int operator==(const Tree&, const Tree&);
	friend class InorderIterator;
private:
	TreeNode* root;
	void inorder(TreeNode*);
	void preorder(TreeNode*);
	void postorder(TreeNode*);
	TreeNode* copy(TreeNode*);
public:
	Tree(const Tree&);
	Tree() { root = 0; };

	bool Insert(int);
	int Delete(int);//임의 값 x를 delete하는 구현 실습
	void inorder();
	void preorder();
	void postorder();
	void NoStackInorder();
	void NonrecInorder();
	void LevelOrder();
	void Split(int i, Tree& b, Tree& c, int& x);
	Tree* ThreeWayJoin(Tree* a, TreeNode* x, Tree* b);
	Tree* TwoWayJoin(Tree* a, Tree* b);
	void adjust();
	int Height();
	bool IsSkewed();
	Tree* Copy(); //void Copy(Tree&);
	TreeNode* InorderSucc(TreeNode*);
};
TreeNode* Tree::InorderSucc(TreeNode* current)
{
	TreeNode* temp = current->RightChild;
	if (current->RightChild != NULL)
		while (temp->LeftChild != NULL) temp = temp->LeftChild;
	return temp;
}

class InorderIterator {
public:
	int* Next();
	InorderIterator(Tree tree) : t(tree) {
		CurrentNode = t.root;
	};

private:
	Tree t;
	Stack<TreeNode*> s;
	TreeNode* CurrentNode;
};


int* InorderIterator::Next()
{
	while (CurrentNode) {
		s.Add(CurrentNode);
		CurrentNode = CurrentNode->LeftChild;
	}
	if (!s.IsEmpty()) {
		CurrentNode = *s.Delete(CurrentNode);
		int& temp = CurrentNode->data;
		CurrentNode = CurrentNode->RightChild;
		return &temp;
	}
	else return 0;
}

void Tree::inorder()
{
	inorder(root);
}

void Tree::preorder()
{
	preorder(root);
}

void Tree::postorder()
{
	postorder(root);
}

void Tree::inorder(TreeNode* CurrentNode)
{
	if (CurrentNode) {
		inorder(CurrentNode->LeftChild);
		cout << " " << CurrentNode->data;
		inorder(CurrentNode->RightChild);
	}
}

void Tree::preorder(TreeNode* CurrentNode)
{
	if (CurrentNode) {
		cout << CurrentNode->data << " ";
		preorder(CurrentNode->LeftChild);
		preorder(CurrentNode->RightChild);
	}
}

void Tree::postorder(TreeNode* CurrentNode)
{
	if (CurrentNode) {
		postorder(CurrentNode->LeftChild);
		postorder(CurrentNode->RightChild);
		cout << CurrentNode->data << " ";
	}
}

Tree::Tree(const Tree& s)//copy constructor
{
	root = copy(s.root);
}

TreeNode* Tree::copy(TreeNode* orignode)
{
	if (orignode) {
		TreeNode* temp = new TreeNode;
		temp->data = orignode->data;
		temp->LeftChild = copy(orignode->LeftChild);
		temp->RightChild = copy(orignode->RightChild);
		return temp;
	}
	else return 0;
}
// Driver
int operator==(const Tree& s, const Tree& t)
{
	return equal(s.root, t.root);
}

// Workhorse
int equal(TreeNode* a, TreeNode* b)
/* This function returns 0 if the subtrees at a and b are not
equivalent. Otherwise, it will return 1 */
{
	if ((!a) && (!b)) return 1;  // both a and b are 0
	if (a && b &&                // both a and b are non-0
		(a->data == b->data)      // data is the same
		&& equal(a->LeftChild, b->LeftChild) // left subtrees are the same
		&& equal(a->RightChild, b->RightChild)) // right subtrees are the same
		return 1;
	return 0;
}

bool Tree::Insert(int x) {//binary search tree를 만드는 입력 => A + B * C을 tree로 만드는 방법: 입력 해결하는 알고리즘 작성 방법을 설계하여 구현
	TreeNode* p = root;
	TreeNode* q = 0;
	while (p) {
		q = p;
		if (x == p->data) return false;
		if (x < p->data) p = p->LeftChild;
		else p = p->RightChild;
	}
	p = new TreeNode;
	p->LeftChild = p->RightChild = 0;
	p->data = x;
	if (!root) root = p;
	else if (x < q->data) q->LeftChild = p;
	else q->RightChild = p;
	return true;
}
int Tree::Delete(int elm) {
	TreeNode* p = root; // traversal node
	TreeNode* q = 0;	// target node
	TreeNode* r = 0;	// inorder sucessor node
	TreeNode* s = 0;	// parent node
	int inorderSucessor;
	// find target node(q) and its parent node(s)
	while (p)
	{
		s = q;
		q = p;
		if (elm == p->data) break;
		if (elm < p->data) p = p->LeftChild;
		else p = p->RightChild;
	}
	// if p == NULL, elm dosen't exist in this tree
	if (!p)
	{
		cout << "no such element in tree" << endl;
		return 0;
	}

	if (!q->LeftChild && !q->RightChild) // child node : 0
	{
		if (q->data < s->data) s->LeftChild = 0;
		else if(q->data > s->data) s->RightChild = 0;
	}
	else if (!q->LeftChild || !q->RightChild) // child node : 1
	{
		if (q->data == s->LeftChild->data)
		{
			if (q->LeftChild) s->LeftChild = q->LeftChild;
			else s->LeftChild = q->RightChild;
		}
		else if (q->data == s->RightChild->data)
		{
			if (q->LeftChild) s->RightChild = q->LeftChild;
			else s->RightChild = q->RightChild;
		}
	}
	else // non leaf, child node : 2
	{
		// configure inorder sucessor, inorder sucessor node(r)
		r = q->RightChild;
		while (r->LeftChild) r = r->LeftChild;
		inorderSucessor = r->data;

		this->Delete(inorderSucessor);
		q->data = inorderSucessor;
	}
	return 1;
}
void Tree::NonrecInorder()//void Tree::inorder(TreeNode *CurrentNode)와 비교
{
	Stack<TreeNode*> s;
	TreeNode* CurrentNode = root;
	while (1) {
		while (CurrentNode) {
			s.Add(CurrentNode);
			CurrentNode = CurrentNode->LeftChild;
		}
		if (!s.IsEmpty()) {
			CurrentNode = *s.Delete(CurrentNode);
			cout << CurrentNode->data << endl;
			CurrentNode = CurrentNode->RightChild;
		}
		else break;
	}
}
void Tree::LevelOrder()
{
	Queue <TreeNode*> q;
	TreeNode* CurrentNode = root;
	while (CurrentNode) {
		cout << CurrentNode->data << endl;
		if (CurrentNode->LeftChild)
			q.Add(CurrentNode->LeftChild);
		if (CurrentNode->RightChild)
			q.Add(CurrentNode->RightChild);
		CurrentNode = *q.Delete(CurrentNode);
	}
}
void Tree::NoStackInorder() //inorder()와 비교
{
	if (!root) return;
	TreeNode* top = 0, * LastRight = 0, * p, * q, * r, * r1;//local variable이 key point
	p = q = root;
	while (1) {
		while (1) {
			if ((!p->LeftChild) && (!p->RightChild)) {
				cout << p->data; break;
			}
			if (!p->LeftChild) {
				cout << p->data;
				r = p->RightChild; p->RightChild = q;
				q = p; p = r;
			}
			else {
				r = p->LeftChild; p->LeftChild = q;
				q = p; p = r;
			}
		}
		TreeNode* av = p;
		while (1) {
			if (p == root) return;
			if (!q->LeftChild) {
				r = q->RightChild; q->RightChild = p;
				p = q; q = r;
			}
			else if (!q->RightChild) {
				r = q->LeftChild; q->LeftChild = p;
				p = q; q = r; cout << p->data;
			}
			else
				if (q == LastRight) {
					r = top; LastRight = r->LeftChild;
					top = r->RightChild;
					r->LeftChild = r->RightChild = 0;
					r = q->RightChild; q->RightChild = p;
					p = q; q = r;
				}
				else {
					cout << q->data;
					av->LeftChild = LastRight; av->RightChild = top;
					top = av; LastRight = q;
					r = q->LeftChild; q->LeftChild = p;
					r1 = q->RightChild; q->RightChild = r;
					p = r1;
					break;
				}
		}
	}
}

// split the binary search tree with respect to key i
// original tree => tree b + tree c, split point : i, split point confirm : x
void Tree::Split(int i, Tree& b, Tree& c, int& x)
{
	// empty tree
	if (!root)
	{
		b.root = c.root = 0; x = 0;
		return;
	}
	
	int mode = 0;
	TreeNode* prev = root;
	TreeNode* current = root;
	c.root = root;
	while (current)
	{
		if (i == current->data) // split point i == root
		{
			if (current == root) // current == root -> split
			{
				x = current->data;
				b.root = current->LeftChild;
				c.root = current->RightChild;
				return;
			}
			if (mode == 0) // split left child...?
			{
				prev->LeftChild = current->RightChild;
				b.root = current->LeftChild;
			}
			else // split right child...?
			{
				prev->RightChild = current->LeftChild;
				b.root = current->RightChild;
			}
			c.root = root;
			x = current->data;
			return;
		}
		else if (i < current->data) // key is less than current
		{
			prev = current;
			mode = 0;
			current = current->LeftChild; // move to leftchild
		}
		else // key is larger than current 
		{
			prev = current;
			mode = 1;
			current = current->RightChild;
		}
	}
	return;
}

// have to a < x < b
Tree* Tree::ThreeWayJoin(Tree* a, TreeNode* x, Tree* b)
{
	TreeNode* newNode = new TreeNode;
	newNode->data = x->data;
	newNode->LeftChild = a->root;
	newNode->RightChild = b->root;

	Tree* newTree = new Tree;
	newTree->root = newNode;
	return newTree;
}

// have to a < b
Tree* Tree::TwoWayJoin(Tree* a, Tree* b)
{
	if (!a) return b;
	if (!b) return a;

	TreeNode midval;
	TreeNode* p = a->root;
	TreeNode* q = 0;
	
	while (p) // find a's biggest Node and Delete it
	{
		q = p;
		p = p->RightChild;
	}
	midval.data = q->data;
	a->Delete(q->data);
	return ThreeWayJoin(a, &midval, b);
}

void Tree::adjust()
{
	Tree b;
	Tree c;
	int confirm;
	if (IsSkewed() && (Height() > 2))
	{
		// Split(key value, b, c, confirm);
		// configure split key value...
		// TwoWayJoin(b, c);
	}
}

int Tree::Height()
{
	Queue <TreeNode*> q;
	TreeNode* CurrentNode = root;
	int height = 1;
	while (CurrentNode)
	{
		if (CurrentNode->LeftChild)
		{
			q.Add(CurrentNode->LeftChild);
		}
		if (CurrentNode->RightChild) 
		{
			q.Add(CurrentNode->RightChild);
		}
		CurrentNode = *q.Delete(CurrentNode);
	}
}

bool Tree::IsSkewed()
{
	TreeNode* current = root;
	TreeNode* next = 0;
	while (current)
	{
		if (!(current->LeftChild) && (current->RightChild)) next = current->RightChild;
		else if ((current->LeftChild) && !(current->RightChild)) next = current->LeftChild;
		else return false;
	}
	return true;
}

int main(void)
{
	srand(time(NULL));
	Tree t;
	Tree b, c;
	int eq = -1;
	char select = 'i';
	int max = 0, x = 0;
	int splitKey;
	int splitConfirm;
	while (select != 'q')
	{
		int rnd = 0;
		cout << "BinarySearchTree. Select i:Insert, r: remove, d:Display, e:NonrecInorder, f:preorder, g:postorder, h:copy and compare, q : Quit, s : split" << endl << "==>";
		cin >> select;
		switch (select)
		{
		case 'i':
			cout << "The number of items = ";
			cin >> max;
			for (int i = 0; i < max; i++) {
				rnd = rand() / 100;
				if (!t.Insert(rnd)) cout << "Insert Duplicated data" << endl;
			}

			break;
		case 'r':
			int x;
			cout << "Delete data insert" << endl;
			cin >> x;
			if (t.Delete(x)) //입력된 x에 대한 tree 노드를 찾아 삭제한다.
			{
				cout << x << " sucessfully deleted" << endl;
			}
			else cout << "Delete " << x << " failed" << endl;
			break;
		case 'd':
			t.inorder();
			cout << endl;
			break;
		case 'e':
			t.NonrecInorder();
			break;
		case 'f':
			t.preorder();
			break;
		case 'g':
			t.postorder();
			break;
		case 'h':
			eq = (t == Tree(t));//copy constructor를 호출
			if (eq) {
				cout << "compare result: true" << endl;
			}
			else
				cout << "compare result: false" << endl;
			break;
		case 'q':
			cout << "Quit" << endl;
			break;
		case 's':
			cout << "split current tree" << endl;
			cout << "split key : ";
			cin >> splitKey;
			t.Split(splitKey, b, c, splitConfirm);
			cout << "b : ";
			b.inorder();
			cout << endl << "c : ";
			c.inorder();
			cout << endl;
			break;
		default:
			cout << "WRONG INPUT  " << endl;
			cout << "Re-Enter" << endl;
			break;
		}
	}

	system("pause");
	return 0;
}
