#include "account.h"
#include <iostream>

//Create Account
Account::Account(string Name, int AccountNum) : AccountNum{ AccountNum }, Name{ Name } {
	Balances.resize(10);
	History.resize(10);
}

//Delete Account
Account::~Account() {}

//Add certain amount to the fund
//return true when transaction completed
bool Account::deposit(int Amount, int FundType){
	Balances[FundType] += Amount;
	addToHistory("D", FundType, Amount, true, "");
	return true;
}

//Substract certain amount to the fund
//Return true when withdraw completed, false when error occur
bool Account::withdraw(int Amount, int FundType){
	int AmountNeeded = amountNeeded(Amount, FundType); 
	if (AmountNeeded == 0) {
		Balances[FundType] -= Amount;
		addToHistory("W", FundType, Amount,true,"");
		return true; //end
	}
	if (FundType == 0 && Balances[1] > AmountNeeded) {
		if (transferWithdraw(AmountNeeded, 1, to_string(AccountNum) + "1")) {
			deposit(AmountNeeded, 0);
			return withdraw(Amount, FundType);
		}
	}
	else if (FundType == 2 && Balances[3] > AmountNeeded) {
		if (transferWithdraw(AmountNeeded, 3, to_string(AccountNum) + "2")) {
			deposit(AmountNeeded, 2);
			return withdraw(Amount, FundType);
		}
	}
	else if (FundType == 3 && Balances[2] > AmountNeeded) {
		if (transferWithdraw(AmountNeeded, 2, to_string(AccountNum) + "3")) {
			deposit(AmountNeeded, 3);
			return withdraw(Amount, FundType);
		}
	}
	addToHistory("W", FundType, Amount, false, "");
	return false;
}

//Substract certain amount to the fund to transfer to other fund
//Return true when withdraw completed, false when error occur
bool Account::transferWithdraw(int Amount, int FundType, string other) {
	if (amountNeeded(Amount, FundType) == 0) {
		Balances[FundType] -= Amount;
		addToHistory("T", FundType, Amount, true, other);
		return true; //end
	}
	addToHistory("T", FundType, Amount, false, other);
	return false;
}

//Return extra amount needed to widtdraw certain amount   
//Return zero when no extra amount is needed when withdrawing
int Account::amountNeeded(int Amount, int FundType){
	int AmountNeeded = Amount - Balances[FundType];
	if (AmountNeeded > 0)
		return AmountNeeded;
	return 0;
}

//Return unique number of this account
int Account::accountNum() const{
	return AccountNum;
}

//Add a transaction history to the private vector history as string
void Account::addToHistory(string Transaction, int FundType, int Amount, bool Succeed = true, string other = "")
{
	string HistoryLine = Transaction + " " + to_string(AccountNum) + to_string(FundType) + " " + to_string(Amount);
	if (other != "")
		HistoryLine += " " + other;
	if (!Succeed)
		HistoryLine += " (Failed)";
	History[FundType].push_back(HistoryLine);
}

//Return string that shows transaction history of all ten funds
string Account::wholeFundHistory() {
	string FundHistory = "Displaying Transaction History for " + Name + " by fund.\n";
	for (int I = 0; I < 10; I++) {
		FundHistory += fundName[I] + ": $" + to_string(Balances[I]) + "\n";
		for(int J = 0; J < History[I].size(); J++)
			FundHistory += "	" + History[I][J] + "\n";
	}
	return FundHistory;
}

//Return string that shows history transaction of a specific fund
string Account::fundHistory(int FundType) {
	string FundHistory = "Displaying Transaction History for " + Name + "'s "
		+ fundName[FundType] + ": $" + to_string(Balances[FundType]) + "\n";
	for (int I = 0; I < History[FundType].size(); I++)
			FundHistory += "	" + History[FundType][I] + "\n";
	
	return FundHistory;
}

//Return string that show the total balance of every funds
string Account::fundTotal() {
	string FundTotal = "\n" +Name + " Account ID: " + to_string(AccountNum) + "\n";
	for (int I = 0; I < 10; I++) 
		FundTotal += "	" + fundName[I] +": $" + to_string(Balances[I]) + "\n";
	return FundTotal;
}
