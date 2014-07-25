#ifndef IMAGEBOX_H
#define IMAGEBOX_H

#include <QLabel>
#include "imagetrim.h"

class ImageBox : public QLabel
{
    Q_OBJECT

private:
    QImage image;
    QSize imageSize;
    int col;
    int row;
    int x;
    int y;
    ImageTrim * window ;
    bool loaded;

signals:
    void clicked();

public slots:
    void setImage(QImage img);

protected:
    void mousePressEvent ( QMouseEvent * event ) ;

public:
    ImageBox(int fromRow = 0, int fromCol = 0, int height = 1, int width = 1);
    ImageBox(bool empty, int fromRow = 0, int fromCol = 0, int height = 1, int width = 1);
    int getCol() const;
    int getRow() const;
    int getx() const;
    int gety() const;
    QPoint getPos() const;
    QImage getImage(int mapSize) const;
};

#endif // IMAGEBOX_H
