/*!
  * \file helpinfobox.h
  * \author Erik Le Normand
  * \version 1.0
  * \date 21/08/2014
  **/
#ifndef HELPINFOBOX_H
#define HELPINFOBOX_H

#include <QDialog>

namespace Ui {
class HelpInfoBox;
}

//! The info display class.
/*!
 * HelpInfoBox displays a small window with informations about this application.
*/
class HelpInfoBox : public QDialog
{
    Q_OBJECT

public:
    explicit HelpInfoBox(QWidget *parent = 0);
    ~HelpInfoBox();

private:
    Ui::HelpInfoBox *ui;
};

#endif // HELPINFOBOX_H
