#ifndef GW_W
#define GW_W

#include <QtWidgets>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class GameWindow : public QWidget {
  Q_OBJECT;

public:
  GameWindow(QWidget *parent = nullptr);
  vector<string> getPlayer();

public:
  QListWidget *playerList;
  QLineEdit *nameInput;
  QPushButton *transActionButton, *removeButton;
private slots:
  void addPlayer();
  void removePlayer();
};
#endif
