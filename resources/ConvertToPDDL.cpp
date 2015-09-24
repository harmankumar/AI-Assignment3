#include <bits/stdc++.h>

using namespace std;

int main()
{
	int M,N,num_cars;
	f>>M>>N>>num_cars;
	int id,len,xleft,ytop;
	char orientation;

	for(int i=0; i<num_cars; i++)
	{
		f>>id>>len>>xleft>>ytop;
		f>>orientation;
	}
	ifstream f;
	f.open("input.txt");

	// File read, convert it to PDDL.

/*  In the PDDL domain, the start state has to be specified.
	Start state depends on the input file.
	Actions are universal for every state.
	Goal state depends on the input file.
*/
}