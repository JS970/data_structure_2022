// source 1.4 : object array
#include <iostream>
using namespace std;
#define N 3
class Employee
{
	int enumb;
	string ename;
	float salary;
	string dept;
	static int count;
public:
	Employee()
	{
		cout << "put parameters" << endl;
		cout << "enumb : ";
		cin >> enumb;
		cout << "ename : ";
		cin >> ename;
		cout << "salary : ";
		cin >> salary;
		cout << "dept : ";
		cin >> dept;
		cout << endl;
		count++;
	}
	Employee(int enumb_input)
	{
		enumb = enumb_input;
		ename = "undefined";
		salary = 0.0;
		dept = "undefined";
		count++;
	}
	Employee(const Employee& e)
	{
		enumb = e.enumb;
		ename = e.ename;
		salary = e.salary;
		dept = e.dept;
		count++;
	}
	~Employee()
	{
		count = count - 1;
	}
	Employee operator=(const Employee& e)
	{
		Employee res(e);
		return res;
	}
	int operator++()
	{
		count++;
	}
	static int Show() //count value initialize
	{
		cout << "current count value : " << count << endl;
		count = 0;
		cout << "count value initialized" << endl;

		return count;
	}
	void showparam()
	{
		cout << "enumb : " << enumb << endl;
		cout << "ename : " << ename << endl;
		cout << "salary : " << salary << endl;
		cout << "dept : " << dept << endl;
	}
	friend ostream& operator << (ostream& stream, Employee& e)
	{
		stream << "enumb : " << e.enumb << endl;
		stream << "ename : " << e.ename << endl;
		stream << "salary : " << e.salary << endl;
		stream << "dept : " << e.dept << endl;
		stream << "current count : " << count << endl;

		return stream;
	}
};

void initializeEmployee(Employee* emp[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "initialization of employee emp[" << i << "]" << endl;
		emp[i] = new Employee();
		cout << endl;
	}
}
void ShowEmployee(Employee* emp[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "show employee emp[" << i << "]'s parameter" << endl;
		emp[i]->showparam();
		cout << endl;
	}
}

int Employee::count = 0;

int main()
{
	int num = N;
	Employee* emp[N]; // array of objects
	initializeEmployee(emp, num);
	ShowEmployee(emp, num);
}