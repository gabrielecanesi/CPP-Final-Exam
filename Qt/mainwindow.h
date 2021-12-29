#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    QString open_file_name;
    void resizeEvent(QResizeEvent *event);
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
