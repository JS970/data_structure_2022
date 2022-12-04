// source 5.4: Heap
#include <iostream>
#include <time.h>
#include <string>
using namespace std;
const int HeapSize = 1000;

class AirPlane
{
	friend class ControlTower;
	friend class MaxHeap;
	friend class MinHeap;
public:
	AirPlane();
	AirPlane(int t);
	AirPlane(const AirPlane&);
	void PrintPlane(int t);
	void RenewRemaining(int t) 
	{
		if (usingType)
			remainingTime = planedTime - t;
		else
			remainingTime = planedTime + 2000 - t;
	}
	void RenewWaiting(int t)
	{
		waitingTime = (t - planedTime <= 0) ? 0 : t - planedTime;
	}
private:
	string airId;
	string airName;
	bool usingType;
	int planedTime;
	int remainingTime;
	int waitingTime = 0;
};

// Max Priority Queue
class MaxPQ
{
public:
	virtual void Insert(const AirPlane&) = 0;
	virtual AirPlane* DeleteMax(AirPlane&) = 0;
};

// Min Priority Queue
class MinPQ
{
public:
	virtual void Insert(const AirPlane&) = 0;
	virtual AirPlane* DeleteMin(AirPlane&) = 0;
};

// Max Heap
class MaxHeap : public MaxPQ
{
	friend class AirPlane;
	friend class ControlTower;
public:
	MaxHeap(int sz = HeapSize)
	{
		MaxSize = sz; n = 0;
		heap = new AirPlane[MaxSize + 1]; // Don't want to use heap[0]
	}
	void display(int t);
	void Insert(const AirPlane& x);
	AirPlane* DeleteMax(AirPlane& x);
	int CurrentTopRemain() { return heap[n - 1].remainingTime; }
	void RenewHeap(int t) {
		for (int i = 0; i <= n; i++)
		{
			heap[i].RenewRemaining(t);
			heap[i].RenewWaiting(t);
		}
	}

private:
	AirPlane* heap;
	int n; // current size of MaxHeap
	int MaxSize; // Maximum allowable size of MaxHeap
	void HeapEmpty() { cout << "Heap Empty" << endl; }
	void HeapFull() { cout << "Heap Full" << endl; }
};

void MaxHeap::display(int t)
{
	int i;
	for (i = 1; i <= n; i++) heap[i].PrintPlane(t);
}

void MaxHeap::Insert(const AirPlane& x)
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
		if (x.waitingTime <= heap[i / 2].waitingTime) break;
		// move from parent to i
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = x;
}

AirPlane* MaxHeap::DeleteMax(AirPlane& x)
{
	int i, j;
	if (!n) 
	{
		HeapEmpty();
		return 0;
	}
	x = heap[1];
	AirPlane k = heap[n];
	n--;

	for (i = 1, j = 2; j <= n;)
	{
		if (j < n)
			if (heap[j].remainingTime < heap[j + 1].remainingTime) j++;
		// j points to the larger chile
		if (k.remainingTime >= heap[j].remainingTime) break;
		heap[i] = heap[j];
		i = j;
		j *= 2;
	}
	heap[i] = k;
	return &x;
}

// Min Heap
class MinHeap : public MinPQ
{
	friend class AirPlane;
	friend class ControlTower;
public:
	MinHeap(int sz = HeapSize)
	{
		MaxSize = sz; n = 0;
		heap = new AirPlane[MaxSize + 1]; // Don't want to use heap[0]
	}
	void display(int t);
	void Insert(const AirPlane& x);
	void Insert_Emergency(const AirPlane& x);
	AirPlane* DeleteMin(AirPlane& x);
	AirPlane* DeleteMin_Emergency(AirPlane& x);
	int CurrentTopRemain() { return heap[n - 1].remainingTime; }
	void RenewHeap(int t) {
		for (int i = 0; i <= n; i++)
		{
			heap[i].RenewRemaining(t);
			heap[i].RenewWaiting(t);
		}
	}
private:
	AirPlane* heap;
	int n; // current size of MinHeap
	int MaxSize; // Minimum size of MinHeap
	void HeapEmpty() { cout << "Heap Empty" << endl; }
	void HeapFull() { cout << "Heap Full" << endl; }
};

void MinHeap::display(int t)
{
	int i;
	for (i = 1; i <= n; i++) heap[i].PrintPlane(t);
}

void MinHeap::Insert(const AirPlane& x)
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
		if (x.planedTime >= heap[i / 2].planedTime) break;
		// move from parent to i
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = x;
}

void MinHeap::Insert_Emergency(const AirPlane& x)
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
		if (x.remainingTime >= heap[i / 2].remainingTime) break;
		// move from parent to i
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = x;
}

