// source 1.3 : Simple class implementation
#include <iostream>
using namespace std;

class Employee {
	int enumb; // enum -> enumb
	string ename;
	float salary;
	string dept;
	static int count; // count++ when object is generated
	

public:
	Employee() 
	{
		enumb = 0;
		ename = "undefined";
		salary = 0.0;
		dept = "undefined";
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

// static member of class must be initialized outside of main function...? - 2022.09.12
int Employee::count = 0;

int main() {
	Employee sd1;
	Employee sd2(10);
	Employee sd3(sd1);
	Employee::Show();
	sd1.Show();
	Employee sd4 = sd2;
	sd3 = sd2;
	cout << endl;
	cout << sd4;
	system("pause");
}