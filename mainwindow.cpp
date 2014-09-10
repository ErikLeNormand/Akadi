#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QFileDialog>
#include <QDesktopWidget>

#define initBox(x,y,w,h,def) \
    ImageBox * box = new ImageBox(x,y,w,h,def); \
    box->setCursor(QCursor(Qt::PointingHandCursor)); \
    ui->mainLayout->addWidget(box, box->getRow(), box->getCol(), box->gety(), box->getx()); \
    imgBoxList.append(box);

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Minecraft painting generator"));
    if (QIcon::hasThemeIcon("applications-graphics"))
    {
        this->setWindowIcon(QIcon::fromTheme("applications-graphics"));
    }

    QRect rec = QApplication::desktop()->screenGeometry();
    int def = (rec.height() - 140) / 16 ;
    mapSize = 0;

    QImage base(":/new/image/base");

    for(int i=0; i<7; i++)
    {
        initBox(0,i,1,1,def)
    }
    for (int i=0; i<5; i++)
    {
        initBox(2,i*2,1,2,def);
    }
    for (int i=0; i<2; i++)
    {
        initBox(4,i,2,1,def);
    }
    {
        initBox(6,0,2,4,def);
    }
    for (int i=0; i<6; i++)
    {
        initBox(8,i*2,2,2,def);
    }
    for (int i=0; i<3; i++)
    {
        initBox(12,i*4,4,4,def);
    }
    {
        initBox(0,12,4,4,def);
    }
    for (int i=0; i<2; i++)
    {
        initBox(4+3*i,12,3,4,def);
    }

    this->setImage(base);

    comboSize = new QComboBox();
    comboSize->addItem(tr("256 px : Pixel soup"), 256);
    comboSize->addItem(tr("512 px : For console"), 512);
    comboSize->addItem(tr("1024 px : No glass ?"), 1024);
    comboSize->addItem(tr("2048 px : Can forgive"), 2048);
    comboSize->addItem(tr("4096 px : Recommended"), 4096);
    comboSize->addItem(tr("6144 px : For PC Gamer"), 6144);
    comboSize->addItem(tr("8192 px : HardCore"), 8192);
    comboSize->addItem(tr("12288 px : Insame"), 12288);
    comboSize->addItem(tr("16384 px : No, You didn't ?"), 16384);

    if (QIcon::hasThemeIcon("document-open"))
    {
        ui->actionOpenFile->setIcon(QIcon::fromTheme("document-open"));
    }
    if (QIcon::hasThemeIcon("document-save"))
    {
        ui->actionGenerate->setIcon(QIcon::fromTheme("document-save"));
    }
    if (QIcon::hasThemeIcon("document-save-as"))
    {
        ui->actionGeneratePack->setIcon(QIcon::fromTheme("document-save-as"));
    }
    if (QIcon::hasThemeIcon("application-exit"))
    {
        ui->actionExit->setIcon(QIcon::fromTheme("application-exit"));
    }
    if (QIcon::hasThemeIcon("help-about"))
    {
        ui->actionHelpInfos->setIcon(QIcon::fromTheme("help-about"));
    }

    ui->mainToolBar->addWidget(comboSize);
    ui->mainToolBar->addSeparator();
    QWidget * spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    ui->mainToolBar->addWidget(spacer);
    ui->mainToolBar->addAction(ui->actionHelpInfos);

    hiBox = new HelpInfoBox();

    QObject::connect(ui->actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setImage(QImage image)
{
    int ratio = image.width()/16;
    for (int i=0; i<imgBoxList.size(); i++)
    {
        imgBoxList[i]->setImage(image.copy(imgBoxList.at(i)->getCol()*ratio,
                                           imgBoxList.at(i)->getRow()*ratio,
                                           imgBoxList.at(i)->getx()*ratio,
                                           imgBoxList.at(i)->gety()*ratio), true);
    }
}

void MainWindow::on_actionGenerate_triggered()
{    
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "paintings_kristoffer_zetterstrand.png", tr("Image Files (*.png)"));

    if (fileName != "")
    {
        this->generate(fileName);
    }
}

void MainWindow::on_actionGeneratePack_triggered()
{
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),".");

    if (dirName != "")
    {
        QDir dir(dirName + "/PaintingOnly/assets/minecraft/textures/painting");
        dir.mkpath(".");
        QString fileName = dir.path() + "/paintings_kristoffer_zetterstrand.png";
        this->generate(fileName);
    }
}

void MainWindow::on_actionOpenFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if (fileName != "")
    {
        QImage image;
        if (image.load(fileName))
        {
            this->setImage(image);
        }
        else
        {
            ui->statusBar->showMessage("Image loading failed !");
        }
    }
}

void MainWindow::generate(QString fileName)
{
    ui->statusBar->showMessage(tr("Please wait during image generation."));

    mapSize = comboSize->currentData().toInt();
    QImage image(QSize(mapSize,mapSize), QImage::Format_ARGB32);
    image.fill(QColor(0,0,0,0));

    QPainter painter(&image);
    for (int i=0; i<imgBoxList.size(); i++)
    {
        painter.drawImage(imgBoxList.at(i)->getPos()*mapSize/16, imgBoxList.at(i)->getImage(mapSize));
    }
    painter.end();

    image.save(fileName);
    ui->statusBar->clearMessage();
    ui->statusBar->showMessage(tr("The file is generated."), 2000);
}

void MainWindow::on_actionHelpInfos_triggered()
{
    hiBox->show();
}
