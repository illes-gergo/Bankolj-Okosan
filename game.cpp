#include "game.h"

GameWindow::GameWindow(QWidget *parent) : QWidget(parent) {
  QGridLayout *layout = new QGridLayout();
  transActionButton = new QPushButton("Játékos hozzáadása");
  removeButton = new QPushButton("Játékos törlése");
  playerList = new QListWidget();
  nameInput = new QLineEdit("Játékos neve");

  layout->addWidget(nameInput);
  layout->addWidget(transActionButton);
  layout->addWidget(removeButton);
  layout->addWidget(playerList);
  setLayout(layout);
  connect(transActionButton, SIGNAL(clicked()), this, SLOT(addPlayer()));
  connect(removeButton, SIGNAL(clicked()), this, SLOT(removePlayer()));
  connect(nameInput, SIGNAL(returnPressed()), this, SLOT(addPlayer()));
  connect(nameInput, SIGNAL(returnPressed()), nameInput, SLOT(clear()));
}

void GameWindow::addPlayer() {
  // std::cout << "Lefutottam" << std::endl;
  playerList->addItem(nameInput->text().toStdString().c_str());
}

vector<string> GameWindow::getPlayer() {
  int count = this->playerList->count();
  vector<string> retval;
  for (int i = 0; i < count; i++) {
    retval.push_back(this->playerList->item(i)->text().toStdString());
  }
  return retval;
}

void GameWindow::removePlayer() {
  delete this->playerList->takeItem(this->playerList->currentRow());
}
