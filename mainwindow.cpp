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

    //header skips position to after data header. Not sure why it's offset by 0x0C, but oh well
    int header = 0x200 - 0x0C;
//    for (int i = 0; i < 3; ++i)
//    {
//        //Something not quite working here?
//        //QString valueInHex= QString("%1").arg(char(textByteArray[i + header]), 0, 16);
//        qDebug() << "Byte " << i << " = " << valueInHex;
//    }

    Stitch stitches[(sizeof(textByteArray) / 3 ) + 200];

    for (uint i = 0; i < sizeof(textByteArray); i += 3)
    {
        stitches[i / 3].SetBytes(textByteArray[header + i],textByteArray[header + i + 1], textByteArray[header + i + 2]);
    }

    for (uint i = 0; i < (sizeof(textByteArray) / 3); i++)
    {
        stitches[i].Calculate();
    }



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

    //Not working?
    int pos = filename.lastIndexOf(QChar('/'));
    ui->filenameLabel->setText(filename.right(pos));

    QString outputText;
    for (uint i = 0; i < (sizeof(textByteArray) / 3); i++)
    {
        text.append(QString("Stitch ").append(QString::number(i).append(QString(": length =").append(stitches[i].GetLength()))));
    }

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

//void MainWindow::on_pushButton_2_clicked()
//{
//    OpenFile();
//    return;
//}
