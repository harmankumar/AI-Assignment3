#include <bits/stdc++.h>

using namespace std;

struct vroom
{
	int id;
	int length;
	int col;		//xleft
	int row;		//ytop
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
	f.open("problem.txt");
	int M,N,num_cars;
	f>>M>>N>>num_cars;
	int goalx,goaly;

	vroom thiscar;
	for(int i=0; i<num_cars; i++)
	{
		f >> thiscar.id >> thiscar.length >> thiscar.col >> thiscar.row;
		f >> thiscar.orient;
		thiscar.col--;
		thiscar.row--;
		car_info.push_back(thiscar);
	}

	f>>goalx>>goaly;
	goalx--;
	goaly--;

	f.close();

	ofstream f1;
	f1.open("problem.pddl");

	f1<<"(define (problem car-management)"<<endl<<endl;
	f1<<"\t(:domain car-domain)"<<endl;

	//defining objects
	f1<<"\t(:objects"<<endl<<"\t\t";
		string s1;
		char x = '0';
		for(int i=0; i<num_cars; i++)
		{
			s1 = "car" + tostring(i);   //adding cars
			s1 += " "; 
			f1<<s1;
		}
		f1<<"cart";
		f1<<endl<<"\t\t";

		//adding cols
		for (int i=0; i<N; i++)
		{
				s1 = "x" + tostring(i) + " ";
				f1<<s1;
		}
		f1<<endl<<"\t\t";

		//adding rows
		for (int i=0; i<M; i++)
		{
				s1 = "y" + tostring(i) + " ";
				f1<<s1;
		}
		f1<<endl<<"\t\t";

	f1<<"\t)";	
	f1<<endl;
	// Done with objects.



	//starting intial state
	f1<<"\t(:init"<<endl<<"\t\t";
		// Initializing cars.
		for(int i=0; i<num_cars; i++)
		{
			s1 = "(CAR car" + tostring(i) + ") ";  
			f1<<s1;
		}
		f1<<"(CAR cart)";
		f1<<endl<<"\t\t";

		//Initialising prevStates
		f1<<"(PREV cart) ";
		for(int i=0; i<num_cars; i++)
		{
			s1 = "(SMPL car" + tostring(i) + ") ";  
			f1<<s1;
		}
		f1<<endl<<"\t\t";
		//initialising cols
		for (int i=0; i<N; i++)
		{
				s1 = "(COLX x" + tostring(i) + ") ";
				f1<<s1;
		}
		f1<<endl<<"\t\t";

		//initialising rows
		for (int i=0; i<M; i++)
		{
				s1 = "(ROWY y" + tostring(i) + ") ";
				f1<<s1;
		}
		f1<<endl<<"\t\t";

		//connectivity
		for (int i=0; i<N-1; i++)
		{
			s1 = "(FOR x" + tostring(i) + " x" + tostring(i+1) + ") ";
			f1<<s1;
		}
		f1<<endl<<"\t\t";
		for (int i=0; i<M-1; i++)
		{
			s1 = "(FOR y" + tostring(i) + " y" + tostring(i+1) + ") ";
			f1<<s1;
		}
		f1<<endl<<"\t\t";
		for (int i=1; i<N; i++)
		{
			s1 = "(BAC x" + tostring(i) + " x" + tostring(i-1) + ") ";
			f1<<s1;
		}
		f1<<endl<<"\t\t";
		for (int i=1; i<M; i++)
		{
			s1 = "(BAC y" + tostring(i) + " y" + tostring(i-1) + ") ";
			f1<<s1;
		}
		f1<<endl<<"\t\t";

		// Orienting cars.
		for(int i=0; i<num_cars; i++)
		{
			if(car_info[i].orient == 'H')
			{
				s1 = "(HOR car" + tostring(i) + ") ";
			}
			else
			{
				s1 = "(VER car" + tostring(i) + ") ";
			}
			f1<<s1;
		}
		f1<<endl<<"\t\t";


