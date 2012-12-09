#ifndef HELPWINDOWS_H
#define HELPWINDOWS_H

#include <QDialog>

namespace Ui {
class HelpWindows;
}

class HelpWindows : public QDialog
{
    Q_OBJECT
    
public:
    explicit HelpWindows(QWidget *parent = 0, QString Action = NULL);
    ~HelpWindows();
    
private:
    Ui::HelpWindows *ui;
};

#endif // HELPWINDOWS_H
