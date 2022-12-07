#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
const int HeapSize = 100;

template <class Type> class List;
template <class Type> class ListIterator;

template <class Type>
class ListNode
{
	friend class List<Type>;
	friend class ListIterator<Type>;
	friend class Graph;
	ListNode(Type);
private:
	Type data;
	ListNode* link;
};

template <class Type>
ListNode<Type>::ListNode(Type Default)
{
	data = Default;
	// random weight for each nodes
	link = 0;
}

template <class Type>
class List
{
	friend class ListIterator<Type>;
public:
	List() { first = 0; }
	void Insert(Type);
	void Delete(Type);
private:
	ListNode<Type>* first;
};

template <class Type>
void List<Type>::Insert(Type k)
{
	ListNode<Type>* newnode = new ListNode<Type>(k);
	newnode->link = first;
	first = newnode;
}

template <class Type>
void List<Type>::Delete(Type k)
{
	ListNode<Type>* previous = 0;
	ListNode<Type>* current = first;
	for (current = first; current && current->data != k;
		previous = current, current = current->link);
	if (current)
	{
		if (previous) previous->link = current->link;
		else first = first->link;
		delete current;
	}
}

template <class Type>
class ListIterator
{
	friend class Graph;
public:
	ListIterator(const List<Type>& l) : list(l) { current = l.first; }
	Type* First();
	Type* Next();
	bool NotNull();
	bool NextNotNull();
private:
	const List<Type>& list;
	ListNode<Type>* current;
};

template <class Type>
Type* ListIterator<Type>::First()
{
	if (list.first) return &list.first->data;
	else return 0;
}
template <class Type>
Type* ListIterator<Type>::Next()
{
	current = current->link;
	return &current->data;
}

template <class Type>
bool ListIterator<Type>::NotNull()
{
	if (current) return true;
	else return false;
}

template <class Type>
bool ListIterator<Type>::NextNotNull()
{
	if (current->link) return true;
	else return false;
}

// char type list '<<' operator overloading
ostream& operator<<(ostream& os, List<char>& l)
{
	ListIterator<char> li(l);
	if (!li.NotNull()) return os;
	os << *li.First() << endl;
	while (li.NextNotNull())
		os << *li.Next() << endl;
	return os;
}

class Queue;

class QueueNode
{
	friend class Queue;
private:
	int data;
	QueueNode* link;
	QueueNode(int def = 0, QueueNode* l = 0)
	{
		data = def;
		link = l;
	}
};

class Queue
{
public:
	Queue() { front = rear = 0; }
	void Insert(int);
	int* Delete(int&);
	bool IsEmpty() { if (front == 0) return true; else return false; }
private:
	QueueNode* front;
	QueueNode* rear;
	void QueueEmpty() { cout << "Queue Empty" << endl; }
};

void Queue::Insert(int y)
{
	if (front == 0) front = rear = new QueueNode(y, 0); // Empty queue
	else rear = rear->link = new QueueNode(y, 0); // update rear
}

int* Queue::Delete(int& retvalue)
{
	if (front == 0)
	{
		QueueEmpty();
		return 0;
	}
	QueueNode* x = front;
	retvalue = front->data;
	front = x->link;
	if (front == 0) rear = 0;

	delete x;
	return &retvalue;
}

class Edges
{
	friend class Graph;
	friend class MinHeap;
public:
	Edges(ListNode<int>* v1 = 0, ListNode<int>* v2 = 0)
	{
		vertex1 = v1; vertex2 = v2; weight = rand();
	}
private:
	ListNode<int>* vertex1;
	ListNode<int>* vertex2;
	int weight;
};

class Graph
{
public:
	Graph(bool, int);
	Graph(int vertices);
	void BFS(int);
	bool InsertVertex(int startNode, int endNode);
	void displayAdjacencyLists();
	void DFS(int v);
	void Prim(Graph& g, int startnode);
private:
	List<int>* HeadNodes; // int type linkedlist array
	int n; // number of node(vertices)
	Edges* e; // edges array
	int ne; // number of edges
	bool* visited; // visited array
	void _DFS(const int v);
};

Graph::Graph(bool overloading, int nodes)
{
	n = nodes;
	HeadNodes = new List<int>[n];
	e = new Edges[n - 1];
}

Graph::Graph(int vertices = 1)
{
	n = vertices;
	HeadNodes = new List<int>[n];
	int j = 0; // edge index
	int count = 0;
	bool flag = true;

	// edge generation, set to 6(could set this value random using rand())
	cout << "input number of edges to generate graph: ";
	cin >> ne;
	e = new Edges[ne];
	for (int i = 0; i < ne; i++)
	{
		// weight initialization
		e[i].weight = rand() % 10;
		int v1 = rand() % (n);
		int v2 = rand() % (n);
		// add verteces to edge
		e[i].vertex1 = new ListNode<int>(v1);
		e[i].vertex2 = new ListNode<int>(v2);
		HeadNodes[v1].Insert(v2);
		HeadNodes[v2].Insert(v1);
		cout << "e[" << i << "].vertex1->data : " << e[i].vertex1->data << endl;
		cout << "e[" << i << "].vertex2->data : " << e[i].vertex2->data << endl;
	}

}