AirPlane* MinHeap::DeleteMin(AirPlane& x)
{
	int i, j;
	if (!n)
	{
		HeapEmpty();
		return 0;
	}
	x = heap[1];
	AirPlane k = heap[n];
	n--;

	for (i = 1, j = 2; j <= n;)
	{
		if (j < n)
			if (heap[j].planedTime > heap[j + 1].planedTime) j++;
		// j points to the smaller child
		if (k.planedTime <= heap[j].planedTime) break;
		heap[i] = heap[j];
		i = j;
		j *= 2;
	}
	heap[i] = k;
	return &x;
}

AirPlane* MinHeap::DeleteMin_Emergency(AirPlane& x)
{
	int i, j;
	if (!n)
	{
		HeapEmpty();
		return 0;
	}
	x = heap[1];
	AirPlane k = heap[n];
	n--;

	for (i = 1, j = 2; j <= n;)
	{
		if (j < n)
			if (heap[j].remainingTime > heap[j + 1].remainingTime) j++;
		// j points to the smaller child
		if (k.remainingTime <= heap[j].remainingTime) break;
		heap[i] = heap[j];
		i = j;
		j *= 2;
	}
	heap[i] = k;
	return &x;
}

AirPlane::AirPlane()
{
	int rnum = (rand() * rand() % 1000);
	
	// airID generation
	if (rnum % 3) airId = "KE";
	else airId = "AA";
	string tmp = to_string(rnum % 899 + 100);
	airId.append(string(tmp));


	// airName generation
	int i = rnum % 14;
	string plane[14] = { "BOEING727", "BOEING737", "BOEING 747", "BOEING757", "BOEING767",
					"BOEING777", "BOEING787",
					"A220", "A320", "A300", "A310", "A330", "A340", "A380" };
	airName = plane[i];

	// usingType configuration
	// usingType == false : landing plane
	// usingType == true : takeofof plane
	if (rnum % 2) usingType = false;
	else true;

	// planedTime configuration
	planedTime = rnum % 86400; // 86400 second == 24 hours

	// remainingTime configuration
	// remainingTime = planedtime - currenttime
	remainingTime = planedTime;

	if (!usingType)
		remainingTime += 2000;

	waitingTime = 0;
}

AirPlane::AirPlane(int t)
{
	int rnum = (rand() * rand() % 100) + t;

	// airID generation
	if (rnum % 3) airId = "KE";
	else airId = "AA";
	string tmp = to_string(rnum % 899 + 100);
	airId.append(string(tmp));


	// airName generation
	int i = rnum % 14;
	string plane[14] = { "BOEING727", "BOEING737", "BOEING 747", "BOEING757", "BOEING767",
					"BOEING777", "BOEING787",
					"A220", "A320", "A300", "A310", "A330", "A340", "A380" };
	airName = plane[i];

	// usingType configuration
	// usingType == false : landing plane
	// usingType == true : takeofof plane
	if (rnum % 2) usingType = false;
	else true;

	// planedTime configuration
	planedTime = rnum % 86400; // 86400 second == 24 hours

	// remainingTime configuration
	// remainingTime = planedtime - currenttime
	remainingTime = planedTime;

	if (!usingType)
		remainingTime += 2000;

	waitingTime = 0;
}

AirPlane::AirPlane(const AirPlane& a)
{
	airId = a.airId;
	airName = a.airName;
	usingType = a.usingType;
	remainingTime = a.remainingTime;
	planedTime = a.planedTime;
}

void AirPlane::PrintPlane(int t)
{
	cout << "airId : " << airId << endl;
	cout << "airName : " << airName << endl;
	string type = (usingType) ? "takeoff" : "landing";
	cout << "usingType : " << type << endl;
	cout << "planedTime : " << planedTime << endl;
	if (usingType)
		cout << "Waiting Time : " << waitingTime << endl;
	else
		cout << "remainingTime : " << remainingTime << endl;
	cout << endl;
}

class ControlTower
{
public:
	ControlTower() { }
	int Control(int t);
	void Report(int t);
	void NewPlane(int t);
private:
	MaxHeap takeoff_queue = MaxHeap();
	MinHeap landing_queue = MinHeap();
	MinHeap runway_queue = MinHeap();
	int totalwait_t = 0;
	int takeoff_index = 0;
	int totalwait_l = 1;
	int land_index = 0;
};

