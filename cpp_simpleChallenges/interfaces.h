#include <iostream>
#include <string>

using namespace std;

// Interface with misc methods
class IMisc
{
public:

	// easy overloaded print methods 
	void print(string _text, bool breakline = 0)
	{
		cout << _text;

		if (breakline)
			breakln();
	}

	void print(int _number, bool breakline = 0)
	{
		cout << _number;

		if (breakline)
			breakln();
	}

	void breakln()
	{
		cout << endl;
	}
};
