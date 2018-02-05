#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openButton_Clicked()
{

}

void MainWindow::on_actionOpen_triggered()
{
   QString file = QFileDialog::getOpenFileName(this, "Open a file");
   if (file.isEmpty())
   {
       //Nope
       return;
   }
   QFile sFile(file);
   if (!sFile.open(QFile::ReadOnly | QFile::Text))
   {
       //Nope
       return;
   }
  // QTextStream in(&sFile);
  // QString text = in.readAll();
   sFile.close();
}
