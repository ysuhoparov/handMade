#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QFrame>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    frame = new QFrame(this);
    frame->setFrameShape(QFrame::Panel);
    frame->resize(800,600);

    nw = new Mynwork();
    nw->initSocket(frame);

}


MainWindow::~MainWindow()
{
    delete ui;
}