int ControlTower::Control(int t)
{
	AirPlane currentplane;
	bool flag = true;
	if (landing_queue.heap[1].remainingTime < 2000 && (landing_queue.n != 0))
	{
		currentplane = *landing_queue.DeleteMin(currentplane);
		int i, j;
		for (i = 1; i <= runway_queue.n; i++)
		{
			if (currentplane.planedTime == runway_queue.heap[i].planedTime)
				break;
		}
		for (j = i; j < runway_queue.n; j++)
		{
			runway_queue.heap[j] = runway_queue.heap[j + 1];
		}
		runway_queue.n--;
		flag = false;
	}
	else
	{
		currentplane = *runway_queue.DeleteMin(currentplane);
	}
	bool type = currentplane.usingType;

	if (t == 0) t = currentplane.planedTime;
	
	if (type)
	{
		totalwait_t += currentplane.waitingTime;
		takeoff_index++;
		int i, j;
		for (i = 1; i <= takeoff_queue.n; i++)
		{
			if (currentplane.planedTime == takeoff_queue.heap[i].planedTime)
				break;
		}
		for (j = i; j < takeoff_queue.n; j++)
		{
			takeoff_queue.heap[j] = takeoff_queue.heap[j + 1];
		}
		takeoff_queue.n--;
		cout << t << " : " << currentplane.airId << " " 
			<< currentplane.airName << " - takeoff start" << endl;
		cout << "takeoff takes 5 minutes" << endl;
		t += 300;
		cout << t << " : " << currentplane.airId << " " << currentplane.airName
			<< " - sucessfully takeoffed" << endl;
		cout << t << " : runway prepared" << endl;
		cout << "=================================================" << endl;
		cout << "=================================================" << endl;
	}
	else
	{
		totalwait_l += currentplane.waitingTime;
		land_index++;
		cout << t << " : " << currentplane.airId << " "
			<< currentplane.airName << " - landing start" << endl;
		cout << "landing takes 3 minutes" << endl;
		t += 180;
		cout << t << " : " << currentplane.airId << " " << currentplane.airName
			<< " - sucessfully landed" << endl;
		cout << t << " : runway prepared" << endl;
		cout << "=================================================" << endl;
		cout << "=================================================" << endl;
	}
	runway_queue.RenewHeap(t);
	landing_queue.RenewHeap(t);
	takeoff_queue.RenewHeap(t);

	return t;
}

void ControlTower::Report(int t)
{
	cout << "current landing queue (RemainingTime MinQueue) : " << landing_queue.n << endl;
	landing_queue.display(t);
	cout << "=================================================" << endl;
	cout << "current takeoff queue (WaitingTime MaxQueue) : " << takeoff_queue.n << endl;
	takeoff_queue.display(t);
	cout << "=================================================" << endl;
	int mean_t, mean_l;
	mean_t = (takeoff_index == 0) ? 0 : totalwait_t / takeoff_index;
	mean_l = (land_index == 0) ? 0 : totalwait_l / land_index;
	cout << "current mean land waiting time : " << mean_l / 3600 << ":" << mean_l % 3600 / 60 
		<< ":" << mean_l % 60 << endl;
	cout << "current mean takeoff waiting time : " << mean_t / 3600 << ":" << mean_t % 3600 / 60
		<< ":" << mean_t % 60 << endl;
	cout << endl;
	cout << "=================================================" << endl;
}

void ControlTower::NewPlane(int t)
{
	AirPlane* newplane = new AirPlane(t);

	if (newplane->usingType)
		takeoff_queue.Insert(*newplane);
	else
		landing_queue.Insert_Emergency(*newplane);
	runway_queue.Insert(*newplane);
}

int main()
{
	ControlTower ct = ControlTower();
	int time = 0; // Simulation Time
	int timeindex = 0;

	// Initial Planes
	for (int i = 0; i < 3; i++)
	{
		ct.NewPlane(timeindex);
		timeindex += 420;
	}
	for (int i = 0; i < 12; i++)
	{
		ct.NewPlane(timeindex);
		timeindex += 180;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << "<< ControlTower plane control -  " << i+1 << " >>" << endl;
		ct.Report(time);
		cout << "CurrentTime - " << time / 3600 << ":" << time % 3600 / 60 << endl;
		cout << "=================================================" << endl;
		time = ct.Control(time);
	}
	for (int i = 0; i < 20; i++)
	{
		ct.NewPlane(timeindex);
		timeindex += 180;

		cout << "<< ControlTower plane control -  " << i + 11 << " >>" << endl;
		ct.Report(time);
		cout << "CurrentTime - " << time / 3600 << ":" << time % 3600 / 60 << endl;
		cout << "=================================================" << endl;
		time = ct.Control(time);
	}
	cout << "<< ControlTower plane control - 31 >>" << endl;
	ct.Report(time);
	cout << "CurrentTime - " << time / 3600 << ":" << time % 3600 / 60 << endl;
	cout << "=================================================" << endl;

	return 0;
}