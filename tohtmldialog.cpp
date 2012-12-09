#include "tohtmldialog.h"
#include "ui_tohtmldialog.h"
#include <QtSql>

ToHtmlDialog::ToHtmlDialog(QWidget *parent, QSqlDatabase db) :
    QDialog(parent),
    ui(new Ui::ToHtmlDialog)
{
    ui->setupUi(this);
    SQliteDb = db;
    ui->radioButton->setChecked(true);
}

ToHtmlDialog::~ToHtmlDialog()
{
    delete ui;
}

void ToHtmlDialog::on_Btn_cancell_clicked()
{
    ToHtmlDialog::close();
}
void ToHtmlDialog::on_Btn_export_clicked()
{

}
void ToHtmlDialog::on_radioButton_2_clicked()
{
    ui->comboBox->setEnabled(true);
}
void ToHtmlDialog::on_radioButton_clicked()
{
    ui->comboBox->setEnabled(false);
}