		//positioning cars
		bool isfilled[M][N];
		for(int i = 0; i<car_info.size(); i++)
		{
			vroom temp = car_info[i];
			if(temp.orient == 'H')
			{
				for(int j = 0; j<temp.length; j++)
				{
					isfilled[car_info[i].row][car_info[i].col + j] = true;
				}
				s1 = "(POSITION car" + tostring(i) + " x" + tostring(temp.col) + " x" + 
							tostring(temp.col + temp.length - 1) + " y" + tostring(temp.row) + ")";
			}
			else
			{
				for(int j = 0; j<temp.length; j++)
				{
					isfilled[car_info[i].row + j][car_info[i].col] = true;
				}
				s1 = "(POSITION car" + tostring(i) + " y" + tostring(temp.row) + " y" + 
							tostring(temp.row + temp.length - 1) + " x" + tostring(temp.col) +")";
			}
			f1<<s1<<endl<<"\t\t";
		}
		f1<<endl<<"\t\t";

		//initialising empty
		for(int i = 0; i<N; i++)
		{
			for(int j=0; j<M; j++)
			{
				if(!isfilled[j][i])
					f1<<"(EMPTY x" + tostring(i) + " y" + tostring(j) + ") ";
			}
			f1<<endl<<"\t\t";
		}
		f1<<endl<<"\t\t";

		f1<<"(= (total-cost) 0)"<<endl;
	f1<<"\t)";	// Done with initial conds.
	f1<<endl;


	// Goal State
	f1<<"\t(:goal"<<endl;
		if(car_info[0].orient == 'H')
		{
			s1 = "(POSITION car0 x" + tostring(goalx) + " x" + 
				tostring(goalx + car_info[0].length - 1) + " y" + tostring(goaly) + ") ";
		}
		else
		{
			s1 = "(POSITION car0 y" + tostring(goaly) + " y" + 
				tostring(goaly + car_info[0].length - 1) + " x" + tostring(goalx) + ") ";
		}
		f1<<"\t\t"<<s1<<endl;
	f1<<"\t)";	
	

	// Minimize metric
	f1<<"\t(:metric minimize (total-cost))";


//final ending
	f1<<")";
	f1.close();



	ofstream f2;
	f2.open("problem-domain.pddl");

	f2<<"(define (domain car-domain)"<<endl;
		f2<<"\t(:requirements :strips)"<<endl;
		f2<<"\t(:predicates"<<endl;
			f2<<"\t\t(CAR ?carId)"<<endl;
			f2<<"\t\t(ROWY ?y)"<<endl;
			f2<<"\t\t(COLX ?x)"<<endl;
			f2<<"\t\t(POSITION ?carId ?front ?back ?cons)"<<endl;
			f2<<"\t\t(HOR ?c)"<<endl;
			f2<<"\t\t(VER ?c)"<<endl;
			f2<<"\t\t(EMPTY ?x ?y)"<<endl;
			f2<<"\t\t(FOR ?u ?v)"<<endl;
			f2<<"\t\t(BAC ?u ?v)"<<endl;
			f2<<"\t\t(PREV ?carId)"<<endl;
			f2<<"\t\t(SMPL ?carId)"<<endl;
		f2<<")"<<endl;


		f2<<"\t(:functions (total-cost))"<<endl;




		//action starts
		f2<<"\t(:action leftMoveOptimal"<<endl;
			f2<<"\t\t:parameters ( "<<endl;
				f2<<"\t\t\t?carId ";
				f2<<"?prevXleft ";
				f2<<"?prevXright ";
				f2<<"?yIndex ";
				f2<<"?finalXleft ";
				f2<<"?finalXright ";
			f2<<")"<<endl;

			f2<<"\t\t:precondition"<<endl;
				f2<<"\t\t\t(and"<<endl;
					f2<<"\t\t\t\t(CAR ?carId) (PREV ?carId)"<<endl;
					f2<<"\t\t\t\t(HOR ?carId)"<<endl;
					f2<<"\t\t\t\t(COLX ?prevXleft) (COLX ?prevXright)"<<endl;
					f2<<"\t\t\t\t(ROWY ?yIndex)"<<endl;
					f2<<"\t\t\t\t(COLX ?finalXleft) (COLX ?finalXright)"<<endl;
					f2<<"\t\t\t\t(BAC ?prevXleft ?finalXleft) (BAC ?prevXright ?finalXright)"<<endl;
					f2<<"\t\t\t\t(POSITION ?carId ?prevXleft ?prevXright ?yIndex)"<<endl;
					f2<<"\t\t\t\t(EMPTY ?finalXleft ?yIndex)"<<endl;
			f2<<"\t\t)"<<endl;

