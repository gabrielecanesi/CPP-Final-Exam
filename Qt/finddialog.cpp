#include "finddialog.h"
#include "ui_finddialog.h"
#include "mainwindow.h"

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog){
    ui->setupUi(this);
    ui->searchLine->setFocusPolicy(Qt::StrongFocus);
}

FindDialog::~FindDialog(){
    delete ui;
}

void FindDialog::on_searchEnd(bool esito){
     if (!esito){
        ui->labelNotFound->setText("<font color='red'>Nessuna occorrenza trovata</font>");
    }
    else {
        ui->labelNotFound->setText("");
    }
}

void FindDialog::on_buttonClose_clicked(){
    this->close();
}

// Azzera il testo quando viene chiusa
void FindDialog::on_FindDialog_rejected(){
    ui->searchLine->setText("");
    ui->labelNotFound->setText("");
}


void FindDialog::on_buttonFind_clicked(){
    emit search(ui->searchLine->text(), ui->checkBox->isChecked());
}

void FindDialog::showEvent(QShowEvent*){
    ui->searchLine->setFocus();
}


