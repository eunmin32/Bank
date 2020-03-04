
#include "bank.h"
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

//Create Bank
Bank::Bank() : OpenedAccout{ nullptr } {};

//Delete Bank
Bank::~Bank() {}

//Process transaction in file and print out output 
void Bank::processTransactions(const string &FileName) {
	cout << "Transaction Processed" << endl;
	convertTxtToTransaction(FileName);
	processQueue();
	displayAllBalances();
}

//Display Error occurred while transaction and all account balance
void Bank::displayAllBalances() const {
	for (int I = 0; I < Error.size(); I++)
		cout << Error[I] << endl;
	Accounts.display();
}

//Read all transaction stored and process the transaction 
void Bank::processQueue(){
	string Action;
	int FundType;
	Transaction Transaction;
	while (!Transactions.empty()) {
		Transaction = Transactions.front();
		Action = Transaction.Action;
		FundType = Transaction.Account1 % 10;
		if (Action == "O") {
			if (!Accounts.retrieve(Transaction.Account1, OpenedAccout)) {
				OpenedAccout = new Account(Transaction.Name, Transaction.Account1); 
				Accounts.insert(OpenedAccout);
			} else {
				Error.push_back("ERROR: Account " + to_string(Transaction.Account1) +" is already open.Transaction refused.");
			}
		} else if (Action == "T") { 
			if (OpenedAccout->transferWithdraw(Transaction.Amount,
				FundType, to_string(Transaction.Account2))) {
				if (Transaction.Account1 / 10 != Transaction.Account2 / 10) {
					if (!Accounts.retrieve(Transaction.Account2, OpenedAccout)) {
						Error.push_back("ERROR: Could not find Account "
							+ to_string(Transaction.Account2) + " Transfer cancelled.");
						Accounts.retrieve(Transaction.Account1, OpenedAccout);
					} else {
						OpenedAccout->deposit(Transaction.Amount, Transaction.Account2 % 10);
						Accounts.retrieve(Transaction.Account1, OpenedAccout);
					}
				} else {
					OpenedAccout->deposit(Transaction.Amount, Transaction.Account2 % 10);
				}
				
			}
			
		} else if (Action == "D") {
			OpenedAccout->deposit(Transaction.Amount, FundType);
		} else if (Action == "W") { 
			OpenedAccout->withdraw(Transaction.Amount, FundType);
		} else if (Action == "H") { 
			if (Transactions.front().Account1 / 1000 < 10) { //4 digit		
				cout << OpenedAccout->wholeFundHistory();
			}
			else { //5 digit
				cout << OpenedAccout->fundHistory(FundType);
			}	
		} else {
		}
		Transactions.pop();
	}
}

//convert file to transactions and store the transaction to the vector, Transactions
void Bank::convertTxtToTransaction(const string& FileName) {
	ifstream inFile(FileName);
	string Line;
	if (inFile.is_open()) {
		while (getline(inFile, Line)) {
			Transactions.push(convertStringToTransaction(Line));
		}
	}
}

//convert a line of string to the Transaction struct
Bank::Transaction Bank::convertStringToTransaction(string Line) {
	stringstream S;
	Transaction Transaction;
	S.str(Line);
	S >> Transaction.Action;
	if (Transaction.Action == "O") {
		string FirstName;
		string LastName;
		S >> FirstName;
		S >> LastName;
		Transaction.Name = FirstName + " " + LastName;
		S >> Transaction.Account1; 
	} if (Transaction.Action == "T") {
		S >> Transaction.Account1;
		S >> Transaction.Amount;
		S >> Transaction.Account2;
	} else {
		S >> Transaction.Account1;
		S >> Transaction.Amount;
	}
	return Transaction;
}
