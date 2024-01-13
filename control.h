#ifndef NUNI
#define NUNI

#include "players.h"
#include <QtWidgets>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class ControlWindow : public QWidget {
  Q_OBJECT;

public:
  ControlWindow(QWidget *parent = nullptr);
  QListWidget *playerListWidget, *historyListWidget;
  QPushButton *button, *undobutton, *loanbutton, *interestbutton;
  QLineEdit *transaction, *loan, *interest;
  void RefreshPlayerListWidget();

private:
  vector<Player> *players;

public:
  void fillPlayers(vector<string> names);

private slots:
  void listHighLightedPlayer();
  void pushTransactionValue();
  void pushInterestRate();
  void pushLoan();
  void undo();
};

#endif
