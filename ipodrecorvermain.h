#ifndef IPODRECORVERMAIN_H
#define IPODRECORVERMAIN_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class IpodRecorverMain;
}

class IpodRecorverMain : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit IpodRecorverMain(QWidget *parent = 0);
    ~IpodRecorverMain();
public slots:
    void connectToBdd();
    void disconnectFromBdd();
    void ConnectToService();
    void on_ConnectButton_clicked();
    void on_SubscribButton_clicked();

    
private:
    Ui::IpodRecorverMain *ui;
    QSqlDatabase db;
    QSqlQuery* query_base;

};

#endif // IPODRECORVERMAIN_H
