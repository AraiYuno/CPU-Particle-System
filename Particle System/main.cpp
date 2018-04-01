#include "Program.h"
#include <stdexcept>
#include <iostream>

using namespace std;

int main()
{
	try
	{
		Program::Instance()->initiate();
	}
	catch (exception& e)
	{
		cout << endl << "EXCEPTION: " << e.what() << endl;
	}
}