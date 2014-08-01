#include "imagebox.h"

#include <QFileDialog>

ImageBox::ImageBox(int fromRow, int fromCol, int height, int width)
{
    loaded = false;

    col = fromCol;
    row = fromRow;
    x = width;
    y = height;

    displaySize = QSize(32*x, 32*y);

    this->setMaximumSize(displaySize);
    this->setMinimumSize(displaySize);

    window = new ImageTrim(this, QSize(x,y));
    QObject::connect(window, SIGNAL(accepted(QImage)),this, SLOT(setImage(QImage)));
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

QImage ImageBox::getImage(int mapSize) const
{
    QSize scaledSize(mapSize/16*x, mapSize/16*y);
    return image.scaled(scaledSize);
}

void ImageBox::setImage(QImage img, bool newImg)
{
    image = QImage(img);
    this->setPixmap(QPixmap::fromImage(image.scaled(displaySize, Qt::KeepAspectRatio)));
    if (newImg)
    {
        window->setImage(img);
    }
}

void ImageBox::mousePressEvent ( QMouseEvent * event )
{
    event->ignore();
    if (!loaded)
    {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
        if (fileName != "")
        {
            if (image.load(fileName))
            {
                this->setImage(image);
                window->setImage(image);
            }
            loaded = true;
        }
    }
    window->open();
}






