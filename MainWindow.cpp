#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QPushButton>
#include <QString>
#include <QByteArray>
#include <QImage>
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QImageReader>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  if (!QImageReader::supportedImageFormats().contains("png")) {
    QMessageBox::critical(
        this, tr("Exiting..."),
        tr("Cannot find PNG support, sorry!"),
        QMessageBox::NoButton);
    exit(EXIT_FAILURE);
  }
  setupImages();
  setupAbout();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::setupImages() {
  QLayout *settingsLayout = ui->tab_settings->layout();
  for(int i = totImages; i > 0; --i) {
    QGraphicsView *big, *small;
    QPushButton *pushMe;

    big = new QGraphicsView(this);
    small = new QGraphicsView(this);
    pushMe = new QPushButton("Set Image #", this);

    connect (pushMe, &QPushButton::clicked, [=]() {
      onSetImagePushed(big, small);
    });

    ui->tabWidget->insertTab(-1, big, QString("Image #"));
    settingsLayout->addWidget(small);
    settingsLayout->addWidget(pushMe);
  }
}

void MainWindow::setupAbout() {
  const char *text =
      "Copyright © 2015 Giuseppe Roberti. All rights reserved.\n"
      "This work is licensed under GPL license.\n"
      "If you have not received a copy of license with the program,\n"
      "please write me to "
      "g.roberti\x40silenti.net\n";

  ui->tabWidget->addTab(new QLabel(tr(text)), "About");
}

void MainWindow::onSetImagePushed(QGraphicsView *big, QGraphicsView *small) {
  if (big == nullptr) return;
  if (small == nullptr) return;

  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
                                                  tr("PNG (*.png)"));
  if (fileName == nullptr) return;
  qDebug() <<
"================================================================================";
  qDebug() << "Filename:" << fileName;

  QByteArray imageFormat = QImageReader::imageFormat(fileName);
  qDebug() << "Image Format:" << imageFormat;
  qDebug() << "Is Format Supported ?:"
           << QImageReader::supportedImageFormats().contains(imageFormat);

  QImageReader imageReader(fileName);
  if (!imageReader.canRead()) {
    QMessageBox::critical(this, "Error!", "Cannot read image, sorry!\n",
                          QMessageBox::Button::Ok, QMessageBox::Button::No);
    return;
  }

  QImage image = imageReader.read();
  QGraphicsScene *scene = new QGraphicsScene(this);
  QGraphicsPixmapItem *item =
      new QGraphicsPixmapItem(QPixmap::fromImage(image));
  // item->setScale(0.3);
  scene->addItem(item);

  qDebug() << "Current:" << small->size();
  qDebug() << "Scene:" << scene->width() << "x" << scene->height();

  big->setScene(scene);
  small->setScene(scene);

  small->scale(small->width() / (scene->width()),
               small->height() / (scene->height()));
  qDebug() << "Scaled:" << small->width() / (scene->width()) << "x"
           << small->height() / (scene->height());
}
