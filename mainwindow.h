#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>

#include "imagebox.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionGenerate_triggered();

    void on_actionGeneratePack_triggered();

    void on_actionOpenFile_triggered();

private:
    Ui::MainWindow * ui;
    QList<ImageBox*> imgBoxList;
    int mapSize;
    QComboBox * comboSize;

    void setImage(QImage image);
};

#endif // MAINWINDOW_H