			f2<<"\t\t:effect"<<endl;
				f2<<"\t\t\t(and"<<endl;
					f2<<"\t\t\t\t(not(POSITION ?carId ?prevXleft ?prevXright ?yIndex))"<<endl;
					f2<<"\t\t\t\t(not(EMPTY ?finalXleft ?yIndex))"<<endl;
					f2<<"\t\t\t\t(POSITION ?carId ?finalXleft ?finalXright ?yIndex)"<<endl;
					f2<<"\t\t\t\t(EMPTY ?prevXright ?yIndex)"<<endl;
					f2<<"\t\t\t\t(increase (total-cost) 1)"<<endl;
			f2<<"\t\t)"<<endl;
		f2<<"\t)"<<endl; // action ends



				//action starts
		f2<<"\t(:action rightMoveOptimal"<<endl;
			f2<<"\t\t:parameters ( "<<endl;
				f2<<"\t\t\t?carId ";
				f2<<"?prevXleft ";
				f2<<"?prevXright ";
				f2<<"?yIndex ";
				f2<<"?finalXleft ";
				f2<<"?finalXright ";
			f2<<")"<<endl;

			f2<<"\t\t:precondition"<<endl;
				f2<<"\t\t\t(and"<<endl;
					f2<<"\t\t\t\t(CAR ?carId) (PREV ?carId)"<<endl;
					f2<<"\t\t\t\t(HOR ?carId)"<<endl;
					f2<<"\t\t\t\t(COLX ?prevXleft) (COLX ?prevXright)"<<endl;
					f2<<"\t\t\t\t(ROWY ?yIndex)"<<endl;
					f2<<"\t\t\t\t(COLX ?finalXleft) (COLX ?finalXright)"<<endl;
					f2<<"\t\t\t\t(FOR ?prevXleft ?finalXleft) (FOR ?prevXright ?finalXright)"<<endl;
					f2<<"\t\t\t\t(POSITION ?carId ?prevXleft ?prevXright ?yIndex)"<<endl;
					f2<<"\t\t\t\t(EMPTY ?finalXRight ?yIndex)"<<endl;
			f2<<"\t\t)"<<endl;

			f2<<"\t\t:effect"<<endl;
				f2<<"\t\t\t(and"<<endl;
					f2<<"\t\t\t\t(not(POSITION ?carId ?prevXleft ?prevXright ?yIndex))"<<endl;
					f2<<"\t\t\t\t(not(EMPTY ?finalXright ?yIndex))"<<endl;
					f2<<"\t\t\t\t(POSITION ?carId ?finalXleft ?finalXright ?yIndex)"<<endl;
					f2<<"\t\t\t\t(EMPTY ?prevXleft ?yIndex)"<<endl;
					f2<<"\t\t\t\t(increase (total-cost) 1)"<<endl;
			f2<<"\t\t)"<<endl;
		f2<<"\t)"<<endl; // action ends


		//action starts
		f2<<"\t(:action upMoveOptimal"<<endl;
			f2<<"\t\t:parameters ( "<<endl;
				f2<<"\t\t\t?carId ";
				f2<<"?prevYtop";
				f2<<"?prevYbottom";
				f2<<"?xIndex";
				f2<<"?finalYtop";
				f2<<"?finalYbottom";
			f2<<")"<<endl;

			f2<<"\t\t:precondition"<<endl;
				f2<<"\t\t\t(and"<<endl;
					f2<<"\t\t\t\t(CAR ?carId) (PREV ?carId)"<<endl;
					f2<<"\t\t\t\t(VER ?carId)"<<endl;
					f2<<"\t\t\t\t(ROWY ?prevYtop) (ROWY ?prevYbottom)"<<endl;
					f2<<"\t\t\t\t(COLX ?xIndex)"<<endl;
					f2<<"\t\t\t\t(ROWY ?finalYtop) (ROWY ?finalYbottom)"<<endl;
					f2<<"\t\t\t\t(BAC ?prevYtop ?finalYtop) (BAC ?prevYbottom ?finalYbottom)"<<endl;
					f2<<"\t\t\t\t(POSITION ?carId ?prevYtop ?prevYbottom ?xIndex)"<<endl;
					f2<<"\t\t\t\t(EMPTY ?xIndex ?finalYtop)"<<endl;
			f2<<"\t\t)"<<endl;