void Graph::displayAdjacencyLists()
{
	for (int i = 0; i < n; i++)
	{
		// HeadNodes linkedlist iterator
		ListIterator<int> iter(HeadNodes[i]);
		if (!iter.NotNull())
		{
			cout << i << " -> null" << endl;
			continue;
		}
		cout << i;
		for (int* first = iter.First(); iter.NotNull(); first = iter.Next())
			cout << " -> " << (*first);
		cout << endl;
	}
}

bool Graph::InsertVertex(int start, int end)
{
	if (start < 0 || start >= n || end < 0 || end >= n)
	{
		cout << "the start node number is out of bound.";
		throw "";
	}
	// check if already existed
	ListIterator<int> iter(HeadNodes[start]);
	for (int* first = iter.First(); iter.NotNull(); first = iter.Next())
		if (*first == end) return false;

	HeadNodes[start].Insert(end);
	HeadNodes[end].Insert(start);
	n++;
	return true;
}

void Graph::BFS(int v)
{
	visited = new bool[n];
	for (int i = 0; i < n; i++)
		visited[i] = false;

	visited[v] = true;
	cout << v << ",";
	Queue q;
	q.Insert(v);

	while (!q.IsEmpty())
	{
		v = *q.Delete(v);
		ListIterator<int> li(HeadNodes[v]);
		if (!li.NotNull()) continue;
		int w = *li.First();
		while (1)
		{
			if (!visited[w])
			{
				q.Insert(w);
				visited[w] = true;
				cout << w << ",";
			}
			if (li.NextNotNull())
				w = *li.Next();
			else break;
		}
	}
	delete[] visited;
}

void Graph::DFS(int v)
{
	visited = new bool[n];
	for (int i = 0; i < n; i++)
		visited[i] = false;

	_DFS(v);
	delete[] visited;
}

void Graph::_DFS(const int v)
{
	visited[v] = true;
	cout << v << ", ";
	ListIterator<int> li(HeadNodes[v]);
	if (!li.NotNull()) return;
	int w = *li.First();
	while (1)
	{
		if (!visited[w]) _DFS(w);
		if (li.NextNotNull()) w = *li.Next();
		else return;
	}
}

// Min Priority Queue
class MinPQ
{
public:
	virtual void Insert(const Edges&) = 0;
	virtual Edges* DeleteMin(Edges&) = 0;
};

// Min Heap
class MinHeap : public MinPQ
{
public:
	MinHeap(int sz = HeapSize)
	{
		MaxSize = sz; n = 0;
		heap = new Edges[MaxSize + 1]; // Don't want to use heap[0]
	}
	void display();
	void Insert(const Edges& x);
	Edges* DeleteMin(Edges& x);
private:
	Edges* heap;
	int n; // current size of MinHeap
	int MaxSize; // Minimum size of MinHeap
	void HeapEmpty() { cout << "Heap Empty" << endl; }
	void HeapFull() { cout << "Heap Full" << endl; }
};

void MinHeap::display()
{
	int i;
	cout << "MinHeap:: (i, heap[i].key): ";
	for (i = 1; i <= n; i++) cout << "(" << i << ", " << heap[i].weight << ") ";
	cout << endl;
}

