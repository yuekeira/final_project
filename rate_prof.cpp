#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int status;
int input;

class Professor {

public:
    string name;
    double Diff_level;
//    string dept;
    double new_Diff_level;
    Professor(string str, double dl) : name(str), Diff_level(dl) {}

    void changeDiff(double new_Diff_level, double student_num) {Diff_level = (Diff_level+new_Diff_level)/student_num;}
};

void check();
void create();
void rate();
void linedel(string line2del);
void linewrite(string name, double Diff);

int main()
{
    string prof_name;
    double Diff_level;
    string dept;
    int student_num = 1;
    double new_Diff_level;

    cout << "what would you like to do" << endl;
    cout << "1 check a professor's rating" << endl;
    cout << "2 rate a professor" <<endl;
    cout << "3 create a professor" <<endl;
    cout << "4 quit the programm" << endl;
    cin >> input;
    if (input == 1)
            check();
    else if (input ==2)
            rate();
    else if (input == 3)
	    create();
    else if (input == 4)
	    exit(0);
	


    return 0;
}


void create()
{
        string name, dept;
        double Diff_level;

        ofstream file("cooper_prof.txt", ios::app);
        cout <<"Please enetr professor last name " << endl;
	cin >> name;
	cout << "Please rate the level of difficulty:"<<endl;
        cin >> Diff_level;
        cout << name << " " << Diff_level << " " << endl;
        file << name << " " << Diff_level<<endl;
        file.close();
        main();
}


void check()
{
	status = 0;
	ifstream file("cooper_prof.txt");
	string name;
	char input;
	string search_name;
	double Diff_level;
	cout << "enter the professor last name"<<endl;
	cin >> search_name;
	while (file >> name >> Diff_level)
	{
		if (search_name == name)
		{
			cout << "professor found" << endl;
			cout << name << " " << Diff_level << endl;
			status = 1;
			
		}
	}

	if(status == 0)
	{
		cout<<"prof not found"<< endl;
		cout<<"Please create a new one" << endl;
	}
			
	
	main();
}

void rate()
{
	status = 0;
	int student_num = 1;
	double new_Diff_level;
	ifstream file("cooper_prof.txt");
	string name, name2rate;
	double Diff_level;
	string line2del;
	stringstream ss;
	cout <<" enter the professor you want to rate"<<endl;
	cin >> name2rate;

	while (file >> name >> Diff_level)
	{
		if (name2rate == name)
		{
			
			Professor newProf(name, Diff_level);
			cout << newProf.name << " " << newProf.Diff_level<< endl;
			ss << newProf.name << " " <<newProf.Diff_level;
			line2del = ss.str();
			linedel(line2del);
			cout << "enter your rating"<< endl;
			cin >> new_Diff_level;
		        newProf.changeDiff(new_Diff_level, student_num);
			cout <<"new rating is: " <<newProf.Diff_level << endl;
			linewrite(newProf.name, newProf.Diff_level);
			status = 1;
		}
	}	
 	
	if (status = 0)
	{
	cout<< "prof not found, plase create new one" << endl;
	}
	main();
}


void linedel(string line2del)
{
    	string line;
	ifstream fin;
    	fin.open("cooper_prof.txt");
   	ofstream temp;
  	temp.open("temp.txt");

    	while (getline(fin,line))
   	{
      		if (line != line2del)
       		{
       			temp << line << endl;
       		}
   	}	

  	temp.close();
   	fin.close();
   	cout << "line deleted"<<endl;
	remove("cooper_prof.txt");
   	rename("temp.txt","cooper_prof.txt");
}

void linewrite(string name, double Diff)
{
	ofstream file("cooper_prof.txt", ios::app);
	file<<name<< " " << Diff<<endl;
	file.close();
}

