/* Question 1
Given a set of integers and a value target, determine if there is a subset whose sum is equal to the target.
Input:
arr = [3, 34, 4, 12, 5, 2], target = 9
Output:
True (because subset [4, 5] or [3, 4, 2] sums to 9)*/


#include<iostream>
using namespace std;

bool checkArrSum(int arr[],int target,int result,int n){ // n = array size
	
	if(result == target){ // base case
		return true;
	}else if(n == 0){ //whole array traversed so false
		return false;
	}
	
	
	
	if(checkArrSum(arr,target,result,n-1)){ // this works when result>target so arr value is excluded
		return true;
	}
	if(checkArrSum(arr,target,result+arr[n-1],n-1)){ // this works when result<target value
		return true;
	}
}


int main(){
	int n;
	cin>>n;
	int arr[n];
	for(int i = 0;i<n;i++){
		cout<<"Enter value: ";
		cin>>arr[i];
	}
	int target;
	cout<<"Target : ";
	cin>> target;
	if(checkArrSum(arr,target,0,n)){
		cout<<" TRUE ";
	}else{
		cout<<" FALSE";
	}
	
}
