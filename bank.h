
#ifndef ASS5_BANK_H
#define ASS5_BANK_H

#include "accounttree.h"
#include <fstream>
#include <string>
#include <queue>

using namespace std;

class Bank {
public:
  //Create Bank
  Bank();

  //Delete Bank
  ~Bank();

  //Process transaction in file and print out output 
  void processTransactions(const string &FileName);

  //Display Error occurred while transaction and all account balance
  void displayAllBalances() const;

private:
	struct Transaction {
		string Name = "";
		int Account1 = 0;
		int Account2 = 0;
		string Action = "";
		int Amount = 0;
	};

	//Data structure stores accounts
	AccountTree Accounts;

	//Pointer that point to currently interacting account
	Account* OpenedAccout;

	//Store Transactions 
	queue<Transaction> Transactions;

	//Store Error occurred during processing queue
	vector<string> Error;

	//Read all transaction stored and process the transaction 
	void processQueue();

	//convert file to transactions and store the transaction to the vector, Transactions
	void convertTxtToTransaction(const string& FileName);

	//convert a line of string to the Transaction struct
	Transaction convertStringToTransaction(string Line);
  
};
#endif // ASS5_BANK_H
