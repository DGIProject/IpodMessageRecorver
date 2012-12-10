#include "tohtmldialog.h"
#include "ui_tohtmldialog.h"
#include <QtSql>
#include <QtGui>
#include <QFile>

ToHtmlDialog::ToHtmlDialog(QWidget *parent, QSqlDatabase db) :
    QDialog(parent),
    ui(new Ui::ToHtmlDialog)
{
    ui->setupUi(this);
    SQliteDb = db;
    ui->radioButton->setChecked(true);
    ui->comboBox->setEnabled(false);
    query_sqlitedb = new QSqlQuery(SQliteDb);
    if (SQliteDb.open())
    {
        query_sqlitedb->clear();
        query_sqlitedb->prepare("SELECT * FROM madrid_chat;");

        if (query_sqlitedb->exec())
        {

            while(query_sqlitedb->next())
            {
                QVariant test2 = query_sqlitedb->value(5);
                ui->comboBox->addItem(test2.toString());
            }

        }
        else
        {
            QMessageBox::information(this, "Erreur", "Une erreur s'est produite, le fichier est peut etre endomage \n" + query_sqlitedb->lastError().text());
        }
    }
    else
    {
        QMessageBox::information(this, "Erreur", "Une erreur s'est produite, le fichier est peut etre endomage \n" + query_sqlitedb->lastError().text());
    }

    SQliteDb.close();

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
    QFile htmlFile("test.txt");
    if (htmlFile.open(QIODevice::WriteOnly))
    {
            QString str ="patate !";
            QTextStream outstream(&htmlFile);
            outstream << str;
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Une Erreur s'est produit lors de l'exportation");
    }

    htmlFile.flush();
    htmlFile.close();

}
void ToHtmlDialog::on_radioButton_2_clicked()
{
    ui->comboBox->setEnabled(true);
}
void ToHtmlDialog::on_radioButton_clicked()
{
    ui->comboBox->setEnabled(false);
}