			f2<<"\t\t:effect"<<endl;
				f2<<"\t\t\t(and"<<endl;
					f2<<"\t\t\t\t(not(POSITION ?carId ?prevYtop ?prevYbottom ?xIndex))"<<endl;
					f2<<"\t\t\t\t(not(EMPTY ?xIndex ?finalYtop))"<<endl;
					f2<<"\t\t\t\t(POSITION ?carId ?finalYtop ?finalYbottom ?xIndex)"<<endl;
					f2<<"\t\t\t\t(EMPTY ?xIndex ?prevYbottom)"<<endl;
					f2<<"\t\t\t\t(increase (total-cost) 1)"<<endl;
			f2<<"\t\t)"<<endl;
		f2<<"\t)"<<endl; // action ends


		//action starts
		f2<<"\t(:action downMoveOptimal"<<endl;
			f2<<"\t\t:parameters ( "<<endl;
				f2<<"\t\t\t?carId ";
				f2<<"?prevYtop";
				f2<<"?prevYbottom";
				f2<<"?xIndex";
				f2<<"?finalYtop";
				f2<<"?finalYbottom";
			f2<<")"<<endl;

			f2<<"\t\t:precondition"<<endl;
				f2<<"\t\t\t(and"<<endl;
					f2<<"\t\t\t\t(CAR ?carId) (PREV ?carId)"<<endl;
					f2<<"\t\t\t\t(VER ?carId)"<<endl;
					f2<<"\t\t\t\t(ROWY ?prevYtop) (ROWY ?prevYbottom)"<<endl;
					f2<<"\t\t\t\t(COLX ?xIndex)"<<endl;
					f2<<"\t\t\t\t(ROWY ?finalYtop) (ROWY ?finalYbottom)"<<endl;
					f2<<"\t\t\t\t(FOR ?prevYbottom ?finalYbottom) (FOR ?prevYtop ?finalYtop)"<<endl;
					f2<<"\t\t\t\t(POSITION ?carId ?prevYtop ?prevYbottom ?xIndex)"<<endl;
					f2<<"\t\t\t\t(EMPTY ?xIndex ?finalYbottom)"<<endl;
			f2<<"\t\t)"<<endl;

			f2<<"\t\t:effect"<<endl;
				f2<<"\t\t\t(and"<<endl;
					f2<<"\t\t\t\t(not(POSITION ?carId ?prevYtop ?prevYbottom ?xIndex))"<<endl;
					f2<<"\t\t\t\t(not(EMPTY ?xIndex ?finalYbottom))"<<endl;
					f2<<"\t\t\t\t(POSITION ?carId ?finalYtop ?finalYbottom ?xIndex)"<<endl;
					f2<<"\t\t\t\t(EMPTY ?xIndex ?prevYtop)"<<endl;
					f2<<"\t\t\t\t(increase (total-cost) 1)"<<endl;
			f2<<"\t\t)"<<endl;
		f2<<"\t)"<<endl; // action ends



		//action starts
		f2<<"\t(:action leftMove"<<endl;
			f2<<"\t\t:parameters ( "<<endl;
				f2<<"\t\t\t?carId ";
				f2<<"?carIdMark ";
				f2<<"?prevXleft ";
				f2<<"?prevXright ";
				f2<<"?yIndex ";
				f2<<"?finalXleft ";
				f2<<"?finalXright ";
			f2<<")"<<endl;

			f2<<"\t\t:precondition"<<endl;
				f2<<"\t\t\t(and"<<endl;
					f2<<"\t\t\t\t(CAR ?carId) (CAR ?carIdMark) (SMPL ?carId) (PREV ?carIdMark)"<<endl;
					f2<<"\t\t\t\t(HOR ?carId)"<<endl;
					f2<<"\t\t\t\t(COLX ?prevXleft) (COLX ?prevXright)"<<endl;
					f2<<"\t\t\t\t(ROWY ?yIndex)"<<endl;
					f2<<"\t\t\t\t(COLX ?finalXleft) (COLX ?finalXright)"<<endl;
					f2<<"\t\t\t\t(BAC ?prevXleft ?finalXleft) (BAC ?prevXright ?finalXright)"<<endl;
					f2<<"\t\t\t\t(POSITION ?carId ?prevXleft ?prevXright ?yIndex)"<<endl;
					f2<<"\t\t\t\t(EMPTY ?finalXleft ?yIndex)"<<endl;
			f2<<"\t\t)"<<endl;

