// STL:: vector - memory heap에 동적 할당
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> vs = { 1, 2, 3, 4, 5 };

	vector<int>::iterator it = vs.begin();
	for (it = vs.begin(); it != vs.end(); it++)
		cout << *it << "";
	cout << endl;

	string a = "have";
	string b = "nice";
	string c = "fish";
	string d = "apple";
	int n = 3;
	vector<vector<string>> table(n);
	table[0].push_back(a); // I add string 'a'to end of first vector in 'arr'
	table[0].push_back(b);
	table[1].push_back(c);
	table[1].push_back(d);

	for (int i = 0; i < table[0].size(); i++)
	{
		for (int j = 0; j < table[i].size(); j++) // print all string in first vector of 'arr'
			cout << table[i][j] << " ";
		cout << endl;
	}

	system("pause");
	return 1;
}