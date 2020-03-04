
#include "bank.h"
#include <iostream>
#include <string>


using namespace std;

int main(int Argc, char *Argv[]) {
    Bank Bank;
	Bank.processTransactions("BankTransIn.txt");
    cout << "Done" << endl;
    return 0;
}