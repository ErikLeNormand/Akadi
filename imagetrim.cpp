#include "imagetrim.h"

#include <QPainter>
#include <QFileDialog>

ImageTrim::ImageTrim(QWidget *parent, QSize size) : QDialog(parent)
{
    int x = size.width();
    int y = size.height();
    if (x>y)
    {
        displaySize = QSize(512,512/x*y);
    }
    else
    {
        displaySize = QSize(512/y*x,512);
    }
    this->setFixedSize(displaySize.width()+22, displaySize.height()+51);

    image = QImage(displaySize, QImage::Format_ARGB32);
    image.fill(QColor(0,0,0,0));

    ratio = 1;
    pos = QPoint(0,0);
    mousePos0 = QPoint(0,0);
    mousePos1 = QPoint(0,0);

    diagLayout = new QVBoxLayout();
    buttonLayout = new QHBoxLayout();

    this->setLayout(diagLayout);
    editImage = new QLabel();
    editImage->setIndent(100);
    editImage->setStyleSheet("background-color:white;border: 1px solid black;");

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
    imgFinal = img;
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

    QImage tmpImage(image);
    QPainter painter(&tmpImage);
    painter.drawImage(pos, imgScaled);
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

    QImage tmpImage(image);
    QPainter painter(&tmpImage);
    painter.drawImage(posTmp, imgScaled);
    painter.end();
    editImage->setPixmap(QPixmap::fromImage(tmpImage));
}

void ImageTrim::mouseReleaseEvent ( QMouseEvent * event )
{
    event->ignore();
    mousePos1 = editImage->mapFromGlobal(QCursor::pos());

    pos = pos + (mousePos1-mousePos0);

    imgFinal = QImage(image);
    QPainter painter(&imgFinal);
    painter.drawImage(pos, imgScaled);
    painter.end();
    editImage->setPixmap(QPixmap::fromImage(imgFinal));
}

void ImageTrim::wheelEvent(QWheelEvent * event)
{
    event->ignore();
    int angle = event->angleDelta().y();
    if (angle < 0)
    {
//        ratio = ratio * 29/30;
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

    imgFinal = QImage(image);
    QPainter painter(&imgFinal);
    painter.drawImage(pos, imgScaled);
    painter.end();
    editImage->setPixmap(QPixmap::fromImage(imgFinal));
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
    imgFinal = QImage(image.scaled(displaySize*4));
    QPainter painter(&imgFinal);
    painter.drawImage(pos*4, imgSrc.scaledToWidth(imgSrc.width()*ratio*4));

    painter.end();
    emit accepted(imgFinal);
    this->accept();
}
