#include "accounttree.h"

// Delete all nodes in BST
AccountTree::~AccountTree() { clear(); };

// Insert new account
bool AccountTree::insert(Account* Account) { 
	if (Root == nullptr) { //empty
		Root = new Node(Account);
	} else {
		Node* nodeptr;
		nodeptr = Root;
		Node* nodeptr2;
		while (nodeptr != nullptr) {
			nodeptr2 = nodeptr;
			if (Account->accountNum() == nodeptr->Accountptr->accountNum())
				return false;
			else if (Account->accountNum() > nodeptr->Accountptr->accountNum())
				nodeptr = nodeptr->Right;
			else 
				nodeptr = nodeptr->Left;		
		}
		if (Account->accountNum() > nodeptr2->Accountptr->accountNum())
			nodeptr2->Right = new Node(Account);
		else
			nodeptr2->Left = new Node(Account);
	}
	return true;
}

// Retrieve account
// returns true if successful AND *Account points to account
bool AccountTree::retrieve(const int &AccountNumber, Account *&Account) const {
	Node* nodeptr = Root;
	while (nodeptr != nullptr) {
		if (AccountNumber == nodeptr->Accountptr->accountNum()) {
			Account = nodeptr->Accountptr;
			return true;
		} else if (AccountNumber > nodeptr->Accountptr->accountNum())
			nodeptr = nodeptr->Right;
		else
			nodeptr = nodeptr->Left;
	}
	Account = nullptr;
	return false;
}

// Display information on all accounts
void AccountTree::display() const{
	cout << displayHelper(Root);
}

// delete all information in AccountTree
void AccountTree::clear() {
	clearHelper(Root);
}

// check if tree is empty
bool AccountTree::isEmpty() const {
	if (Root == nullptr)
		return false;
	return true;
}

//Helper recursive function of display function
string AccountTree::displayHelper(Node* Nodeptr) const{
	string currAccount = Nodeptr->Accountptr->fundTotal();
	if (!(Nodeptr->Left == nullptr && Nodeptr->Right == nullptr)) {
		if (Nodeptr->Left != nullptr)
			currAccount += displayHelper(Nodeptr->Left);
		if (Nodeptr->Right != nullptr)
			currAccount += displayHelper(Nodeptr->Right);
	}
	return currAccount;
}

//Helper recursive function of clear function
void AccountTree::clearHelper(Node* Nodeptr){
	if (Nodeptr->Left != nullptr)
			clearHelper(Nodeptr->Left);
	if (Nodeptr->Right != nullptr)
			clearHelper(Nodeptr->Right);
	delete Nodeptr->Accountptr;
	delete Nodeptr;
}
