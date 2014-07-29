/*!
  * \file imagebox.h
  * \author Erik Le Normand
  * \version 1.0
  * \date 29/07/2014
  **/
#ifndef IMAGEBOX_H
#define IMAGEBOX_H

#include <QLabel>

#include "imagetrim.h"

//! The image display class.
/*!
 * ImageBox is a tool to display an image, each corresponds to a painting in the game.
 * It call a window to modify image when user click it.
*/
class ImageBox : public QLabel
{
    Q_OBJECT

private:
    QImage image;       /*!< One image for one painting */
    QSize displaySize;  /*!< Image display size */
    int col;            /*!< Horizontal position of the image */
    int row;            /*!< Vertical position of the image */
    int x;              /*!< Image width */
    int y;              /*!< Image height */
    ImageTrim * window; /*!< Window to modify image */
    bool loaded;        /*!< True if an image is loaded by user */

public:
    /*!
     * \brief Constructor
     * \param fromRow Vertical position
     * \param fromCol Horizontal position
     * \param height Image Height
     * \param width Image Width
     */
    ImageBox(int fromRow = 0, int fromCol = 0, int height = 1, int width = 1);
    /*!
     * \brief Return horizontal image position
     */
    int getCol() const;
    /*!
     * \brief Return vertical image position
     */
    int getRow() const;
    /*!
     * \brief Return image width
     */
    int getx() const;
    /*!
     * \brief Return image height
     */
    int gety() const;
    /*!
     * \brief Return image position
     */
    QPoint getPos() const;
    /*!
     * \brief Return image
     * \param mapSize Ratio used to scale given image.
     * \return The scaled image.
     */
    QImage getImage(int mapSize) const;

public slots:
    /*!
     * \brief Change image for the painting
     * \param img QImage to load
     */
    void setImage(QImage img);

protected:
    /*!
     * \brief Event of image click
     * Open a window on click. This window is an ImageTrim used to modify the image.
     */
    void mousePressEvent ( QMouseEvent * event ) ;
};

#endif // IMAGEBOX_H
