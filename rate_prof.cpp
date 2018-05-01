#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
using namespace std;

int status;
int input;
string dept_name;

class Professor {

public:
    string name;
    double Diff_level;
    double new_Diff_level;
    int student_num;
    string dept_name;
    Professor(string str, double dl, int student, string dept) : name(str), Diff_level(dl), student_num(student), dept_name(dept) {}

    void changeDiff(double new_Diff_level,int student_num) {Diff_level = (Diff_level*(student_num-1)+new_Diff_level)/student_num;}
    void changenumber(int num) {student_num = num + 1;}
    friend bool operator< (const Professor &lhs, const Professor &rhs);
};

bool operator< (const Professor &lhs, const Professor &rhs)
{
	if (lhs.Diff_level < rhs.Diff_level)
		return true;
	else if (lhs.Diff_level > rhs.Diff_level)
		return false;
	else //compare name
	{
		if(lhs.name < rhs.name)
			return true;
		else if (lhs.name > lhs.name)
			return false;
		else 
			return false;
	}
}


	

void check();
void create();
void rate();
void linedel(string line2del);
void linewrite(string name, double Diff, int student_num, string dept_name);
void low2high();



int main()
{
    cout << "________________________________________" << endl;
    cout << "what would you like to do" << endl;
    cout << "1 check a professor's rating" << endl;
    cout << "2 rate a professor" <<endl;
    cout << "3 create a professor" <<endl;
    cout << "4 dispaly professor from low to high" << endl;
    cout << "5 quit the programm" << endl;
    cout << " "<< endl;
    cin >> input;
    if (input == 1)
            check();
    else if (input ==2)
            rate();
    else if (input == 3)
	    create();
    else if (input == 4)
	    low2high();
    else if (input == 5)
	    exit(0);
    else
	    cout <<"Invalid input, please enter a number from 1 to 5." << endl;
	
    return 0;
}


void create()
{
        string name, dept_name;
        double Diff_level;
	int student_num = 1;
        ofstream file("cooper_prof.txt", ios::app);
        cout <<"Please enetr professor last name " << endl;
	cin >> name;
	cout << "Please enter the department (EE,ME,CE,CHE,FA,ARCH)"<<endl;
	cin >> dept_name;
	cout << "Please rate the level of difficulty: (scale 1 to 5)"<<endl;
        cin >> Diff_level;
        cout << name << " " << dept_name << " " <<Diff_level << " "<< endl;
        file << name << " " << dept_name<< " " << Diff_level<< " " << student_num << endl;
        file.close();
        main();
}


void check()
{
	status = 0;
	ifstream file("cooper_prof.txt");
	string name, search_name;
	int student_num;
	char input;
	double Diff_level;
	cout << "enter the professor's last name"<<endl;
	cin >> search_name;
	while (file >> name >> dept_name >>Diff_level>> student_num)
	{
		if (search_name == name)
		{
		cout << "professor found" << endl;
		cout << name << " " << Diff_level << " || Rated by " << student_num << " students."<<endl;
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
	double new_Diff_level;
	double Diff_level;
	int student_num;
	string name, name2rate;
	string line2del;
	stringstream ss;


	ifstream file("cooper_prof.txt");
	cout <<" enter the professor you want to rate"<<endl;
	cin >> name2rate;

	while	 (file >> name >> dept_name >> Diff_level >> student_num)
	{
		if (name2rate == name)
		{
			
			Professor newProf(name, Diff_level, student_num,dept_name);
			cout << newProf.name << " " << newProf.Diff_level<< endl;
			ss << newProf.name << " " << newProf.dept_name<< " " <<newProf.Diff_level<< " " <<newProf.student_num;
			line2del = ss.str();
			linedel(line2del);
			cout << "enter your rating"<< endl;
			cin >> new_Diff_level;
			newProf.changenumber(newProf.student_num);
		        newProf.changeDiff(new_Diff_level, newProf.student_num);
			cout <<"new rating is: " <<newProf.Diff_level << endl;
			linewrite(newProf.name, newProf.Diff_level, newProf.student_num, newProf.dept_name);
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

void linewrite(string name, double Diff, int student_num, string dept_name)
{
	ofstream file("cooper_prof.txt", ios::app);
	file<<name<< " " << dept_name<<" "<< Diff<< " " << student_num<< endl;
	file.close();
}


void low2high()
{
	string name;
	double Diff_level;
	int student_num;
	string dept;

	cout<< "whcih department would you like to see?"<<endl;
	cout<< "enter ALL for all department" <<endl; 
	cin >> dept;

	set<Professor> ProfSet;
	
	ifstream file;
	file.open("cooper_prof.txt");
	if (dept == "All")
	{
		while(file >> name >> dept_name >> Diff_level >> student_num)
		{
			Professor inset(name, Diff_level, student_num, dept_name);
			ProfSet.insert(inset);
		}

		for (auto it=ProfSet.begin(); it!=ProfSet.end(); ++it)
		{
			cout<<it->name << " " <<it->Diff_level <<endl;
		}
	}
	else
	{
		while(file >> name >> dept_name >> Diff_level >> student_num)
		{
			if(dept == dept_name)
			{
				Professor inset(name, Diff_level, student_num, dept_name);
				ProfSet.insert(inset);
			}
		}
		for (auto it=ProfSet.begin(); it!=ProfSet.end(); ++it)
		{
			cout << it->name <<" " <<it->dept_name<< " " <<it -> Diff_level <<endl;
		}
	}
	main();
}

