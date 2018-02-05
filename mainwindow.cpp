#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QFileDialog>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    filename = "";
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
    QString file = QFileDialog::getOpenFileName(this, "Open Embroidery File", "D:/Libraries/Desktop/OneDrive/LHD Embroidery Data", tr("Wilcom embroidery files (*.emb)"));
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
    filename = file;
    QTextStream in(&sFile);
    QString text = in.readAll();

    int pos = filename.lastIndexOf(QChar('/'));
    ui->filenameLabel->setText(filename.right(pos));
    ui->textBrowser->setPlainText(text);

    sFile.close();
}
