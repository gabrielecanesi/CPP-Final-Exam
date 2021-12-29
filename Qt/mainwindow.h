#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private slots:
    void on_actionApri_triggered();

    void on_actionSalva_triggered();

    void on_actionSalva_con_nome_triggered();

    void on_actionCerca_triggered();

    void on_actionNuovo_triggered();

private:
    QString open_file_name;
    Ui::MainWindow *ui;
    FindDialog *search_dialog;
    friend class FindDialog;
    bool evidenzia_testo(QString& query, bool match_case);
    void reset_ricerca();
};
#endif // MAINWINDOW_H
