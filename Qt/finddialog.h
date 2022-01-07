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

    /**
     * @brief segnale custom per la ricerca
     * @param query la stringa da cercare
     * @param matchCase true se deve considerare solo il case esatto della query
     */
    void search(const QString& query, bool matchCase);


private slots:

    void on_buttonClose_clicked();

    void on_FindDialog_rejected();

    void on_buttonFind_clicked();

    /**
     * @brief slot custom che esamina l'esito della ricerca
     * @param result true se non sono state trovate occorren
     */
    void on_searchEnd(bool result);




    /**
     * @brief Slot per triggerare l'avvio della ricerca tramite invio nel lineEdit
     */
    void on_searchLine_returnPressed();

private:
    Ui::FindDialog *ui;
    void showEvent(QShowEvent* event);

    /**
     * @brief Gestione della pressione del taso esc per chiudere il dialog
     * @param e l'evento
     */
    void keyPressEvent(QKeyEvent* e);
};

#endif // FINDDIALOG_H
