#include "finddialog.h"
#include "ui_finddialog.h"
#include "mainwindow.h"

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);
}

FindDialog::~FindDialog(){
    delete ui;
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
    QString text = ui->lineEdit->text();
    bool res = static_cast<MainWindow*>(parent())->evidenzia_testo(text, ui->checkBox->isChecked());
    if (!res){
        ui->label_non_trovata->setText("<font color='red'>Nessuna occorrenza trovata</font>");
    }
    else {
        ui->label_non_trovata->setText("");
    }
}

