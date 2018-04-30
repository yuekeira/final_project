#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Professor {

public:
    string name;
    double Diff_level;
    string dept;
    double new_Diff_level;
    Professor(string str, double dl, string dept) : name(str), Diff_level(dl), dept(dept) {}

    void changeDiff(double new_Diff_level, double student_num) {Diff_level = (Diff_level+new_Diff_level)/student_num;}
};

//class MEProfessor : public Professor {
//public:
//    MEProfessor(string str) : Professor(str) {}
//};
//
//class PhysicsProfessor : public Professor {
//public:
//    bool monopoly;
//   PhysicsProfessor(string str) : Professor(str) {}
//};

int main()
{
    string prof_name;
    double Diff_level;
    string dept;
    int student_num = 1;
    double new_Diff_level;
    cout <<"Enter the last name of the professor:" ;
    cin >> prof_name;
    //Professor name(prof_name);
    cout << "Please rate the level of difficulty:";
    cin >> Diff_level;
    cout << "Which department?";
    cin >> dept;
    Professor newProfessor(prof_name,Diff_level,dept);
    cout << newProfessor.name << newProfessor.Diff_level << endl;

    ofstream newfile ("cooper_prof.txt", ios::app);
//    newfile.open("cooper_prof.txt");
    newfile<< newProfessor.name<< " " << newProfessor.Diff_level<< " " << endl;
//    newfile.close();


    student_num++;
    cout << "Enter a new rating:";
    cin >> new_Diff_level;
    newProfessor.changeDiff(new_Diff_level,student_num);
    cout << "new rating is" << newProfessor.Diff_level << endl;
//    ofstream newfile("cooper_prof.txt", ios::app);
//    newfile.open("cooper_prof.txt");
    newfile<<newProfessor.name << " " << newProfessor.Diff_level << " " << endl;
    newfile.close();


    return 0;
}
