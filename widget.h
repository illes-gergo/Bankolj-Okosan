#ifndef KAKISKUKI
#define KAKISKUKI

#include "control.h"
#include "game.h"
#include <QtWidgets>

class Window : public QTabWidget {
  Q_OBJECT;

public:
  Window(QWidget *parent = nullptr);

private:
  ControlWindow *cwindow;
  GameWindow *gwindow;
private slots:
  void transferPlayerList();
};

#endif
