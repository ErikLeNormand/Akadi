/*!
  * \file mainwindow.h
  * \author Erik Le Normand
  * \version 1.0
  * \date 29/07/2014
  **/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>

#include "imagebox.h"

namespace Ui
{
class MainWindow;
}

//! The main window class.
/*!
 * Main window where all images are displayed in several QLabel.
 * There are interactions with images to change them.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow * ui;
    QList<ImageBox*> imgBoxList;    /*!< List of ImageBox where images are displayed */
    int mapSize;                    /*!< Final image definition */
    QComboBox * comboSize;          /*!< Combo box used to choose the image definition */

public:
    /*!
     * \brief Constructor
     *
     * Create main window with file menu and all image box to display painting.
     */
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    /*!
     * \brief Define all images
     * \param image QImage where are all images used in painting.
     *
     * Define images for all image boxes with parts of given picture.
     */
    void setImage(QImage image);
    /*!
     * \brief Generate image
     * \param fileName Complete path of created image.
     *
     * Create the file with all painting with eventual directories.
     */
    void generate(QString fileName);

private slots:
    /*!
     * \brief Button to create the final file.
     *
     * This action generate an image with all chosen images displayed in main window.
     * The image format is like the file format used by the game engine.
     */
    void on_actionGenerate_triggered();
    /*!
     * \brief Button to create the final file with ressource pack directories.
     *
     * This action generate an image with all chosen images displayed in main window.
     * The image format is like the file format used by the game engine.
     * Create also the directories for a resource pack.
     */
    void on_actionGeneratePack_triggered();
    /*!
     * \brief Button to load a file.
     *
     * Action to open image file in game engine format to rework an image.
     */
    void on_actionOpenFile_triggered();
};

#endif // MAINWINDOW_H
