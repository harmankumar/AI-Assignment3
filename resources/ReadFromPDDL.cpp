#include <bits/stdc++.h>

using namespace std;


string toString(int Number)
{
	string String = static_cast<ostringstream*>( &(ostringstream() << Number) )->str();
	return String;
}

string getID(string carname)
{
	carname.erase(0,3);
	int id = atoi (carname.c_str());
	return toString(id+1);
}

string getMove(char a)
{
	if(a == 'U')
		return "U";
	if(a == 'D')
		return "D";
	if(a == 'L')
		return "L";
	if(a == 'R')
		return "R";
}

int main()
{
	ifstream in;
	in.open("sas_plan");
	if (in.is_open())
	{
		cout<<"Opened"<<endl;
	}
	else
	{
		cout<<"There is some error"<<endl;
		return 5;
	}
	string current;
	in>>current;
	int freq = 0;
	string carName,trash;
	char move;
	vector <string> finalData;
	int count = 0;
	while(current[0] != ';')
	{
		count++;
		// cout<<"analysing line "<<count<<"\t"<<current<<endl;
		if(current.compare("(upmove") == 0)
		{
			if(count != 1){
				string line = getID(carName) + " " + getMove(move) + " " + toString(freq);
				finalData.push_back(line);
			}
			in>>carName;
			freq = 1;
			move = 'U';
			for(int i=0;i<6;i++)
				in>>trash;
		}
		else if(current.compare("(downmove") == 0)
		{
			if(count != 1){
				string line = getID(carName) + " " + getMove(move) + " " + toString(freq);
				finalData.push_back(line);
			}
			in>>carName;
			freq = 1;
			move = 'D';
			for(int i=0;i<6;i++)
				in>>trash;
		}
		else if(current.compare("(leftmove") == 0)
		{
			if(count != 1){
				string line = getID(carName) + " " + getMove(move) + " " + toString(freq);
				finalData.push_back(line);
			}
			in>>carName;
			freq = 1;
			move = 'L';
			for(int i=0;i<6;i++)
				in>>trash;
		}
		else if(current.compare("(rightmove") == 0)
		{
			if(count != 1){
				string line = getID(carName) + " " + getMove(move) + " " + toString(freq);
				finalData.push_back(line);
			}
			in>>carName;
			freq = 1;
			move = 'R';
			for(int i=0;i<6;i++)
				in>>trash;
		}
		else if(current.compare("(upmoveoptimal") == 0)
		{
			in>>carName;
			freq++;
			for(int i=0;i<5;i++)
				in>>trash;
		}
		else if(current.compare("(downmoveoptimal") == 0)
		{
			in>>carName;
			freq++;
			for(int i=0;i<5;i++)
				in>>trash;
		}
		else if(current.compare("(leftmoveoptimal") == 0)
		{
			in>>carName;
			freq++;
			for(int i=0;i<5;i++)
				in>>trash;
		}
		else if(current.compare("(rightmoveoptimal") == 0)
		{
			in>>carName;
			freq++;
			for(int i=0;i<5;i++)
				in>>trash;
		}
		in>>current;

	}
	string line = getID(carName) + " " + getMove(move) + " " + toString(freq);
	finalData.push_back(line);
	in.close();
//--------------------------
	ofstream out;
	out.open("finalOutput.txt");
	out<<finalData.size()<<endl;
	for(int i=0; i<finalData.size(); i++)
	{
		out<<finalData[i]<<endl;
	}
	out.close();
	return 0;
}