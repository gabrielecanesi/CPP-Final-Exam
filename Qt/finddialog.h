#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

namespace Ui {
class FindDialog;
}

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = nullptr);
    ~FindDialog();


signals:

    // Segnale custom per mattere in comunicazione FindDialog e MainWindow
void search(const QString& query, bool matchCase);


private slots:
    void on_buttonClose_clicked();

    void on_FindDialog_rejected();

    void on_buttonFind_clicked();

    // Slot custom per verificare il risultato della ricerca
    void on_searchEnd(bool result);



    void on_searchLine_returnPressed();

private:
    Ui::FindDialog *ui;
    void showEvent(QShowEvent* event);
    void keyPressEvent(QKeyEvent* e);
};

#endif // FINDDIALOG_H
