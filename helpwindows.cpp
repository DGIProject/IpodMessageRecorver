#include "helpwindows.h"
#include "ui_helpwindows.h"
#include <QtGui>

HelpWindows::HelpWindows(QWidget *parent, QString Action) :
    QDialog(parent),
    ui(new Ui::HelpWindows)
{
    ui->setupUi(this);
    ui->Donnate->hide();
    ui->About->hide();
    ui->Help->hide();
    ui->version->hide();

    if (Action == "vers")
    {
        ui ->version->show();
    }
    else if ( Action == "Abo")
    {
        ui->About->show();
    }
    else if ( Action == "hel")
    {
        ui->Help->show();
    }
    else if ( Action == "Don")
    {
        ui->Donnate->show();
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Impossible d'initailiser l'interface");
        HelpWindows::close();
    }


}


HelpWindows::~HelpWindows()
{
    delete ui;
}
