#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "finddialog.h"
#include <QFileDialog>
#include <iostream>
#include <QTextStream>
#include "finddialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      search_dialog(new FindDialog(this))
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete search_dialog;
}



void MainWindow::on_actionApri_triggered(){
    QString file_name = QFileDialog::getOpenFileName(this, "Seleziona un file di testo", "", "File di testo (*.txt) ;; Tutti i file (*.*)");
    if (file_name != ""){
        QFile text_file(file_name);
        if(text_file.open(QIODevice::ReadOnly | QIODevice::Text)){
            open_file_name = file_name;
            QTextStream input(&text_file);
            ui->editor_testo->setText(input.readAll());
            text_file.close();
        }
    }
}

void MainWindow::on_actionSalva_triggered(){
    if(open_file_name == ""){
        on_actionSalva_con_nome_triggered();
    }
    else {
        QFile file(open_file_name);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out_stream(&file);
        out_stream << ui->editor_testo->toPlainText();
        file.close();
    }

}


void MainWindow::on_actionSalva_con_nome_triggered(){
    QString new_file_name = QFileDialog::getSaveFileName(this, "Scegli dove salvare il File", "", "");
    if (new_file_name != ""){
        open_file_name = new_file_name;
        QFile text_file(new_file_name);
        if (text_file.open(QIODevice::WriteOnly)){
            QTextStream out_stream(&text_file);
            out_stream << ui->editor_testo->toPlainText();
            text_file.close();
        }
    }
}


void MainWindow::on_actionCerca_triggered(){
    this->search_dialog->show();
}


void MainWindow::on_actionNuovo_triggered(){
    this->open_file_name = "";
    this->ui->editor_testo->setText("");
}

bool MainWindow::evidenzia_testo(QString& query, bool match_case){
    QString str;
    if(match_case){
        str = ui->editor_testo->toPlainText();
    }
    else {
        str = ui->editor_testo->toPlainText().toLower();
        query = query.toLower();
    }


    QTextCharFormat format;
    format.setBackground(Qt::transparent);
    QTextCursor cursor(ui->editor_testo->document());
    cursor.setPosition(0, QTextCursor::MoveAnchor);
    cursor.setPosition(str.size(), QTextCursor::KeepAnchor);
    cursor.setCharFormat(format);

    bool found = false;
    format.setBackground(Qt::yellow);
    for(unsigned int i = 0; i < str.size() - query.size() + 1; ++i){
        unsigned int count = 0;
        for (; count < query.size() && str[i + count] == query[count]; ++count){}
        if(count == query.size()){
            cursor.setPosition(i, QTextCursor::MoveAnchor);
            cursor.setPosition(count + i, QTextCursor::KeepAnchor);
            cursor.setCharFormat(format);
            found = true;
        }
    }



    return found;
}
