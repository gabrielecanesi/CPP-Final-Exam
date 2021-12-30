#include "finddialog.h"
#include "ui_finddialog.h"
#include "mainwindow.h"

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog){
    ui->setupUi(this);
    ui->lineEdit->setFocusPolicy(Qt::StrongFocus);
}

FindDialog::~FindDialog(){
    delete ui;
}

void FindDialog::on_termine_ricerca(bool esito){
     if (!esito){
        ui->label_non_trovata->setText("<font color='red'>Nessuna occorrenza trovata</font>");
    }
    else {
        ui->label_non_trovata->setText("");
    }
}

void FindDialog::on_button_close_clicked(){
    this->close();
}

// Azzera il testo quando viene chiusa
void FindDialog::on_FindDialog_rejected(){
    ui->lineEdit->setText("");
    ui->label_non_trovata->setText("");
}


void FindDialog::on_button_find_clicked(){
    emit ricerca(ui->lineEdit->text(), ui->checkBox->isChecked());
}

void FindDialog::showEvent(QShowEvent*){
    ui->lineEdit->setFocus();
}
