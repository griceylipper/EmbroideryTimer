#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QFileDialog>
#include <QFile>
#include "stitch.h"

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

void MainWindow::OpenFile()
{
    QString file = QFileDialog::getOpenFileName(this, "Open Embroidery File", "D:/Libraries/Desktop/OneDrive/LHD Embroidery Data", tr("Tajima files (*.dst);;Wilcom files (*.emb)"));
    if (file.isEmpty())
    {
        //Nope
        qDebug("Error - file.IsEmpty()");
        return;
    }

    QFile sFile(file);
    if (!sFile.open(QFile::ReadOnly | QFile::Text))
    {
        //Nope
        qDebug("Error - !sFile.open(QFile::ReadOnly | QFile::Text)");
        return;
    }
    filename = file;

    //Take whole file and put it in a QByteArray
    QByteArray textByteArray = sFile.readAll();

    //Remove header. Should start at 0x200, but needs offset by 0x0C for some reason?
    textByteArray.remove(0, 0x200 - 0x0C);

    //Hex encoding
    //textByteArray = textByteArray.toHex(' ');

    //Set text output to show raw bytes in Hex
    //ui->textBrowser->setText(QString(textByteArray));

    //Make array big enough to hold all stitch data
    Stitch stitches[(textByteArray.size() / 3) + 10];

    for (uint i = 0; i < textByteArray.size(); i += 3)
    {
        stitches[i / 3].SetBytes(textByteArray[i],textByteArray[i + 1], textByteArray[2]);
    }

    for (uint i = 0; i < (textByteArray.size() / 3); i++)
    {
        stitches[i].Calculate();
    }

//    //Not working?
//    int pos = filename.lastIndexOf(QChar('/'));
//    ui->filenameLabel->setText(filename.right(pos));

    QString outputText;

    float totalLength = 0;
    for (uint i = 0; i < (textByteArray.size() / 3); i++)
    {
        totalLength += stitches[i].GetLength();
        QString temp = "Stitch " + QString::number(i + 1) + ": length = " + QString::number(stitches[i].GetLength()) + QString("\n");
        outputText.append(temp);
        if (stitches[i].GetFlags() != 0)
        {
            QString flags = "*****FLAGS******\n";
            outputText.append(flags);
        }
    }

    outputText.insert(0, "Total length = " + QString::number(totalLength) + "mm\n");


    ui->textBrowser->setPlainText(outputText);

    sFile.close();
    return;

}

void MainWindow::on_actionOpen_triggered()
{
    OpenFile();
    return;
}

void MainWindow::on_openButton_clicked()
{
    OpenFile();
    return;
}
