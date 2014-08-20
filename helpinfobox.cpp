#include "helpinfobox.h"
#include "ui_helpinfobox.h"

HelpInfoBox::HelpInfoBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpInfoBox)
{
    ui->setupUi(this);
    if (QIcon::hasThemeIcon("help-about"))
    {
        this->setWindowIcon(QIcon::fromTheme("help-about"));
    }
}

HelpInfoBox::~HelpInfoBox()
{
    delete ui;
}