			f2<<"\t\t:effect"<<endl;
				f2<<"\t\t\t(and"<<endl;
					f2<<"\t\t\t\t(not(POSITION ?carId ?prevXleft ?prevXright ?yIndex))"<<endl;
					f2<<"\t\t\t\t(not(EMPTY ?finalXleft ?yIndex))"<<endl;
					f2<<"\t\t\t\t(POSITION ?carId ?finalXleft ?finalXright ?yIndex)"<<endl;
					f2<<"\t\t\t\t(EMPTY ?prevXright ?yIndex)"<<endl;
					f2<<"\t\t\t\t(not (SMPL ?carId)) (not (PREV ?carIdMark)) (PREV ?carId) (SMPL ?carIdMark)"<<endl;
					f2<<"\t\t\t\t(increase (total-cost) 2)"<<endl;
			f2<<"\t\t)"<<endl;
		f2<<"\t)"<<endl; // action ends



				//action starts
		f2<<"\t(:action rightMove"<<endl;
			f2<<"\t\t:parameters ( "<<endl;
				f2<<"\t\t\t?carId ";
				f2<<"?carIdMark ";
				f2<<"?prevXleft ";
				f2<<"?prevXright ";
				f2<<"?yIndex ";
				f2<<"?finalXleft ";
				f2<<"?finalXright ";
			f2<<")"<<endl;

			f2<<"\t\t:precondition"<<endl;
				f2<<"\t\t\t(and"<<endl;
					f2<<"\t\t\t\t(CAR ?carId) (CAR ?carIdMark) (SMPL ?carId) (PREV ?carIdMark)"<<endl;
					f2<<"\t\t\t\t(HOR ?carId)"<<endl;
					f2<<"\t\t\t\t(COLX ?prevXleft) (COLX ?prevXright)"<<endl;
					f2<<"\t\t\t\t(ROWY ?yIndex)"<<endl;
					f2<<"\t\t\t\t(COLX ?finalXleft) (COLX ?finalXright)"<<endl;
					f2<<"\t\t\t\t(FOR ?prevXleft ?finalXleft) (FOR ?prevXright ?finalXright)"<<endl;
					f2<<"\t\t\t\t(POSITION ?carId ?prevXleft ?prevXright ?yIndex)"<<endl;
					f2<<"\t\t\t\t(EMPTY ?finalXRight ?yIndex)"<<endl;
			f2<<"\t\t)"<<endl;

			f2<<"\t\t:effect"<<endl;
				f2<<"\t\t\t(and"<<endl;
					f2<<"\t\t\t\t(not(POSITION ?carId ?prevXleft ?prevXright ?yIndex))"<<endl;
					f2<<"\t\t\t\t(not(EMPTY ?finalXright ?yIndex))"<<endl;
					f2<<"\t\t\t\t(POSITION ?carId ?finalXleft ?finalXright ?yIndex)"<<endl;
					f2<<"\t\t\t\t(EMPTY ?prevXleft ?yIndex)"<<endl;
					f2<<"\t\t\t\t(not (SMPL ?carId)) (not (PREV ?carIdMark)) (PREV ?carId) (SMPL ?carIdMark)"<<endl;
					f2<<"\t\t\t\t(increase (total-cost) 2)"<<endl;
			f2<<"\t\t)"<<endl;
		f2<<"\t)"<<endl; // action ends


		//action starts
		f2<<"\t(:action upMove"<<endl;
			f2<<"\t\t:parameters ( "<<endl;
				f2<<"\t\t\t?carId ";
				f2<<"?carIdMark ";
				f2<<"?prevYtop";
				f2<<"?prevYbottom";
				f2<<"?xIndex";
				f2<<"?finalYtop";
				f2<<"?finalYbottom";
			f2<<")"<<endl;

