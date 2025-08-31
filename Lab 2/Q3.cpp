#include<iostream>
using namespace std;

int main(){
	int departments;
	
	cout<<"enter number of departments : ";
	cin>> departments;
	
	int students[departments];
		
	int** arr = new int* [departments]; //double pointer for jagged array
	
	for(int i = 0;i<departments ; i++){
		cout<<"enter number of students in department "<<i+1<<" : ";
		cin>>students[i];
		arr[i] = new int[students[i]];  // allocating each row with different number of students
	}
	cout<<endl;
	for (int i = 0;i<departments ; i++){
		for( int j =0;j<students[i];j++){
			
			cout<<"Enter department "<<i+1<<" student "<<j+1<<" marks : "; // data entry
			cin>>arr[i][j];
			
		}cout<<endl;
	}
	
	
	int highest ,lowest;
	int highPos,lowPos; // position of student in array
	float avg;
	
	for(int i =0; i < departments ; i++){
			
			highest = arr[i][0];
			lowest = arr[i][0];
			avg=0;
			
		for(int j = 0;j<students[i];j++){
			
			if(arr[i][j] > highest){
				highPos = j;
			}
			if (arr[i][j] < lowest){
				lowPos = j;
			}
			avg += arr[i][j];
			cout<< "Department "<<i+1<<" Student "<<j+1<<" marks : "<<arr[i][j]<<endl; // display whole array
		}cout<<endl;
		cout<<"Student "<<highPos+1<<" got highest marks "<<endl; 
		cout<<"Student "<<lowPos+1<<" got lowest marks "<<endl;
		cout<<"Department Average : "<<avg/students[i]<<endl;
		cout<<endl;
	}
}
