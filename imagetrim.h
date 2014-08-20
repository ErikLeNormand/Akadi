/*!
  * \file imagetrim.h
  * \author Erik Le Normand
  * \version 1.0
  * \date 29/07/2014
  **/
#ifndef IMAGETRIM_H
#define IMAGETRIM_H

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDialog>
#include <QWheelEvent>
#include <QKeyEvent>

//! The image editor class.
/*!
 * ImageTrim is a window used to edit an image.
 * Used to move and to resize image display in a painting.
*/
class ImageTrim : public QDialog
{
    Q_OBJECT

private:
    QSize displaySize;          /*!< Display Size, same format than painting */
    QImage image;               /*!< Draw plan */
    QImage imgSrc;              /*!< Image without modification */
    QImage imgScaled;           /*!< Scaled image */
//    QImage imgFinal;            /*!< Final image */
    double ratio;               /*!< Ratio used to resize image */
    QSize format;
    QPoint pos;                 /*!< Image position */
    QPoint mousePos0;           /*!< Mouse position on mouse press */
    QPoint mousePos1;           /*!< Mouse position on mouse release */
    QVBoxLayout * diagLayout;   /*!< Main layout */
    QHBoxLayout * buttonLayout; /*!< Button layout */
    QLabel * editImage;         /*!< Image display */
    QPushButton * buttAccept;   /*!< Button to valid modification */
    QPushButton * buttLoad;     /*!< Button to load a new image */

    /*!
     * \brief Display the image
     * \param otherPos True if don't use pos
     * \param position New position of the image
     */
    void displayImage(bool otherPos = false, QPoint position = QPoint(0,0));

public:
    /*!
     * \brief Constructor
     * \param size Format size of the painting used to resize window
     * \param windowSize size of the edition zone
     *
     * Window where user can resize and move the loaded image.
     * Format size corresponds to painting format.
     */
    explicit ImageTrim(QWidget * parent, QSize size, int windowSize);
    /*!
     * \brief Load an image
     * \param img New image to load.
     *
     * Change image by a new image and reset parameter changes.
     */
    void setImage(QImage img);

protected:
    /*!
     * \brief Save mouse position.
     */
    void mousePressEvent(QMouseEvent * event);
    /*!
     * \brief Move image with the mouse cursor.
     */
    void mouseMoveEvent(QMouseEvent * event);
    /*!
     * \brief Change final image position .
     */
    void mouseReleaseEvent(QMouseEvent * event);
    /*!
     * \brief Resize image on wheel move.
     */
    void wheelEvent(QWheelEvent * event);
    /*!
     * \brief Move image
     *
     * User can use keys Z, S, Q and D to move the image to a pixel.
     */
    void keyPressEvent(QKeyEvent * event);

signals:
    /*!
     * \brief Signal to transmit image
     * \param img Final image
     */
    void accepted(QImage img);

public slots:
    /*!
     * \brief Open window to load new image.
     */
    void loadImage();
    /*!
     * \brief Accept image and with changes
     *
     * Emit a signal with final image.
     */
    void acceptModif();

};

#endif // IMAGETRIM_H
