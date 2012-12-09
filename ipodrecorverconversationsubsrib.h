#ifndef IPODRECORVERCONVERSATIONSUBSRIB_H
#define IPODRECORVERCONVERSATIONSUBSRIB_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class IpodRecorverConversationSubsrib;
}

class IpodRecorverConversationSubsrib : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit IpodRecorverConversationSubsrib(QWidget *parent = 0, QSqlDatabase db = NULL);
    ~IpodRecorverConversationSubsrib();
    
private:
    Ui::IpodRecorverConversationSubsrib *ui;
    QSqlDatabase db_subscrib;
    QSqlQuery* query_subscrib;
public slots:
    void on_ValidBtn_clicked();
    void on_CanceBtn_clicked();
};
#endif // IPODRECORVERCONVERSATIONSUBSRIB_H
