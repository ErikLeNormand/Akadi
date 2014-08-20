#ifndef HELPINFOBOX_H
#define HELPINFOBOX_H

#include <QDialog>

namespace Ui {
class HelpInfoBox;
}

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
