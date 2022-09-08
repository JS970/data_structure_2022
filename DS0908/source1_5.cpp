#include <iostream>

using namespace std;

#define N 10

class Employee {

	int enum;
	string ename;
	float salary;
	string dept;
	static int count;//객체가 생성될 때마다 count++

public:
	Employee();
	Employee(int);
	Employee(const Employee&);
	~Employee();
	Employee& operator=(const Employee&);
	int operator++();
	static int Show();//count 값을 초기화
	friend ostream& operator << (ostream& stream, Employee&);
};



Employee::Employ() { ... }
Employee::Employ(int n) { ... }

class EmpTable {//객체 배열 처리하는 클래스

	int top;
	Employee data[N];
public:
	void initializeEmployee();
	void ShowEmployee();
};



void EmpTable::initializeEmployee()
{
	int n = top;

	for (int i = 0; i < n; i++)
	{
		cin >> enum >> ....
			data[i] = new Employee(...);
	}
}



void EmpTable::ShowEmployee() {

	...

}



void main() {

	int num = N;
	EmpTable empt;
	empt.initializeEmployee();
	empt.showEmployee();
	system("pause");
}