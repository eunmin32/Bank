
#ifndef ASS5_ACCOUNT_H
#define ASS5_ACCOUNT_H

#include <string>
#include <vector>
#include <ostream>
using namespace std;

class Account {
public:
	//Create Account
	explicit Account(string Name, int AccountNum);

	//Delete Account
	~Account();

	//Add certain amount to the fund
	//Return true when transaction completed
	bool deposit(int Amount, int FundType);

	//Substract certain amount to the fund
	//Return true when withdraw completed, false when error occur
	bool withdraw(int Amount, int FundType);

	//Substract certain amount to the fund to transfer to other fund
	//Return true when withdraw completed, false when error occur
	bool transferWithdraw(int Amount, int FundType, string other);

	//Return extra amount needed to widtdraw certain amount   
	//Return zero when no extra amount is needed when withdrawing
	int amountNeeded(int Amount, int FundType);

	//Return unique number of this account
	int accountNum() const;

	//Add a transaction history to the private vector history as string
	void addToHistory(string Transaction, int FundType, int Amount, bool Succeed, string other);

	//Return string that shows transaction history of all ten funds
	string wholeFundHistory();

	//Return string that shows history transaction of a specific fund
	string fundHistory(int FundType);

	//Return string that show the total balance of every funds
	string fundTotal();

private:
	//Array store name of the fund
	const string fundName[10]{"Money Market", "Prime Money Market", "Long-Term Bond", "Short-Term Bond",
	"500 Index Fund", "Capital Value Fund", "Growth Equity Fund", "Growth Index Fund", "Value Fund",
	"Value Stock Index"};

	//Vector store the balance of funds
	vector<int> Balances;

	//Vector store the transaction history of each fund
	vector<vector<string>> History;

	//Int store the unique account number
	int AccountNum;

	//String store the name of Account owner
	string Name;
};
#endif // ASS5_ACCOUNT_H
