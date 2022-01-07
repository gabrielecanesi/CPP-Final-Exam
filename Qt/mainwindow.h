#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "finddialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    // Segnale custom emesso quando viene terminata una ricerca
    void searchEnd(bool result);

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_actionFind_triggered();

    void on_actionNew_triggered();

    /**
     * @brief Slot custom che esegue una ricerca del testo proveniente da un altro segnale.
     * @param query la stringa da cercare
     * @param matchCase true se deve confrontare il case esatto, false altrimenti
     */
    void on_searchRequest(const QString& query, bool matchCase);


    /**
     * @brief handler per il change del test dell'editor
     */
    void on_textEditor_textChanged();

private:
    FindDialog *findDialog; ///< Puntatore alla dialog di ricerca
    Ui::MainWindow *ui;
    QString openFileName; ///< Percorso del file attualmente aperto
    QString query; ///< Query di ricerca corrente
    bool matchCase;

    /**
     * @brief Lunghezza del testo. utile per l'esecuzione della ricerca solo se
     * il testo è stato modificato e non evidenziato.
     */
    long textLength;

    /**
     * @brief searchReset
     */

    /**
     * @brief funzione di appoggio che inizia la ricerca
     */
    void searchReset();

    /**
     * @brief funzione di appoggio che elimina i risultati di ricerca
     */
    void searchStart();
};
#endif // MAINWINDOW_H
