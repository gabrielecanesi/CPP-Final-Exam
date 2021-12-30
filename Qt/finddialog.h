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
void ricerca(const QString& query, bool match_case);


private slots:
    void on_button_close_clicked();

    void on_FindDialog_rejected();

    void on_button_find_clicked();

    void on_termine_ricerca(bool esito);


private:
    Ui::FindDialog *ui;
    void showEvent(QShowEvent* event);
};

#endif // FINDDIALOG_H
