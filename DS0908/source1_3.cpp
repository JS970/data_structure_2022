// source 1.3 : Simple class implementation
#include <iostream>
using namespace std;

class Employee {
	int enum;
	string ename;
	float salary;
	string dept;
	static int count; // count++ when object is generated

public:
	Employee();
	Employee(int);
	Employee(const Employee&);
	~Employee();
	Employee& operator=(const Employee&);
	int operator++;
	static int Show(); //count value initialize
	friend ostream& operator << (ostream& stream, Employee&);
};

void main() {
	Employee sd1;
	Employee sd2(10);
	Employee sd3(sd2);
	Employee::Show();
	sd1.Show();
	Employee sd4 = sd2;
	sd3 = sd2;
	cout << endl;
	cout << sd4;
	system("pause");
}