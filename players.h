#include <string>
#include <vector>
#include <cmath>
// #include <iostream>
using namespace std;

class Player {
public:
  vector<int> balance;
  vector<int> loan;
  string name;

public:
  Player();
  Player(string name);
  Player(string name, int balance);

  string getName();
  int getBalance();
  int getLoan();
  void addBalance(int value);
  void addLoan(int value);
  void interestRate(int value);
  void undo();
  int getHistorySize();
};

