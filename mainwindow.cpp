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

void MainWindow::OpenFile()
{
    QString file = QFileDialog::getOpenFileName(this, "Open Embroidery File", "D:/Libraries/Desktop/OneDrive/LHD Embroidery Data", tr("Wilcom files (*.emb);;Tajima files (*.dst)"));
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


    //uncompress file
    QByteArray textByteArray = text.toUtf8();

//    bool foundPadding = false;
//    bool foundCompressedData = false;
//    int firstByte = -1;
//    for (int i = 0; i < 127; i++)
//    {
//        //0x20 is the padding byte
//        //If group of 16 bytes starts with padding
//        if (textByteArray[i * 16] == 0x20)
//        {
//            for (int j = 0; j < 16; j++)
//            {
//                //If next 16 bytes are all padding
//                if (textByteArray[i + j] == 0x20)
//                {
//                    foundPadding = true;
//                    continue;
//                }
//            }
//        }
//        else
//        {
//            //Padding has ended
//            if (foundPadding)
//            {
//                foundCompressedData = true;
//                firstByte = i * 16;
//            }
//        }
//    }

    int firstByte = 0x200;
    qDebug() << "firstByte = " << firstByte;


    qUncompress(choppedByteArray);
    if (choppedByteArray.isEmpty())
    {
        //Nope
        ui->textBrowser->setPlainText("File corrput");
    }

    QString uncompressedText;
    uncompressedText.fromUtf8(choppedByteArray);

    //Not working?
    int pos = filename.lastIndexOf(QChar('/'));
    ui->filenameLabel->setText(filename.right(pos));

    ui->textBrowser->setPlainText(uncompressedText);

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
    //Not working?
    OpenFile();
    return;
}

//void MainWindow::on_pushButton_2_clicked()
//{
//    OpenFile();
//    return;
//}
