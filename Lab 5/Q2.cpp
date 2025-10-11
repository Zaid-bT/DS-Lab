/*Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
Input:
n = 3
Output:
["((()))","(()())","(())()","()(())","()()()"]
Explanation:
Use backtracking to add '(' and ')' recursively, while ensuring the count of '(' is always = count of ')'*/


#include<iostream>
using namespace std;

void Paranthesis(char str[],int i,int openB,int closeB, int n){
	if(closeB == n ){ //base case
		str[i] = '\0';
		cout<<str<<endl;
		return;
	}
	
	if(openB < n){ //runs until recahes array limit
		str[i] = '(';
		Paranthesis(str,i+1,openB+1,closeB,n);
	}
	if(closeB < openB){//runs until close brackets are equal to open bracketss
		str[i] = ')';
		Paranthesis(str,i+1,openB,closeB+1,n);
	}
}

int main(){
	int n;
	cin>>n;
	char str[2*n+1]; //holds both open/close bracket with null terminator at end
	
	Paranthesis(str,0,0,0,n);
	return 0;
}
