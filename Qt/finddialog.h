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

private slots:
    void on_button_close_clicked();

    void on_FindDialog_rejected();

    void on_button_find_clicked();

private:
    Ui::FindDialog *ui;
};

#endif // FINDDIALOG_H
