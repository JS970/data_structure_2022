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

class student
{
public:
	student() { 
		sid = rand() % 10000;
		grade = rand() % 5 + rand() % 100 * 0.01; if (grade >= 4.5) grade = grade - 0.5;
		age = rand() % 30;
	}
	int sid;
	float grade;
	int age;
};

class Tree;

class TreeNode {
	friend class Tree;
	friend class InorderIterator;
	friend int equal(TreeNode*, TreeNode*);
	friend int main();
private:
	TreeNode* LeftChild;
	student data;
	TreeNode* RightChild;

	TreeNode() {
		LeftChild = RightChild = 0;
	};

	TreeNode(student ch, TreeNode* Lefty, TreeNode* Righty) {
		data.sid = ch.sid;
		LeftChild = Lefty;
		RightChild = Righty;
	}
};

class Tree {
	friend int operator==(const Tree&, const Tree&);
	friend class InorderIterator;
	friend int main();
private:
	TreeNode* root;
	void inorder(TreeNode*);
	void preorder(TreeNode*);
	void postorder(TreeNode*);
	TreeNode* copy(TreeNode*);
public:
	Tree(const Tree&);
	Tree() { root = 0; };

	bool Insert(student); // 기말고사
	int Delete(int);// 기말고사
	void inorder();
	void preorder();
	void postorder();
	void StackPostorder(); // 기말고사
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
		int& temp = CurrentNode->data.sid;
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
		cout << "student id : " << CurrentNode->data.sid << endl;
		cout << "grade : " << CurrentNode->data.grade << endl;
		cout << "age : " << CurrentNode->data.age << endl << endl;
		inorder(CurrentNode->RightChild);
	}
}

void Tree::preorder(TreeNode* CurrentNode)
{
	if (CurrentNode) {
		cout << CurrentNode->data.sid << " ";
		preorder(CurrentNode->LeftChild);
		preorder(CurrentNode->RightChild);
	}
}

void Tree::postorder(TreeNode* CurrentNode)
{
	if (CurrentNode) {
		postorder(CurrentNode->LeftChild);
		postorder(CurrentNode->RightChild);
		cout << CurrentNode->data.sid << " ";
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
		(a->data.sid == b->data.sid)      // data is the same
		&& equal(a->LeftChild, b->LeftChild) // left subtrees are the same
		&& equal(a->RightChild, b->RightChild)) // right subtrees are the same
		return 1;
	return 0;
}

bool Tree::Insert(student x) {//binary search tree를 만드는 입력 => A + B * C을 tree로 만드는 방법: 입력 해결하는 알고리즘 작성 방법을 설계하여 구현
	TreeNode* p = root;
	TreeNode* q = 0;
	while (p) {
		q = p;
		if (x.sid == p->data.sid) return false;
		if (x.sid < p->data.sid) p = p->LeftChild;
		else p = p->RightChild;
	}
	p = new TreeNode;
	p->LeftChild = p->RightChild = 0;
	p->data.sid = x.sid;
	if (!root) root = p;
	else if (x.sid < q->data.sid) q->LeftChild = p;
	else q->RightChild = p;
	return true;
}
int Tree::Delete(int elm) {
	//leaf node를 삭제하는 경우
	//non-leaf node를 삭제하는 경우에는 inorder successor로 replace 한후에 leaf node를 삭제하도록 구현해야 한다. 
	//기말고사 => inorder successor가 아니라 inorder predecessor로 replace해야 함
	TreeNode* p = root; // traversal node
	TreeNode* q = 0;	// target node
	TreeNode* r = 0;	// inorder predecessor node
	TreeNode* s = 0;	// parent node
	int inorderpredecessor;
	// find target node(q) and its parent node(s)
	while (p)
	{
		s = q;
		q = p;
		if (elm == p->data.sid) break;
		if (elm < p->data.sid) p = p->LeftChild;
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
		if (q->data.sid < s->data.sid) s->LeftChild = 0;
		else if (q->data.sid > s->data.sid) s->RightChild = 0;
	}
	else if (!q->LeftChild || !q->RightChild) // child node : 1
	{
		if (q->data.sid == s->LeftChild->data.sid)
		{
			if (q->LeftChild) s->LeftChild = q->LeftChild;
			else s->LeftChild = q->RightChild;
		}
		else if (q->data.sid == s->RightChild->data.sid)
		{
			if (q->LeftChild) s->RightChild = q->LeftChild;
			else s->RightChild = q->RightChild;
		}
	}
	else // non leaf, child node : 2
	{
		// configure inorder predecessor, inorder predecessor node(r)
		r = q->LeftChild;
		while (r->RightChild) r = r->RightChild;
		inorderpredecessor = r->data.sid; //

		this->Delete(inorderpredecessor); //
		q->data.sid = inorderpredecessor; //
	}
	return 1;
}


