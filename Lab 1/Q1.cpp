#include<iostream>
using namespace std;


class BankAccount{
	float balance;
	
	public:
		BankAccount(){   // default constructor with balance set to zero
			balance = 0.0;	
		}
		
		BankAccount(float setBalance){  // parameterized constructor....can set any balance amount
			balance = setBalance;
		}
		
		BankAccount(const BankAccount& other){  //copy constructor
        	balance = other.balance;
    	}
    	
    	void withdraw(float amount){ //deducting amount from bank balance
    		balance -= amount;
		}
		
		float getBalance(){ //getter for balance
			return balance;
		}

};


int main(){
	
	BankAccount account1;
	cout<<"initial balance of acc1: "<<account1.getBalance()<<endl; //set using default constructor
	
	BankAccount account2(1000.0);
	cout<<"initial balance of acc2: "<<account2.getBalance()<<endl; //set using parametirised constructor
	
	BankAccount account3(account2); //using copy constructor
	cout<<"initial balance of acc3: "<<account3.getBalance()<<endl;
	account3.withdraw(200.0);
	cout<<"balance of acc2 after withdrawl: "<<account2.getBalance()<<endl; 
	cout<<"balance of acc3 after withdrawl: "<<account3.getBalance()<<endl;
	
	return 0;
}
