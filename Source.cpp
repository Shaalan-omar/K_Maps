#include "k_mapFuncs.h"
using namespace std;


int main()
{
	ANSWER::input();
	ANSWER::initialize_k_map();
	string answer = ANSWER::find_answer();
	cout << "The simplfied experssion for the minterms you have entered is :  " << answer << endl;

	return 0;
}

