#include "imagetrim.h"

#include <QPainter>
#include <QFileDialog>
#include <QResizeEvent>

ImageTrim::ImageTrim(QWidget *parent, QSize size, int windowSize) : QDialog(parent)
{
    int x = size.width();
    int y = size.height();

    if (x>y)
    {
        displaySize = QSize(windowSize,windowSize/x*y);
    }
    else
    {
        displaySize = QSize(windowSize/y*x,windowSize);
    }
    this->setFixedSize(displaySize.width()+24, displaySize.height()+53);

    this->setWindowTitle("Image editor");
    if (QIcon::hasThemeIcon("applications-graphics"))
    {
        this->setWindowIcon(QIcon::fromTheme("applications-graphics"));
    }

    format = size;

    image = QImage(displaySize, QImage::Format_ARGB32);
    image.fill(QColor(0,0,0,0));\

    ratio = 1;
    pos = QPoint(0,0);
    mousePos0 = QPoint(0,0);
    mousePos1 = QPoint(0,0);

    diagLayout = new QVBoxLayout();
    buttonLayout = new QHBoxLayout();

    this->setLayout(diagLayout);
    editImage = new QLabel();
    editImage->setIndent(100);
    editImage->setStyleSheet("background-color:white; border: 1px solid black;");
    editImage->setCursor(QCursor(Qt::OpenHandCursor));

    diagLayout->addWidget(editImage);
    diagLayout->addLayout(buttonLayout);

    buttAccept = new QPushButton(tr("Valid"));
    buttLoad = new QPushButton(tr("Reload"));
    buttonLayout->addWidget(buttAccept);
    buttonLayout->addWidget(buttLoad);

    QObject::connect(buttAccept, SIGNAL(clicked()),this, SLOT(acceptModif()));
    QObject::connect(buttLoad, SIGNAL(clicked()),this, SLOT(loadImage()));
}

void ImageTrim::setImage(QImage img)
{
    imgSrc = img;
    imgScaled = img;
    pos = QPoint(0,0);
    ratio = 1;

    double x = double(displaySize.width()) / double(img.width());
    double y = double(displaySize.height()) / double(img.height());
    if (img.width()*y < displaySize.width())
    {
        ratio = x;
    }
    else
    {
        ratio = y;
    }
    imgScaled = imgSrc.scaledToWidth(imgSrc.width()*ratio);

    this->displayImage();
}

void ImageTrim::displayImage(bool otherPos, QPoint position)
{
    QImage tmpImage(image);
    QPainter painter(&tmpImage);
    if (otherPos)
    {
        painter.drawImage(position, imgScaled);
    }
    else
    {
        painter.drawImage(pos, imgScaled);
    }
    painter.end();
    editImage->setPixmap(QPixmap::fromImage(tmpImage));
}

void ImageTrim::mousePressEvent ( QMouseEvent * event )
{
    event->ignore();
    mousePos0 = editImage->mapFromGlobal(QCursor::pos());
}

void ImageTrim::mouseMoveEvent ( QMouseEvent * event )
{
    event->ignore();
    mousePos1 = editImage->mapFromGlobal(QCursor::pos());

    QPoint posTmp = pos + (mousePos1-mousePos0);

    this->displayImage(true, posTmp);
}

void ImageTrim::mouseReleaseEvent ( QMouseEvent * event )
{
    event->ignore();
    mousePos1 = editImage->mapFromGlobal(QCursor::pos());

    pos = pos + (mousePos1-mousePos0);

    this->displayImage();
}

void ImageTrim::wheelEvent(QWheelEvent * event)
{
    event->ignore();
    int angle = event->angleDelta().y();
    if (angle < 0)
    {
        ratio = ratio * 49/50;
    }
    else
    {
        ratio = ratio * 50/49;
    }

    int x = imgScaled.width();
    int y = imgScaled.height();
    imgScaled = imgSrc.scaledToWidth(imgSrc.width()*ratio);

    x = imgScaled.width() - x;
    pos.setX(pos.x() - x/2);

    y = imgScaled.height() - y;
    pos.setY(pos.y() - y/2);

    this->displayImage();
}

void ImageTrim::keyPressEvent(QKeyEvent * event)
{
    bool moved = false;
    switch (event->key()) {
    case Qt::Key_Z:
        pos.setY(pos.y()+1);
        moved = true;
        break;
    case Qt::Key_S:
        pos.setY(pos.y()-1);
        moved = true;
        break;
    case Qt::Key_Q:
        pos.setX(pos.x()+1);
        moved = true;
        break;
    case Qt::Key_D:
        pos.setX(pos.x()-1);
        moved = true;
        break;
    default:
        break;
    }
    if (moved)
    {
        this->displayImage();
    }
}

void ImageTrim::loadImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if (fileName != "")
    {
        QImage img;
        if (img.load(fileName))
        {
            this->setImage(img);
        }
    }
}

void ImageTrim::acceptModif()
{
    QImage imgFinal = QImage(image.scaled(format*1024));
    double imgDif = 1 / double(displaySize.width()) * format.width()*1024;
    QPoint posFinal = pos * imgDif;

    QPainter painter(&imgFinal);
    painter.drawImage(posFinal, imgSrc.scaledToWidth(imgSrc.width()*ratio*imgDif));
    painter.end();
    emit accepted(imgFinal);
    this->accept();
}

