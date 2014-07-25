#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QList>
#include <QPainter>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Minecraft painting generator");

    mapSize = 512;
    QImage base(":/new/image/base");

    for(int i=0; i<7; i++)
    {
        ImageBox * box = new ImageBox(0,i,1,1);
        box->setImage(base.copy(i*16,0,16,16));
        ui->mainLayout->addWidget(box, box->getRow(), box->getCol(), box->gety(), box->getx());
        imgBoxList.append(box);
    }

    for (int i=0; i<5; i++)
    {
        ImageBox * box = new ImageBox(2,i*2,1,2);
        box->setImage(base.copy(i*32,32,32,16));
        ui->mainLayout->addWidget(box, box->getRow(), box->getCol(), box->gety(), box->getx());
        imgBoxList.append(box);
    }

    for (int i=0; i<2; i++)
    {
        ImageBox * box = new ImageBox(4,i,2,1);
        box->setImage(base.copy(i*16,64,16,32));
        ui->mainLayout->addWidget(box, box->getRow(), box->getCol(), box->gety(), box->getx());
        imgBoxList.append(box);
    }

    {
        ImageBox * box = new ImageBox(6,0,2,4);
        box->setImage(base.copy(0,96,64,32));
        ui->mainLayout->addWidget(box, box->getRow(), box->getCol(), box->gety(), box->getx());
        imgBoxList.append(box);
    }

    for (int i=0; i<6; i++)
    {
        ImageBox * box = new ImageBox(8,i*2,2,2);
        box->setImage(base.copy(i*32,128,32,32));
        ui->mainLayout->addWidget(box, box->getRow(), box->getCol(), box->gety(), box->getx());
        imgBoxList.append(box);
    }

    for (int i=0; i<3; i++)
    {
        ImageBox * box = new ImageBox(12,i*4,4,4);
        box->setImage(base.copy(i*64,192,64,64));
        ui->mainLayout->addWidget(box, box->getRow(), box->getCol(), box->gety(), box->getx());
        imgBoxList.append(box);
    }

    {
        ImageBox * box = new ImageBox(0,12,4,4);
        box->setImage(base.copy(192,0,64,64));
        ui->mainLayout->addWidget(box, box->getRow(), box->getCol(), box->gety(), box->getx());
        imgBoxList.append(box);
    }

    for (int i=0; i<2; i++)
    {
        ImageBox * box = new ImageBox(4+3*i,12,3,4);
        box->setImage(base.copy(192,i*48+64,64,48));
        ui->mainLayout->addWidget(box, box->getRow(), box->getCol(), box->gety(), box->getx());
        imgBoxList.append(box);
    }

    comboSize = new QComboBox();
    comboSize->addItem("256", 256);
    comboSize->addItem("512", 512);
    comboSize->addItem("1024", 1024);
    comboSize->addItem("2048", 2048);
    comboSize->addItem("4096", 4096);

    ui->mainToolBar->addWidget(comboSize);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionGenerate_triggered()
{    
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "paintings_kristoffer_zetterstrand.png", tr("Image Files (*.png)"));

    if (fileName != "")
    {
        mapSize = comboSize->currentData().toInt();
        QImage image(QSize(mapSize,mapSize), QImage::Format_ARGB32);
        image.fill(QColor(0,0,0,0));

        QPainter painter(&image);
        for (int i=0; i<26; i++)
        {
            painter.drawImage(imgBoxList.at(i)->getPos()*mapSize/16, imgBoxList.at(i)->getImage(mapSize));
        }
        painter.end();

        image.save(fileName);
        ui->statusBar->showMessage("The file was generated.", 2000);
    }
}

void MainWindow::on_actionGeneratePack_triggered()
{
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),".");

    if (dirName != "")
    {
        mapSize = comboSize->currentData().toInt();
        QImage image(QSize(mapSize,mapSize), QImage::Format_ARGB32);
        image.fill(QColor(0,0,0,0));

        QPainter painter(&image);
        for (int i=0; i<26; i++)
        {
            painter.drawImage(imgBoxList.at(i)->getPos()*mapSize/16, imgBoxList.at(i)->getImage(mapSize));
        }
        painter.end();

        QDir dir(dirName + "/PaintingOnly/assets/minecraft/textures/painting");
        dir.mkpath(".");
        image.save(dir.path() + "/paintings_kristoffer_zetterstrand.png");
        ui->statusBar->showMessage("The file was generated.", 2000);
    }
}




