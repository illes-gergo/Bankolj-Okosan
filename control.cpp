#include "control.h"

ControlWindow::ControlWindow(QWidget *parent) : QWidget(parent) {
  button = new QPushButton("Összeg küldése");
  players = new vector<Player>;
  loanbutton = new QPushButton("Hitel küldése");
  undobutton = new QPushButton("Utolsó művelet visszavonása");
  playerListWidget = new QListWidget();
  historyListWidget = new QListWidget();
  transaction = new QLineEdit();
  loan = new QLineEdit();
  interest = new QLineEdit();
  interestbutton = new QPushButton("Kamat küldése");
  QGridLayout *layout = new QGridLayout();
  QHBoxLayout *bottomlayout = new QHBoxLayout();
  layout->addWidget(transaction);
  layout->addWidget(button);
  layout->addWidget(interest);
  layout->addWidget(interestbutton);
  layout->addWidget(loan);
  layout->addWidget(loanbutton);
  layout->addWidget(undobutton);
  bottomlayout->addWidget(playerListWidget);
  bottomlayout->addWidget(historyListWidget);
  layout->addLayout(bottomlayout, 7, 0);
  connect(playerListWidget, SIGNAL(itemSelectionChanged()), this,
          SLOT(listHighLightedPlayer()));
  connect(button, SIGNAL(clicked()), this, SLOT(pushTransactionValue()));
  connect(transaction, SIGNAL(returnPressed()), this,
          SLOT(pushTransactionValue()));
  connect(interestbutton, SIGNAL(clicked()), this, SLOT(pushInterestRate()));
  connect(interest, SIGNAL(returnPressed()), this, SLOT(pushInterestRate()));
  connect(loanbutton, SIGNAL(clicked()), this, SLOT(pushLoan()));
  connect(loan, SIGNAL(returnPressed()), this, SLOT(pushLoan()));
  connect(undobutton, SIGNAL(clicked()), this, SLOT(undo()));
  setLayout(layout);
}

void ControlWindow::fillPlayers(vector<string> names) {
  this->playerListWidget->clear();
  this->players->clear();
  string msg;
  for (int i = 0; i < static_cast<int>(names.size()); i++) {
    this->players->push_back(Player(names[i]));
    msg = players->at(i).getName() +
          ":\tVagyon: " + to_string(players->at(i).getBalance()) +
          "Ft;\tTartozás: " + to_string(players->at(i).getLoan()) + "Ft";
    this->playerListWidget->addItem(msg.c_str());
  }
}

void ControlWindow::RefreshPlayerListWidget() {
  int size = players->size();
  string msg;
  for (int i = 0; i < size; i++) {
    msg = players->at(i).getName() +
          ":\tVagyon: " + to_string(players->at(i).getBalance()) +
          "Ft;\tTartozás: " + to_string(players->at(i).getLoan()) + "Ft";
    this->playerListWidget->item(i)->setText(msg.c_str());
  }
}

void ControlWindow::listHighLightedPlayer() {
  // cout << "Slot triggered" <<endl;
  this->historyListWidget->clear();
  int index = this->playerListWidget->currentRow();
  Player *currentplayer = &players->at(index);
  int histsize = currentplayer->getHistorySize();
  vector<int> loan;
  vector<int> balance;
  int vecind;
  string msg;
  if (histsize < 2) {
    this->historyListWidget->addItem("Nem volt még pénzmozgás!");
    return;
  }
  for (int i = 0; i < histsize - 1; i++) {
    // this->historyListWidget->addItem("To be implemented!");
    loan = currentplayer->loan;
    balance = currentplayer->balance;
    vecind = histsize - i - 1;
    if (loan.at(vecind) - loan.at(vecind - 1) > 0) {
      msg = "Hitel felvétele " +
            to_string(loan.at(vecind) - loan.at(vecind - 1)) + "Ft értékben";
      this->historyListWidget->addItem(msg.c_str());
    } else if (loan.at(vecind) - loan.at(vecind - 1) < 0 &&
               balance.at(vecind) - balance.at(vecind - 1) < 0) {
      msg = "Hitel törlesztése " +
            to_string(-loan.at(vecind) + loan.at(vecind - 1)) + "Ft értékben";
      this->historyListWidget->addItem(msg.c_str());
    } else if (loan.at(vecind) - loan.at(vecind - 1) == 0 &&
               balance.at(vecind) - balance.at(vecind - 1) < 0) {
      msg = "Kiadás " +
            to_string(-balance.at(vecind) + balance.at(vecind - 1)) +
            "Ft értékben";
      this->historyListWidget->addItem(msg.c_str());
    } else if (loan.at(vecind) - loan.at(vecind - 1) == 0 &&
               balance.at(vecind) - balance.at(vecind - 1) > 0) {
      msg = "Bevétel " +
            to_string(balance.at(vecind) - balance.at(vecind - 1)) +
            "Ft értékben";
      this->historyListWidget->addItem(msg.c_str());
    }
  }
}

void ControlWindow::pushTransactionValue() {
  bool ok;
  // cout << "Slot triggered" << endl;
  int index = this->playerListWidget->currentRow();
  if (static_cast<size_t>(index) > players->size()) {
    return;
  } else {
    Player *selecetdPlayer = &players->at(index);
    int value = this->transaction->text().toInt(&ok);
    if (!ok) {
      return;
    } else {
      selecetdPlayer->addBalance(value);
    }
    RefreshPlayerListWidget();
    listHighLightedPlayer();
  }
  transaction->clear();
}

void ControlWindow::pushInterestRate() {
  bool ok;
  // cout << "Slot triggered" << endl;
  int index = this->playerListWidget->currentRow();
  if (static_cast<size_t>(index) > players->size()) {
    return;
  } else {
    Player *selecetdPlayer = &players->at(index);
    int value = this->interest->text().toInt(&ok);
    if (!ok) {
      return;
    } else {
      selecetdPlayer->interestRate(value);
    }
    RefreshPlayerListWidget();
    listHighLightedPlayer();
  }
  interest->clear();
}

void ControlWindow::pushLoan() {
  bool ok;
  // cout << "Slot triggered" << endl;
  int index = this->playerListWidget->currentRow();
  if (static_cast<size_t>(index) > players->size()) {
    return;
  } else {
    Player *selecetdPlayer = &players->at(index);
    int value = this->loan->text().toInt(&ok);
    if (!ok) {
      return;
    } else {
      selecetdPlayer->addLoan(value);
    }
    RefreshPlayerListWidget();
    listHighLightedPlayer();
  }
  loan->clear();
}

void ControlWindow::undo() {
  int index = this->playerListWidget->currentRow();
  if (static_cast<size_t>(index) > players->size()) {
    cout << "Index catch" << endl;
    cout << index << endl;
    return;
  } else {
    Player *selecetdPlayer = &players->at(index);
    cout << "Running undo" << endl;
    selecetdPlayer->undo();
    RefreshPlayerListWidget();
    listHighLightedPlayer();
  }
}
