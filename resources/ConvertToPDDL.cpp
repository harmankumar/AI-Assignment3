#include <bits/stdc++.h>

using namespace std;

struct vroom
{
	int id;
	int length;
	int xleft;
	int ytop;
	char orient; 
};

string tostring(int Number)
{
	string String = static_cast<ostringstream*>( &(ostringstream() << Number) )->str();
	return String;
}

int main()
{
	vector<vroom> car_info;
	ifstream f;
	f.open("input.txt");
	int M,N,num_cars;
	f>>M>>N>>num_cars;
	int goalx,goaly;

	vroom thiscar;
	for(int i=0; i<num_cars; i++)
	{
		f >> thiscar.id >> thiscar.length >> thiscar.xleft >> thiscar.ytop;
		f >> thiscar.orient;
		car_info.push_back(thiscar);
	}

	f>>goalx>>goaly;

	f.close();

	ofstream f1;
	f1.open("problem.pddl");

	f1<<"(define (car management)"<<endl<<endl;

	f1<<"(:domain"<<endl<<"car-domain"<<endl<<")";

	//defining objects


	f1<<"(:objects"<<endl;
	string s1;
	char x = '0';
	for(int i=0; i<num_cars; i++)
	{
		s1 = "car" + tostring(i);   //adding cars
		s1 += " "; 
		f1<<s1;
	}
	f1<<endl;

	for(int i=0; i<M; i++)
	{
		for(int j=0; j<N; j++)
		{
			s1 = "block" + tostring(i) + tostring(j) + " ";	//Adding blocks.
			f1<<s1;
		}
		f1<<endl;
	}
	f1<<endl;
	// Done with blocks
	
	f1<<")";	
	f1<<endl;
	// Done with objects.

//starting intial state

	f1<<"(:init"<<endl;
	// Initializing cars.
	for(int i=0; i<num_cars; i++)
	{
		s1 = "(CAR car" + tostring(i) + ") ";  
		f1<<s1;
	}
	f1<<endl;

	//Initializing blocks.
	for(int i=0; i<M; i++)
	{
		for(int j=0; j<N; j++)
		{
			s1 = "(BLOCK block" + tostring(i) + tostring(j) + ") ";	//Adding blocks.
			f1<<s1;
		}
		f1<<endl;
	}
	f1<<endl;

	for(int i=0; i<M; i++)
	{
		for(int j=0; j<N-1; j++)
		{
			s1 = "(CONNECTEDH block" + tostring(i) + tostring(j) + " block" + tostring(i) + tostring(j+1) + ") ";	//Adding blocks.
			f1<<s1;
			s1 = "(CONNECTEDH block" + tostring(i) + tostring(j+1) + " block" + tostring(i) + tostring(j) + ") ";	//Adding blocks.
			f1<<s1;
		}
		f1<<endl;
	}
	f1<<endl;

	for(int i=0; i<M-1; i++)
	{
		for(int j=0; j<N; j++)
		{
			s1 = "(CONNECTEDV block" + tostring(i) + tostring(j) + " block" + tostring(i) + tostring(j) + ") ";	//Adding blocks.
			f1<<s1;
			s1 = "(CONNECTEDV block" + tostring(i+1) + tostring(j) + " block" + tostring(i) + tostring(j) + ") ";	//Adding blocks.
			f1<<s1;
		}
		f1<<endl;
	}
	f1<<endl;

	bool isfilled[M][N];

	for(int i = 0; i<car_info.size(); i++)
	{
		if(car_info[i].orient == 'H')
		{
			f1<<"(HORIZONTAL car" + tostring(i) + ") ";

			for(int j = 0; j<car_info[i].length; j++)
			{
				isfilled[car_info[i].xleft + j][car_info[i].ytop] = true;
			}
		}

		else
		{
			f1<<"(VERTICAL car" + tostring(i) + ") ";

			for(int j = 0; j<car_info[i].length; j++)
			{
				isfilled[car_info[i].xleft][car_info[i].ytop - j] = true;
			}
		}
	}

	for(int i = 0; i<car_info.size(); i++)
	{
		if(car_info[i].orient == 'H')
		{
			f1<<"(FRONTEND car"<<tostring(i)<<" block"<<tostring(car_info[i].xleft)<<tostring(car_info[i].ytop)<<") ";
			f1<<"(BACKEND car"<<tostring(i)<<" block"<<tostring(car_info[i].xleft + car_info[i].length - 1)<<tostring(car_info[i].ytop)<<") ";
		}

		else
		{
			f1<<"(FRONTEND car"<<tostring(i)<<" block"<<tostring(car_info[i].xleft)<<tostring(car_info[i].ytop)<<") ";
			f1<<"(BACKEND car"<<tostring(i)<<" block"<<tostring(car_info[i].xleft)<<tostring(car_info[i].ytop - car_info[i].length + 1)<<") ";
		}
	}
	f1<<endl;

	//initialising empty
	for(int i = 0; i<M; i++)
	{
		for(int j=0; j<N; j++)
		{
			if(!isfilled[i][j])
				f1<<"(EMPTY block" + tostring(i) + tostring(j) + ") ";
		}
	}
	f1<<endl<<endl;

	f1<<")";	// Done with initial conds.
	f1<<endl;


	// Goal State

	f1<<"(:goal"<<endl;
	f1<<"(:and"<<endl;

	s1 = "(FRONTEND car1 block" + tostring(goalx) + tostring(goaly) + ") ";	//Adding blocks.
	
	f1<<s1<<endl;
	f1<<")"<<endl;	
	f1<<")";	
	// Done with goal state.


//final ending
	f1<<")";
	f1.close();



	ofstream f2;
	f2.open("domain.pddl");

	f2<<"(define (domain car-domain)"<<endl;
		f2<<"(:predicates"<<endl;
			f2<<"(CAR ?car-id)"<<endl;
			f2<<"(BLOCK ?block-id)"<<endl;
			f2<<"(EMPTY ?block-id)"<<endl;
			f2<<"(FRONTEND ?car-id ?block-id)"<<endl;
			f2<<"(BACKEND ?car-id ?block-id)"<<endl;
			f2<<"(CONNECTEDH ?from-block ?to-block)"<<endl;
			f2<<"(CONNECTEDV ?from-block ?to-block)"<<endl;
			f2<<"(HORIZONTAL ?car-id)"<<endl;
			f2<<"(VERTICAL ?car-id)"<<endl;
		f2<<")"<<endl;

		//action starts
		f2<<"(:action forMoveX"<<endl;
			f2<<":parameters ( "<<endl;
				f2<<"?carId ";
				f2<<"?blockFrontOld ";
				f2<<"?blockFrontNew ";
				f2<<"?blockBackOld ";
				f2<<"?blockBackNew"<<endl;
			f2<<")"<<endl;


			f2<<":precondition"<<endl;
				f2<<"(and"<<endl;
					f2<<"(CAR ?carId)"<<endl;
					f2<<"(HORIZONTAL ?carId)"<<endl;
					f2<<"(BLOCK ?blockFrontOld) (BLOCK ?blockFrontNew) (BLOCK ?blockBackOld) (BLOCK ?blockBackNew)"<<endl;
					f2<<"(CONNECTEDH ?blockFrontOld ?blockFrontNew) (CONNECTEDH ?blockBackOld ?blockBackOld)"<<endl;
					f2<<"(FRONTEND ?carId ?blockFrontOld) (BACKEND ?carId ?blockBackOld)"<<endl;
					f2<<"(EMPTY ?blockFrontNew)"<<endl;
			f2<<")"<<endl;


			f2<<":effect"<<endl;
				f2<<"(and"<<endl;
					f2<<"(EMPTY ?blockBackOld)"<<endl;
					f2<<"(not (EMPTY ?blockFrontNew))"<<endl;
					f2<<"(FRONTEND ?carId ?blockFrontNew) (BACKEND ?carId ?blockBackNew)"<<endl;
					f2<<"(not (FRONTEND ?carId ?blockFrontOld)) (not (BACKEND ?carId ?blockBackOld))"<<endl;
			f2<<")"<<endl;
		f2<<")"<<endl; // action ends



		//action starts
		f2<<"(:action backMoveX"<<endl;
			f2<<":parameters ( "<<endl;
				f2<<"?carId ";
				f2<<"?blockFrontOld ";
				f2<<"?blockFrontNew ";
				f2<<"?blockBackOld ";
				f2<<"?blockBackNew"<<endl;
			f2<<")"<<endl;

			f2<<":precondition"<<endl;
				f2<<"(and"<<endl;
					f2<<"(CAR ?carId)"<<endl;
					f2<<"(HORIZONTAL ?carId)"<<endl;
					f2<<"(BLOCK ?blockFrontOld) (BLOCK ?blockFrontNew) (BLOCK ?blockBackOld) (BLOCK ?blockBackNew)"<<endl;
					f2<<"(CONNECTEDH ?blockFrontOld ?blockFrontNew) (CONNECTEDH ?blockBackOld ?blockBackOld)"<<endl;
					f2<<"(FRONTEND ?carId ?blockFrontOld) (BACKEND ?carId ?blockBackOld)"<<endl;
					f2<<"(EMPTY ?blockBackNew)"<<endl;
			f2<<")"<<endl;


			f2<<":effect"<<endl;
				f2<<"(and"<<endl;
					f2<<"(EMPTY ?blockFrontOld)"<<endl;
					f2<<"(not (EMPTY ?blockBackNew))"<<endl;
					f2<<"(FRONTEND ?carId ?blockFrontNew) (BACKEND ?carId ?blockBackNew)"<<endl;
					f2<<"(not (FRONTEND ?carId ?blockFrontOld)) (not (BACKEND ?carId ?blockBackOld))"<<endl;
			f2<<")"<<endl;
		f2<<")"<<endl; // action ends



		//action starts
		f2<<"(:action forMoveY"<<endl;
			f2<<":parameters ( "<<endl;
				f2<<"?carId ";
				f2<<"?blockFrontOld ";
				f2<<"?blockFrontNew ";
				f2<<"?blockBackOld ";
				f2<<"?blockBackNew"<<endl;
			f2<<")"<<endl;


			f2<<":precondition"<<endl;
				f2<<"(and"<<endl;
					f2<<"(CAR ?carId)"<<endl;
					f2<<"(VERTICAL ?carId)"<<endl;
					f2<<"(BLOCK ?blockFrontOld) (BLOCK ?blockFrontNew) (BLOCK ?blockBackOld) (BLOCK ?blockBackNew)"<<endl;
					f2<<"(CONNECTEDH ?blockFrontOld ?blockFrontNew) (CONNECTEDH ?blockBackOld ?blockBackOld)"<<endl;
					f2<<"(FRONTEND ?carId ?blockFrontOld) (BACKEND ?carId ?blockBackOld)"<<endl;
					f2<<"(EMPTY ?blockFrontNew)"<<endl;
			f2<<")"<<endl;


			f2<<":effect"<<endl;
				f2<<"(and"<<endl;
					f2<<"(EMPTY ?blockBackOld)"<<endl;
					f2<<"(not (EMPTY ?blockFrontNew))"<<endl;
					f2<<"(FRONTEND ?carId ?blockFrontNew) (BACKEND ?carId ?blockBackNew)"<<endl;
					f2<<"(not (FRONTEND ?carId ?blockFrontOld)) (not (BACKEND ?carId ?blockBackOld))"<<endl;
			f2<<")"<<endl;
		f2<<")"<<endl; // action ends



		//action starts
		f2<<"(:action backMoveY"<<endl;
			f2<<":parameters ( "<<endl;
				f2<<"?carId ";
				f2<<"?blockFrontOld ";
				f2<<"?blockFrontNew ";
				f2<<"?blockBackOld ";
				f2<<"?blockBackNew"<<endl;
			f2<<")"<<endl;

			f2<<":precondition"<<endl;
				f2<<"(and"<<endl;
					f2<<"(CAR ?carId)"<<endl;
					f2<<"(VERTICAL ?carId)"<<endl;
					f2<<"(BLOCK ?blockFrontOld) (BLOCK ?blockFrontNew) (BLOCK ?blockBackOld) (BLOCK ?blockBackNew)"<<endl;
					f2<<"(CONNECTEDH ?blockFrontOld ?blockFrontNew) (CONNECTEDH ?blockBackOld ?blockBackOld)"<<endl;
					f2<<"(FRONTEND ?carId ?blockFrontOld) (BACKEND ?carId ?blockBackOld)"<<endl;
					f2<<"(EMPTY ?blockBackNew)"<<endl;
			f2<<")"<<endl;

			f2<<":effect"<<endl;
				f2<<"(and"<<endl;
					f2<<"(EMPTY ?blockFrontOld)"<<endl;
					f2<<"(not (EMPTY ?blockBackNew))"<<endl;
					f2<<"(FRONTEND ?carId ?blockFrontNew) (BACKEND ?carId ?blockBackNew)"<<endl;
					f2<<"(not (FRONTEND ?carId ?blockFrontOld)) (not (BACKEND ?carId ?blockBackOld))"<<endl;
			f2<<")"<<endl;
		f2<<")"<<endl; // action ends
	f2<<")"<<endl;
	f2.close();
















	return 0;
}