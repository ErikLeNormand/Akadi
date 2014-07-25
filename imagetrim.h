#ifndef IMAGETRIM_H
#define IMAGETRIM_H

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDialog>
#include <QWheelEvent>

class ImageTrim : public QDialog
{
    Q_OBJECT

private:
    QSize imgSize;
    QImage image;
    QImage imgSrc;
    QImage imgDone;
    QImage imgFinal;
    double ratio;
    QVBoxLayout * diagLayout;
    QHBoxLayout * buttonLayout;
    QLabel * editImage;
    QPushButton * buttAccept;
    QPushButton * buttLoad;
    QPoint pos;
    QPoint mousePos0;
    QPoint mousePos1;

protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void wheelEvent(QWheelEvent * event);

public:
    explicit ImageTrim(QWidget * parent, QSize size);
    void setImage(QImage img);

signals:
    void accepted(QImage img);

public slots:
    void acceptModif();
    void loadImage();

};

#endif // IMAGETRIM_H
