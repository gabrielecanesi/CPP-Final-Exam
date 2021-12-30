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
    void termine_ricerca(bool esito);

private slots:
    void on_actionApri_triggered();

    void on_actionSalva_triggered();

    void on_actionSalva_con_nome_triggered();

    void on_actionCerca_triggered();

    void on_actionNuovo_triggered();

    void on_richiesta_ricerca(const QString& query, bool match_case);

private:
    QString open_file_name;
    Ui::MainWindow *ui;
    FindDialog *search_dialog;
    QFileDialog *file_dialog;
    void reset_ricerca();
};
#endif // MAINWINDOW_H
