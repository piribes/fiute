#include "MainWindow.h"

#include <QApplication>
#include <QGuiApplication>
#include <QSystemTrayIcon>
#include <QScreen>
#include <QDebug>
#include <QImageReader>

#define WIDTH  973
#define HEIGHT 1022
#define TOT_IMAGES 6
#define MAX_ALERTS 12

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  MainWindow w;
  w.show();

  qDebug() << "We have" << a.screens().count() << "screen!";
  qDebug() << "Supported Image Formats:"
           << QImageReader::supportedImageFormats();

  return a.exec();
}
