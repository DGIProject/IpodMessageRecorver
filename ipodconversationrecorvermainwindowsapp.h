#ifndef IPODCONVERSATIONRECORVERMAINWINDOWSAPP_H
#define IPODCONVERSATIONRECORVERMAINWINDOWSAPP_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class IpodConversationRecorverMainWindowsApp;
}

class IpodConversationRecorverMainWindowsApp : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit IpodConversationRecorverMainWindowsApp(QWidget *parent = 0, QSqlDatabase db = NULL);
    ~IpodConversationRecorverMainWindowsApp();
    
private:
    Ui::IpodConversationRecorverMainWindowsApp *ui;
    QSqlDatabase db_windwso2;
    QSqlDatabase sqlitedb;
    QSqlQuery* query_windows2;
    QSqlQuery* query_sqlitedb;

private slots :
    void getUserInfo();
    void on_actionChoose_the_file_triggered();
    void VerifyFile(QString db_file);
    void Get_Conv_List();
    void on_ContactList_clicked();
    void GetConversations(QString contact);
    void on_actionDonate_triggered();
    void on_actionHelp_triggered();
    void on_actionUpdates_triggered();
    void on_actionAbout_triggered();
    void on_actionVersions_triggered();
    void on_actionTo_html_format_triggered();
};

#endif // IPODCONVERSATIONRECORVERMAINWINDOWSAPP_H
