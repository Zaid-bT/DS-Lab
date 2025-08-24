#include <iostream>
#include <cstring>
using namespace std;

class Exam{
    char* stdName;
    char* date;
    float score;

public:
    // constructor
    Exam(const char* name, const char* examdate, float s){
        stdName = new char[strlen(name)];
        strcpy(stdName, name);
        date = new char[strlen(date)];
        strcpy(date, examdate);
        score = s;
    }

    //for displaying
    void display(){
        cout<<"Name: "<<stdName<<", Date: "<<date<<", Score: "<<score<<endl;
    }

    //data change
    void setName(const char* name){
        strcpy(stdName, name); // overwrite existing memory
    }

    //destructor
    ~Exam(){
        delete[] stdName;
        delete[] date;
    }
};

int main(){
    Exam exam1("Zaid", "2025-08-24", 55);
    Exam exam2 = exam1;  //shallow copy

    exam1.display();
    exam2.display();

    exam2.setName("Ayaan"); 

    cout<<"\nAfter changing exam2's name:"<<endl;
    exam1.display();  
    exam2.display();

    // At program end: both exam1 and exam2 try to delete the same memory!
     cout<<"\nBoth exam objects show name as Ayaan...as overwriting one name also changes the other one...due to shallow copy"<<endl;

    return 0;
}

