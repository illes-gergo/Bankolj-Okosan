#include "players.h"

Player::Player() {
  this->name = "Gipsz Jakab";
  this->balance.push_back(3e6);
  this->loan.push_back(0);
}

Player::Player(string name) {
  this->name = name;
  this->balance.push_back(3e6);
  this->loan.push_back(0);
}

Player::Player(string name, int balance) {
  this->name = name;
  this->balance.push_back(balance);
  this->loan.push_back(0);
}

string Player::getName() { return this->name; }
int Player::getBalance() { return this->balance.back(); }
int Player::getLoan() { return this->loan.back(); }

void Player::addBalance(int value) {
  this->balance.push_back(balance.back() + value);
  this->loan.push_back(loan.back());
}

void Player::addLoan(int value) {
  if (value > 0) {
    this->loan.push_back(loan.back() + value);
    this->balance.push_back(balance.back());
  } else if (value < 0 && -value < loan.back()) {
    this->loan.push_back(loan.back() + value);
    this->balance.push_back(balance.back() + value);
  } else if (value < 0 && -value > loan.back()) {
    this->balance.push_back(balance.back() - this->loan.back());
    this->loan.push_back(0);
  } else {
    return;
  }
}

void Player::interestRate(int value) {
  double tempBalance = static_cast<double>(this->balance.back()) *
                       (1 + static_cast<double>(value) / 100);
  this->balance.push_back(static_cast<int>(round(tempBalance)));
  this->loan.push_back(loan.back());
}

int Player::getHistorySize() { return this->loan.size(); }

void Player::undo() {
  if (balance.size() < 2) {
    return;
  }
  balance.pop_back();
  loan.pop_back();
}
