#include "itunesmsdialog.h"
#include "ui_itunesmsdialog.h"
#include <QDir>
#include <QDebug>

ItuneSMSDialog::ItuneSMSDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItuneSMSDialog)
{
    ui->setupUi(this);
    QDir dir;
         dir.setFilter(QDir::Dirs | QDir::NoDot | QDir::NoDotDot);
         QFileInfoList list = dir.entryInfoList();
         qDebug() << "     Bytes Filename";
         for (int i = 0; i < list.size(); ++i) {
             QFileInfo fileInfo = list.at(i);
             qDebug() << qPrintable(QString("%1").arg(fileInfo.fileName()));
             ui->comboBox->addItem(QString("%1").arg(fileInfo.fileName()));
         }
}

ItuneSMSDialog::~ItuneSMSDialog()
{
    delete ui;
}
