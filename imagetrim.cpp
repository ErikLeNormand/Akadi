#include "imagetrim.h"

#include <QPainter>
#include <QFileDialog>

ImageTrim::ImageTrim(QWidget *parent, QSize size) :
    QDialog(parent)
{
    int x = size.width();
    int y = size.height();
    if (x>y)
    {
        imgSize = QSize(512,512/x*y);
    }
    else
    {
        imgSize = QSize(512/y*x,512);
    }
    this->setFixedSize(imgSize.width()+22, imgSize.height()+51);

    image = QImage(imgSize, QImage::Format_ARGB32);
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
    imgDone = img;
    imgFinal = img;

    QImage tmpImage(image);
    QPainter painter(&tmpImage);
    painter.drawImage(pos, imgSrc);
    painter.end();
    editImage->setPixmap(QPixmap::fromImage(tmpImage));
}

void ImageTrim::mousePressEvent ( QMouseEvent * event )
{
    mousePos0 = editImage->mapFromGlobal(QCursor::pos());
}

void ImageTrim::mouseMoveEvent ( QMouseEvent * event )
{
    mousePos1 = editImage->mapFromGlobal(QCursor::pos());

    QPoint posTmp = pos + (mousePos1-mousePos0);

    QImage tmpImage(image);
    QPainter painter(&tmpImage);
    painter.drawImage(posTmp, imgDone);
    painter.end();
    editImage->setPixmap(QPixmap::fromImage(tmpImage));
}

void ImageTrim::mouseReleaseEvent ( QMouseEvent * event )
{
    mousePos1 = editImage->mapFromGlobal(QCursor::pos());

    pos = pos + (mousePos1-mousePos0);

    imgFinal = QImage(image);
    QPainter painter(&imgFinal);
    painter.drawImage(pos, imgDone);
    painter.end();
    editImage->setPixmap(QPixmap::fromImage(imgFinal));
}

void ImageTrim::wheelEvent(QWheelEvent *event)
{
    int angle = event->angleDelta().y();
    if (angle < 0)
    {
        ratio = ratio * 9/10;
    }
    else
    {
        ratio = ratio * 10/9;
    }

    int x = imgDone.width();
    int y = imgDone.height();
    imgDone = imgSrc.scaledToWidth(imgSrc.width()*ratio);

    x = imgDone.width() - x;
    pos.setX(pos.x() - x/2);

    y = imgDone.height() - y;
    pos.setY(pos.y() - y/2);

    imgFinal = QImage(image);
    QPainter painter(&imgFinal);
    painter.drawImage(pos, imgDone);
    painter.end();
    editImage->setPixmap(QPixmap::fromImage(imgFinal));
}

void ImageTrim::acceptModif()
{
    imgFinal = QImage(image);
    QPainter painter(&imgFinal);
    painter.drawImage(pos, imgDone);
    painter.end();
    emit accepted(imgFinal);
    this->accept();
}

void ImageTrim::loadImage()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if (fileName != "")
    {
        if (imgSrc.load(fileName))
        {
            this->setImage(image);
            imgDone = QImage(imgSrc);
            imgFinal = QImage(image);
            pos = QPoint(0,0);
            QPainter painter(&imgFinal);
            painter.drawImage(pos, imgSrc);
            painter.end();
            editImage->setPixmap(QPixmap::fromImage(imgFinal));
        }
    }
}
