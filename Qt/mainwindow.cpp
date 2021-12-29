#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


// Questo serve a mantenere il campo di testo della stessa dimensione della finestra
void MainWindow::resizeEvent(QResizeEvent*){
    ui->textEdit->resize(this->size());
}
