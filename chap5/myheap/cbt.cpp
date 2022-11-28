#include <iostream>
using namespace std;

class treeNode 
{
friend class CBT;
public:
	treeNode();
private:
	treeNode * LeftChild;
	treeNode * RightChild;
	int data;
};

treeNode::treeNode ()
{
	LeftChild = 0;
	RightChild = 0;
	data = -1;
}

class CBT
{
public:
	CBT();
	treeNode* parentNode(int x);
	void Insert(int x);
	void Delete(int x);
private:
	treeNode * root;
};

CBT::CBT ()
{
	root = 0;	
}

treeNode* CBT::parentNode(int x)
{
	treeNode * CurrentNode = root;
	treeNode * PrevNode = 0;
	while(CurrentNode)
	{
		PrevNode = CurrentNode;
		if(CurrentNode->data == x) break;
		if(CurrentNode->LeftChild)
			CurrentNode = CurrentNode->RightChild;
		else
			CurrentNode = CurrentNode->LeftChild;
	}

	return PrevNode;
}

void CBT::Insert(int x)
{
	if(!root)
	{
		root->data = x;
	}
	else
	{
		treeNode * CurrentNode = root;
		treeNode * PrevNode = 0;
		bool modeRight = 0;
		while(CurrentNode)
		{
			PrevNode = CurrentNode;
			if(CurrentNode->LeftChild)
			{
				CurrentNode = CurrentNode->RightChild;
				modeRight = 1;
			}
			else
				CurrentNode = CurrentNode->LeftChild;
		}
		CurrentNode->data = x;
		if(modeRight) PrevNode->RightChild = CurrentNode;
		else PrevNode->LeftChild = CurrentNode;

		while(CurrentNode->data > parentNode(CurrentNode->data)->data)
		{
			int tmp = CurrentNode->data;
			CurrentNode->data = parentNode(CurrentNode->data)->data;
			parentNode(CurrentNode->data)->data = tmp;
			CurrentNode = parentNode(CurrentNode->data);
		}
	}
}

void CBT::Delete(int x)
{

}

int main()
{
	CBT heap;
	// heap.Insert Segment fault 11/28 Nov TODO fix
	/* 
	heap.Insert(10);
	heap.Insert(20);
	heap.Insert(15);
	heap.Insert(30);
	heap.Insert(5);
	heap.Insert(35);
	*/
	return 0;
}
