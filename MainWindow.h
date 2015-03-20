#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:
  Ui::MainWindow *ui;
  unsigned const int totImages = 6;

  void setupImages();
  void setupReminders();
  void setupAbout();

  void onSetImagePushed(QGraphicsView* big, QGraphicsView* small);
};

#endif // MAINWINDOW_H
