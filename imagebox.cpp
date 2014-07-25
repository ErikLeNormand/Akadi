#include "imagebox.h"

#include <QFileDialog>

ImageBox::ImageBox(int fromRow, int fromCol, int height, int width)
{
    loaded = false;

    col = fromCol;
    row = fromRow;
    x = width;
    y = height;

    imageSize = QSize(32*x, 32*y);

    this->setMaximumSize(imageSize);
    this->setMinimumSize(imageSize);

    window = new ImageTrim(this, QSize(x,y));
    QObject::connect(window, SIGNAL(accepted(QImage)),this, SLOT(setImage(QImage)));
}

void ImageBox::mousePressEvent ( QMouseEvent * event )
{
    if (!loaded)
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
        if (fileName != "")
        {
            image = QImage(fileName);
            loaded = true;
            window->setImage(image);
            window->open();
        }
    }
    else
    {
        window->open();
    }
}

int ImageBox::getx() const
{
    return x;
}

int ImageBox::gety() const
{
    return y;
}

int ImageBox::getCol() const
{
    return col;
}

int ImageBox::getRow() const
{
    return row;
}

QPoint ImageBox::getPos() const
{
    return QPoint(col,row);
}

void ImageBox::setImage(QImage img)
{
    image = QImage(img);
    this->setPixmap(QPixmap::fromImage(image.scaled(imageSize)));
}

QImage ImageBox::getImage(int mapSize) const
{
    QSize scaledSize(mapSize/16*x, mapSize/16*y);
    return image.scaled(scaledSize);
}






