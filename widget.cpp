#include "widget.h"

Window::Window(QWidget *parent) : QTabWidget(parent) {
  cwindow = new ControlWindow();
  gwindow = new GameWindow();
  this->addTab(gwindow, "Játékosok megadása");
  this->addTab(cwindow, "Bankolás");
  this->resize(800, 600);
  connect(gwindow->removeButton, SIGNAL(clicked()), this,
          SLOT(transferPlayerList()));
  connect(gwindow->transActionButton, SIGNAL(clicked()), this,
          SLOT(transferPlayerList()));
  connect(gwindow->nameInput, SIGNAL(returnPressed()), this,
          SLOT(transferPlayerList()));
  setWindowTitle("Bankolj okosan!");
}

void Window::transferPlayerList() {
  vector<string> playerList = this->gwindow->getPlayer();
  cwindow->fillPlayers(playerList);
}
