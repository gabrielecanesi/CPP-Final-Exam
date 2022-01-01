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

    // Slot custom per ricevere i dati con cui effettuare la ricerca nel testo
    void on_searchRequest(const QString& query, bool matchCase);


    void on_textEditor_textChanged();

private:
    FindDialog *findDialog;
    QString openFileName;
    QString query;
    bool matchCase;
    long textLength;
    Ui::MainWindow *ui;
    void searchReset();
    void searchStart();
};
#endif // MAINWINDOW_H