void MinHeap::Insert(const Edges& x)
{
	int i;
	if (n == MaxSize)
	{
		HeapFull();
		return;
	}
	n++;
	for (i = n; 1;)
	{
		if (i == 1) break; // at root
		if (x.weight >= heap[i / 2].weight) break;
		// move from parent to i
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = x;
}

Edges* MinHeap::DeleteMin(Edges& x)
{
	int i, j;
	if (!n)
	{
		HeapEmpty();
		return 0;
	}
	x = heap[1];
	Edges k = heap[n];
	n--;

	for (i = 1, j = 2; j <= n;)
	{
		if (j < n)
			if (heap[j].weight > heap[j + 1].weight) j++;
		// j points to the smaller child
		if (k.weight <= heap[j].weight) break;
		heap[i] = heap[j];
		i = j;
		j *= 2;
	}
	heap[i] = k;
	return &x;
}

class Sets
{
public:
	Sets(int);
	void display();
	void SimpleUnion(int, int);
	int SimpleFind(int);
	void WeightedUnion(int, int);
	int CollapsingFind(int);
private:
	int* parent;
	int n;
};

Sets::Sets(int sz = HeapSize)
{
	n = sz;
	parent = new int[sz + 1]; // Don't want to use parent[0]
	for (int i = 1; i <= n; i++)
		parent[i] = -1;
}

// Replace the disjoint sets with roots i and j, i != j with their union
void Sets::SimpleUnion(int i, int j)
{
	parent[j] = i;
}

// Find the root of the tree containing element i
int Sets::SimpleFind(int i)
{
	while (parent[i] > 0) i = parent[i];
	return i;
}

void Sets::WeightedUnion(int i, int j)
{
	int temp = parent[i] + parent[j];
	if (parent[i] > parent[j])
	{
		// i has fewer nodes
		parent[i] = j;
		parent[j] = temp;
	}
	else
	{
		// j has fewer nodes
		parent[j] = i;
		parent[i] = temp;
	}
	cout << "vertex[" << i << "]" << "---" << "vertex[" << j << "]" << endl;
}

int Sets::CollapsingFind(int i)
{
	int r;
	for (r = i; parent[r] > 0; r = parent[r]); // find root
	while (i != r)
	{
		int s = parent[i];
		parent[i] = r;
		i = s;
	}
	return r;
}

void Sets::display()
{
	cout << "display:index= ";
	for (int i = 1; i <= n; i++) printf("%3d ", i);
	cout << endl;
	cout << "display:value= ";
	for (int i = 1; i <= n; i++) printf("%3d ", parent[i]);
	cout << endl;
}

bool Isin(int arr[], int sz, int check)
{
	for (int i = 0; i < sz; i++)
		if (check == arr[i]) return true;
	return false;
}

void Graph::Prim(Graph& g, int startnode = 0)
{
	int small;
	int smallidx = 0;
	bool flag = false;
	int select;
	int count = 0;
	int j;
	int* vertexarr = new int[g.n];
	int idx = 0; // count for vertexarr
	for (int i = startnode; i < g.n;)
	{
		flag = false;
		small = 9999;

		vertexarr[idx++] = i;
		for (j = 0; j < g.ne; j++)
		{
			bool v1in = Isin(vertexarr, idx, g.e[j].vertex1->data);
			bool v2in = Isin(vertexarr, idx, g.e[j].vertex2->data);
			if (i == g.e[j].vertex1->data)
			{
				if (small > g.e[j].weight)
				{
					if (i != g.e[j].vertex2->data)
					{
						if (!(v1in && v2in))
						{
							flag = true;
							small = g.e[j].weight;
							smallidx = j;
							select = 1;
						}
					}
				}
			}
		}
		for (j = 0; j < g.ne; j++)
		{
			bool v1in = Isin(vertexarr, idx, g.e[j].vertex1->data);
			bool v2in = Isin(vertexarr, idx, g.e[j].vertex2->data);
			if (i == g.e[j].vertex2->data) // weird.. why??
			{
				if (small > g.e[j].weight)
				{
					if (i != g.e[j].vertex1->data)
					{
						if (!(v1in && v2in))
						{
							flag = true;
							small = g.e[j].weight;
							smallidx = j;
							select = 2;
						}
					}
				}
			}
		}

		if (flag && (select == 1))
			cout << "connect : vertex" << g.e[smallidx].vertex1->data << " ==== vertex" << g.e[smallidx].vertex2->data << endl;
		if (flag && (select == 2))
			cout << "connect : vertex" << g.e[smallidx].vertex2->data << " ==== vertex" << g.e[smallidx].vertex1->data << endl;
		// start vertex, next vertex
		if (InsertVertex(g.e[smallidx].vertex1->data, g.e[smallidx].vertex2->data) && flag)
		{
			// move to connected vertex
			if (select == 1)
				i = g.e[smallidx].vertex2->data;
			else
				i = g.e[smallidx].vertex1->data;
			count++;
		}
		else
		{
			if (count != g.n - 1)
				cout << "cannot make spanning tree start with vertex \"" << startnode << "\"" << endl;
			else cout << "spanning tree gererated!" << endl;
			return;
		}
	}
	displayAdjacencyLists();
}

// Driver program to test above functions
int main(void)
{
	int select = 0, n, start, end, weight, startvertex;
	int startBFSNode = 100;//the start node to BFS

	cout << "Input the total node number: ";
	cin >> n;

	/* Let us create following weighted graph */
	struct Graph graph(n);
	Graph* spanningTree = new Graph(false, n);
	while (select != '0')
	{
		cout << "\n1: Display Adjacency Lists, 2: spanningTree, 4: Quit => ";
		cin >> select;
		switch (select) {
		case 1:
			//display
			graph.displayAdjacencyLists();
			break;
		case 2:
			cout << "\nSpanningTree - Prim's algorithm: " << endl;
			cout << "Insert start vertex => ";
			cin >> startvertex;
			spanningTree->Prim(graph, startvertex);
			delete spanningTree;
			spanningTree = nullptr;
			break;
		case 4:
			exit(0);
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
