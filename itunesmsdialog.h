#ifndef ITUNESMSDIALOG_H
#define ITUNESMSDIALOG_H

#include <QDialog>

namespace Ui {
class ItuneSMSDialog;
}

class ItuneSMSDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ItuneSMSDialog(QWidget *parent = 0);
    ~ItuneSMSDialog();
    
private:
    Ui::ItuneSMSDialog *ui;
};

#endif // ITUNESMSDIALOG_H
