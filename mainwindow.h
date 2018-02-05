#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
   void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    void on_openButton_Clicked();
    QString filename;

};

#endif // MAINWINDOW_H
