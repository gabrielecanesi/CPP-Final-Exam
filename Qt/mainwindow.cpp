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
      search_dialog(new FindDialog(this)),
      file_dialog(new QFileDialog())
{
    ui->setupUi(this);
    this->setWindowTitle("Documento senza nome - Editor Bello");
    connect(search_dialog, SIGNAL(ricerca(QString,bool)), this, SLOT(on_richiesta_ricerca(QString,bool)));
    connect(this, SIGNAL(termine_ricerca(bool)), search_dialog, SLOT(on_termine_ricerca(bool)));
}


MainWindow::~MainWindow()
{
    delete ui;
    delete search_dialog;
}


void MainWindow::on_richiesta_ricerca(const QString& query, bool match_case){
    QString str;
    QString query_temp = query;
    if(match_case){
        str = ui->editor_testo->toPlainText();
    }
    else {
        str = ui->editor_testo->toPlainText().toLower();
        query_temp = query.toLower();
    }

    reset_ricerca();
    QTextCharFormat format;
    QTextCursor cursor(ui->editor_testo->document());
    bool found = false;
    format.setBackground(Qt::yellow);
    format.setForeground(Qt::black);
    for(int i = 0; i < str.size() - query.size() + 1; ++i){
        int count = 0;
        for (; count < query_temp.size() && str[i + count] == query_temp[count]; ++count){}
        if(count == query_temp.size()){
            cursor.setPosition(i, QTextCursor::MoveAnchor);
            cursor.setPosition(count + i, QTextCursor::KeepAnchor);
            cursor.setCharFormat(format);
            found = true;
        }
    }
    emit termine_ricerca(found);

}


void MainWindow::on_actionApri_triggered(){
    reset_ricerca();
    QString file_name = file_dialog->getOpenFileName(this, "Seleziona un file di testo", "", "File di testo (*.txt) ;; Tutti i file (*.*)");
    if (file_name != ""){
        QFile text_file(file_name);
        if(text_file.open(QIODevice::ReadOnly | QIODevice::Text)){
            open_file_name = file_name;
            QTextStream input(&text_file);
            ui->editor_testo->setPlainText(input.readAll());
            text_file.close();
            this->setWindowTitle(open_file_name + " - Editor Bello");
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
    QString new_file_name = file_dialog->getSaveFileName(this, "Scegli dove salvare il File", "", "File di testo (*.txt) ;; Tutti i file (*.*)");
    if (new_file_name != ""){
        QFile text_file(new_file_name);
        if (text_file.open(QIODevice::WriteOnly)){
            open_file_name = new_file_name;
            QTextStream out_stream(&text_file);
            out_stream << ui->editor_testo->toPlainText();
            text_file.close();
            this->setWindowTitle(new_file_name + " - Editor Bello");
        }
    }
}


void MainWindow::on_actionCerca_triggered(){
    this->search_dialog->show();
}

void MainWindow::reset_ricerca(){
    QTextCharFormat format;
    format.setBackground(Qt::transparent);
    QTextCursor cursor(ui->editor_testo->document());
    cursor.setPosition(0, QTextCursor::MoveAnchor);
    cursor.setPosition(ui->editor_testo->toPlainText().size(), QTextCursor::KeepAnchor);
    cursor.setCharFormat(format);

}

void MainWindow::on_actionNuovo_triggered(){
    reset_ricerca();
    this->open_file_name = "";
    this->ui->editor_testo->setPlainText("");
    this->setWindowTitle("Documento senza nome - Editor Bello");
}

