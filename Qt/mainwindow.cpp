#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <iostream>
#include <QTextStream>

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
    ui->editor_testo->resize(this->size());
}


void MainWindow::on_actionApri_triggered(){
    QString file_name = QFileDialog::getOpenFileName(this, "Seleziona un file di testo", "", "File di testo (*.txt) ;; Tutti i file (*.*)");
    QFile text_file(file_name);
    if(text_file.open(QIODevice::ReadOnly | QIODevice::Text)){
        open_file_name = file_name;
        QTextStream input(&text_file);
        ui->editor_testo->setText(input.readAll());
        text_file.close();
        QDialog dialog;
        dialog.show();
        dialog.show();
    }
    else {
        QDialog dialog;
        dialog.show();
    }
}

void MainWindow::on_actionSalva_triggered(){
    QFile file(open_file_name);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out_stream(&file);
    out_stream << ui->editor_testo->toPlainText();
    file.close();
}


void MainWindow::on_actionSalva_con_nome_triggered(){
    QString new_file_name = QFileDialog::getSaveFileName(this, "Scegli dove salvare il File", "", "");
    open_file_name = new_file_name;
    QFile text_file(new_file_name);
    text_file.open(QIODevice::WriteOnly);
    QTextStream out_stream(&text_file);
    out_stream << ui->editor_testo->toPlainText();
    text_file.close();
}

