#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "finddialog.h"
#include <QFileDialog>
#include <iostream>
#include <QTextStream>
#include "finddialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      findDialog(new FindDialog(this)),
      ui(new Ui::MainWindow),
      query(""),
      matchCase(false),
      textLength(0)
{
    ui->setupUi(this);
    this->setWindowTitle("Documento senza nome - Editor Bello");

    // Connect per rispondere alla pressione del tasto "Find"
    connect(findDialog, SIGNAL(search(QString,bool)), this, SLOT(on_searchRequest(QString,bool)));

    // Connect per notificare al FndDialog l'esito della ricerca
    connect(this, SIGNAL(searchEnd(bool)), findDialog, SLOT(on_searchEnd(bool)));
}


MainWindow::~MainWindow()
{
    delete ui;

    // Dealloca i vari dialog allocati
    delete findDialog;

    ui = nullptr;
    findDialog = nullptr;
    // Imposto i dati sulla ricerca ai valori di partenza
    textLength = 0;
    matchCase = false;
}


void MainWindow::searchStart(){
    // Rimuove gli highlights della ricerca precedente
    searchReset();

    // Istanzia gli oggetti che formattano il testo e imposta lo stile
    QTextCharFormat format;
    QTextCursor cursor(ui->textEditor->document());
    // Se matchCase è true, allora filtra solo i match con le stesse maiuscole/minuscole
    QTextDocument::FindFlag flag = matchCase ? QTextDocument::FindCaseSensitively : QTextDocument::FindFlag();
    format.setBackground(Qt::yellow);
    format.setForeground(Qt::black);
    cursor = ui->textEditor->document()->find(query, cursor, flag);

    bool found = false;
    while (!cursor.isNull()) {
        found = true;
        cursor.movePosition(QTextCursor::NextCell, QTextCursor::KeepAnchor);
        cursor.setCharFormat(format);
        cursor = ui->textEditor->document()->find(query, cursor, flag);
    }

    emit searchEnd(found);

}

void MainWindow::on_searchRequest(const QString& query, bool matchCase){
    this->query = query;
    this->matchCase = matchCase;
    searchStart();
}


void MainWindow::on_actionOpen_triggered(){
    // Resetta i risultati di una eventuale ricerca precedente
    searchReset();

    // Apre il fileDialog in modalità apertura
    QString fileName = QFileDialog::getOpenFileName(this, "Seleziona un file di testo", "", "File di testo (*.txt) ;; Tutti i file (*.*)");

    // Se fileName è "", non è stato selezionato nessun file
    if (fileName != ""){

        // Carica il file e sostituisce il nome del file aperto con quello nuovo
        QFile file(fileName);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
            openFileName = fileName;
            QTextStream input(&file);
            ui->textEditor->setPlainText(input.readAll());
            file.close();
            this->setWindowTitle(openFileName + " - Editor Bello");
            textLength = ui->textEditor->toPlainText().length();
        }
    }
}

void MainWindow::on_actionSave_triggered(){
    // Se non è stato caricato nessun file, è da salvare con nome
    if(openFileName == ""){
        on_actionSaveAs_triggered();
    }
    else {
        QFile file(openFileName);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out_stream(&file);
            out_stream << ui->textEditor->toPlainText();
            file.close();
        }
    }
}


void MainWindow::on_actionSaveAs_triggered(){
    // Apre il fileDialog in modalità salva con nome
    QString newFileName = QFileDialog::getSaveFileName(this, "Scegli dove salvare il File", "", "File di testo (*.txt) ;; Tutti i file (*.*)");
    if (newFileName != ""){
        QFile text_file(newFileName);
        if (text_file.open(QIODevice::WriteOnly | QIODevice::Text)){
            openFileName = newFileName;
            QTextStream out_stream(&text_file);
            out_stream << ui->textEditor->toPlainText();
            text_file.close();
            this->setWindowTitle(newFileName + " - Editor Bello");
        }
    }
}


void MainWindow::on_actionFind_triggered(){
    // mostra il FindDialog
    this->findDialog->show();
}

void MainWindow::searchReset(){

    // Resetta gli highlights della ricerca precedente settando
    QTextCharFormat format;
    format.setBackground(Qt::transparent);
    QTextCursor cursor(ui->textEditor->document());
    cursor.setPosition(0, QTextCursor::MoveAnchor);
    cursor.setPosition(ui->textEditor->toPlainText().size(), QTextCursor::KeepAnchor);
    cursor.setCharFormat(format);

}

void MainWindow::on_actionNew_triggered(){
    // Cancella il contenuto del buffer e reimposta il titolo della barra
    searchReset();
    this->openFileName = "";
    this->ui->textEditor->setPlainText("");
    this->setWindowTitle("Documento senza nome - Editor Bello");
}


void MainWindow::on_textEditor_textChanged(){
    if(textLength != ui->textEditor->toPlainText().length()){
        textLength = ui->textEditor->toPlainText().length();
        searchStart();
    }
}

