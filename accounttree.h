
#ifndef ASS5_ACCOUNTTREE_H
#define ASS5_ACCOUNTTREE_H

#include "account.h"
#include <iostream>

class AccountTree {
public:
  // Create BST
	AccountTree() : Root{ nullptr } {};

  // Delete all nodes in BST
  ~AccountTree();

  // Insert new account
  bool insert(Account *Account);

  // Retrieve account
  // returns true if successful AND *Account points to account
  bool retrieve(const int &AccountNumber, Account *&Account) const;

  // Display information on all accounts
  void display() const;

  // delete all information in AccountTree
  void clear();

  // check if tree is empty
  bool isEmpty() const;

private:
  class Node {
  public:
    explicit Node(Account* Accountptr = nullptr)
        : Accountptr{Accountptr}, Right{nullptr}, Left{nullptr} {};
    Account* Accountptr;
    Node* Right;
    Node* Left;
  };
  Node* Root;
  
  //Helper recursive function of display function
  string displayHelper(Node* Nodeptr) const;

  //Helper recursive function of clear function
  void clearHelper(Node* Nodeptr);
};
#endif // ASS5_ACCOUNTTREE_H