void Tree::StackPostorder()
{
	Stack<TreeNode*> s;
	TreeNode* CurrentNode = root;
	while (1) {
		while (CurrentNode) {
			s.Add(CurrentNode);
			CurrentNode = CurrentNode->RightChild;
		}
		if (!s.IsEmpty()) {
			CurrentNode = *s.Delete(CurrentNode);
			cout << "student id : " << CurrentNode->data.sid << endl;
			cout << "grade : " << CurrentNode->data.sid << endl;
			cout << "age : " << CurrentNode->data.age << endl << endl;
			CurrentNode = CurrentNode->LeftChild;
		}
		else break;
	}
}

int main(void)
{
	srand(time(NULL));
	Tree t;
	char select = 'i';
	int max = 0, x = 0;
	student* stdarr = new student[30];
	int r;
	int lc;
	int rc;
	for (int i = 0; i < 30; i++)
	{
		stdarr[i] = student();
	}
	while (select != 'q')
	{
		int rnd = 0;
		cout << "BinarySearchTree. Select i:Insert, r: remove, d:Display(inorder), e:StackPostorder, f:2022 DataStructure Final exam, q : Quit =>";
		cin >> select;
		switch (select)
		{
		case 'i':
			cout << "30 students object generated" << endl;
			for (int i = 0; i < 30; i++) {
				if (!t.Insert(stdarr[i])) cout << "Insert Duplicated data" << endl;
			}
			break;
		case 'r':
			int x;
			cout << "insert sid of the student";
			cin >> x;
			cout << t.Delete(x);//입력된 x에 대한 tree 노드를 찾아 삭제한다.
			cout << endl;
			break;
		case 'd':
			t.inorder();
			cout << endl;
			break;
		case 'e':
			t.StackPostorder();
			break;
		case 'f':
		{
			cout << "generating student objects..." << endl;
			for (int i = 0; i < 30; i++) {
				if (!t.Insert(stdarr[i])) cout << "Insert Duplicated data" << endl;
			}

			cout << "inorder display" << endl;
			for (int i = 0; i < 30; i++) {
				if (!t.Insert(stdarr[i])) cout << "Insert Duplicated data" << endl;
			}

			cout << "StackPostOrder display" << endl;
			t.StackPostorder();

			cout << "Delete examples" << endl;
			cout << "delete root and root's both childs" << endl;
			r = t.root->data.sid;
			lc = t.root->LeftChild->data.sid;
			rc = t.root->RightChild->data.sid;
			cout << "deleted student's sid : " << r << ", " << lc << ", " << rc << endl;
			t.Delete(r);
			t.Delete(lc);
			t.Delete(rc);

			cout << "inorder display after delete" << endl;
			for (int i = 0; i < 30; i++) {
				if (!t.Insert(stdarr[i])) cout << "Insert Duplicated data" << endl;
			}

			cout << "StackPostOrder display after delete" << endl;
			t.StackPostorder();

			break;
		}
		case 'q':
			cout << "Quit" << endl;
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
