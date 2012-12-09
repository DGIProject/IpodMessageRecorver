#ifndef TOHTMLDIALOG_H
#define TOHTMLDIALOG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class ToHtmlDialog;
}

class ToHtmlDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ToHtmlDialog(QWidget *parent = 0, QSqlDatabase db = NULL);
    ~ToHtmlDialog();
    
private:
    Ui::ToHtmlDialog *ui;
    QSqlQuery* query_sqlitedb;
    QSqlDatabase SQliteDb;
public slots:
    void on_Btn_cancell_clicked();
    void on_Btn_export_clicked();
    void on_radioButton_2_clicked();
    void on_radioButton_clicked();
};

#endif // TOHTMLDIALOG_H
