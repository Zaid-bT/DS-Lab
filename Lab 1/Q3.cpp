#include<iostream>
using namespace std;


class Box{
	int* num;
	
	public:
		Box(int n){
			num = new int(n); // DMA
			cout<<"Default contructor...number= "<<*num<<endl;
		}
		
		Box(const Box& other){
        	num = new int(*other.num); // allocate new memory
        	cout << "Copy Constructor....Nata = " <<*num <<endl;
    	}
    	
    	Box& operator=(const Box& other){
        	cout << "Copy Assignment Operator called." << endl;

        	// avoid self-assignment
        	if(this != &other){
            	delete num; // free old memory
            	num = new int(*other.num); // Allocate and copy
        	}
        	return *this;
    	}
    	
    	void setData(int value){  //setter
        	*num = value;
    	}

    	void display(){  // display data
        	cout << "number: " <<*num<< endl;
    	}
    	
    	~Box(){
    		cout<<"destructor called..."<<endl;
    		delete num;
		}
    	
    	
};


int main(){
    cout << "Creating box1 with value 10" << endl;
    Box box1(10);
    box1.display();

    cout << "\nCreating box2 using copy constructor from box1" << endl;
    Box box2 = box1; // calls copy constructor
    box2.display();

    cout << "\nModifying box2's data to 20" << endl;
    box2.setData(20);

    cout << "\nAfter modification:" << endl;
    cout << "box1: ";
    box1.display(); // Should still be 10 if deep copy works
    cout << "box2: ";
    box2.display(); // Should be 20

    cout << "\nCreating box3 with value 99" << endl;
    Box box3(99);
    cout << "Assigning box1 = box3 using copy assignment" << endl;
    box1 = box3; // Calls copy assignment

    cout << "\nAfter assignment:" << endl;
    cout << "box1: ";
    box1.display(); // Should be 99
    cout << "box3: ";
    box3.display(); // Should be 99

    cout << "\nModifying box3's data to 77" << endl;
    box3.setData(77);

    cout << "\nAfter modification:" << endl;
    cout << "box1: ";
    box1.display(); // Should remain 99
    cout << "box3: ";
    box3.display(); // Should be 77

    return 0;
}