			f2<<"\t\t:precondition"<<endl;
				f2<<"\t\t\t(and"<<endl;
					f2<<"\t\t\t\t(CAR ?carId) (CAR ?carIdMark) (SMPL ?carId) (PREV ?carIdMark)"<<endl;
					f2<<"\t\t\t\t(VER ?carId)"<<endl;
					f2<<"\t\t\t\t(ROWY ?prevYtop) (ROWY ?prevYbottom)"<<endl;
					f2<<"\t\t\t\t(COLX ?xIndex)"<<endl;
					f2<<"\t\t\t\t(ROWY ?finalYtop) (ROWY ?finalYbottom)"<<endl;
					f2<<"\t\t\t\t(BAC ?prevYtop ?finalYtop) (BAC ?prevYbottom ?finalYbottom)"<<endl;
					f2<<"\t\t\t\t(POSITION ?carId ?prevYtop ?prevYbottom ?xIndex)"<<endl;
					f2<<"\t\t\t\t(EMPTY ?xIndex ?finalYtop)"<<endl;
			f2<<"\t\t)"<<endl;

			f2<<"\t\t:effect"<<endl;
				f2<<"\t\t\t(and"<<endl;
					f2<<"\t\t\t\t(not(POSITION ?carId ?prevYtop ?prevYbottom ?xIndex))"<<endl;
					f2<<"\t\t\t\t(not(EMPTY ?xIndex ?finalYtop))"<<endl;
					f2<<"\t\t\t\t(POSITION ?carId ?finalYtop ?finalYbottom ?xIndex)"<<endl;
					f2<<"\t\t\t\t(EMPTY ?xIndex ?prevYbottom)"<<endl;
					f2<<"\t\t\t\t(not (SMPL ?carId)) (not (PREV ?carIdMark)) (PREV ?carId) (SMPL ?carIdMark)"<<endl;
					f2<<"\t\t\t\t(increase (total-cost) 2)"<<endl;
			f2<<"\t\t)"<<endl;
		f2<<"\t)"<<endl; // action ends


		//action starts
		f2<<"\t(:action downMove"<<endl;
			f2<<"\t\t:parameters ( "<<endl;
				f2<<"\t\t\t?carId ";
				f2<<"?carIdMark ";
				f2<<"?prevYtop";
				f2<<"?prevYbottom";
				f2<<"?xIndex";
				f2<<"?finalYtop";
				f2<<"?finalYbottom";
			f2<<")"<<endl;

			f2<<"\t\t:precondition"<<endl;
				f2<<"\t\t\t(and"<<endl;
					f2<<"\t\t\t\t(CAR ?carId) (CAR ?carIdMark) (SMPL ?carId) (PREV ?carIdMark)"<<endl;
					f2<<"\t\t\t\t(VER ?carId)"<<endl;
					f2<<"\t\t\t\t(ROWY ?prevYtop) (ROWY ?prevYbottom)"<<endl;
					f2<<"\t\t\t\t(COLX ?xIndex)"<<endl;
					f2<<"\t\t\t\t(ROWY ?finalYtop) (ROWY ?finalYbottom)"<<endl;
					f2<<"\t\t\t\t(FOR ?prevYbottom ?finalYbottom) (FOR ?prevYtop ?finalYtop)"<<endl;
					f2<<"\t\t\t\t(POSITION ?carId ?prevYtop ?prevYbottom ?xIndex)"<<endl;
					f2<<"\t\t\t\t(EMPTY ?xIndex ?finalYbottom)"<<endl;
			f2<<"\t\t)"<<endl;

			f2<<"\t\t:effect"<<endl;
				f2<<"\t\t\t(and"<<endl;
					f2<<"\t\t\t\t(not(POSITION ?carId ?prevYtop ?prevYbottom ?xIndex))"<<endl;
					f2<<"\t\t\t\t(not(EMPTY ?xIndex ?finalYbottom))"<<endl;
					f2<<"\t\t\t\t(POSITION ?carId ?finalYtop ?finalYbottom ?xIndex)"<<endl;
					f2<<"\t\t\t\t(EMPTY ?xIndex ?prevYtop)"<<endl;
					f2<<"\t\t\t\t(not (SMPL ?carId)) (not (PREV ?carIdMark)) (PREV ?carId) (SMPL ?carIdMark)"<<endl;
					f2<<"\t\t\t\t(increase (total-cost) 2)"<<endl;
			f2<<"\t\t)"<<endl;
		f2<<"\t)"<<endl; // action ends




	f2<<")"<<endl;
	f2.close();


	return 0;
}