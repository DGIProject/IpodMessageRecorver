#include <QtGui/QApplication>
#include "ipodrecorvermain.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IpodRecorverMain w;
    w.show();
    
    return a.exec();
}
