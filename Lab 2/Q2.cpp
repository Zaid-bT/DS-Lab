#include<iostream>
using namespace std;

int main(){
	int subsum;
	int totalmarks[5];
	float avgmarks[4];
	int topstudent;
	int **arr = new int*[5];
	for(int i=0;i<5;i++){
		arr[i] = new int[4];
	}
	
	for(int i=0;i<5;i++){
		for(int j=0;j<4;j++){
			cout<<"Enter student "<<i+1<<" subject "<<j+1<<" marks : ";
			cin>>arr[i][j];
			totalmarks[i] +=arr[i][j];
		}cout<<endl;
	}
	
	for(int j=0;j<4;j++){
		subsum=0;
		for(int i=0;i<5;i++){
			subsum += arr[i][j];
		}avgmarks[j] =subsum/4;
	}
	
	topstudent = totalmarks[0];
	for(int i=0;i<5;i++){
		
		if(totalmarks[i]>topstudent){
			topstudent = i;
			
		}
	}
	
	for(int i = 0;i<5;i++){
		cout<<"Total Marks of Student "<<i+1<<" : "<<totalmarks[i]<<endl;
	}cout<<"Student "<<topstudent<<" got highest marks "<<endl;
	
	for(int i = 0;i<4;i++){
		cout<<"Average Marks of Subject "<<i+1<<" : "<<avgmarks[i]<<endl;
	}
	
	
	
	return 0;
}