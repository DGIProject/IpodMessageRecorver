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
    ui->widget->hide();
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
    QFile htmlFile("test.html"), filetoremove("test.html");
    filetoremove.remove();
    filetoremove.close();
    if (htmlFile.open(QIODevice::WriteOnly))
    {
        if (ui->radioButton->isChecked())
        {

        }
        else
        {
            if (SQliteDb.open())
            {
                ui->widget->show();
                query_sqlitedb->clear();

                query_sqlitedb->prepare("SELECT COUNT(*) AS nb_field FROM message WHERE madrid_handle = ?");
                query_sqlitedb->addBindValue(ui->comboBox->currentText());
                int testintforhqdfbsdf = 0;

                if (query_sqlitedb->exec())
                {
                    while(query_sqlitedb->next())
                    {
                        testintforhqdfbsdf = query_sqlitedb->record().value("nb_field").toInt();
                        qDebug() << query_sqlitedb->record().value("nb_field");
                    }
                }

                ui->Progress->setMinimum(0);
                ui->Progress->setMaximum(testintforhqdfbsdf);

                query_sqlitedb->clear();
                query_sqlitedb->prepare("SELECT * FROM message WHERE madrid_handle = ? ORDER BY ROWID");
                query_sqlitedb->addBindValue(ui->comboBox->currentText());

                if (query_sqlitedb->exec())
                {
                    int iteratorcanevol = 0;
                    QString FullLine = "<!DOCTYPE html><html><head><title>Liste des conversations</title><style>.top{background-image: url('imgs/haut-message-rec.png');width: 298px;height: 40px;margin-left: 9px;}.middle{background-image: url('imgs/haut-millieu-rec.png');margin-left: 9px;width: 298px;}.bas{background-image: url('imgs/haut-ba-rec.png');height: 40px;width: 307px;}.top-up{background-image: url('imgs/haut-message-send.png');width: 298px;height: 40px;}.bas-up{background-image: url('imgs/haut-ba-send.png');height: 40px;width: 307px;margin-left: 1px;}.midle-up{background-image: url('imgs/haut-millieu-send.png');width: 298px;}.sender{text-align: right; margin-left: 60%;position: relative;}</style></head><body>";
                    int x = 3;
                    int x2 = 31;
                    int totallines = 0;

                    while(query_sqlitedb->next())
                    {

                        if ( query_sqlitedb->value(x2) == "0")
                        {
                            QString toAppend = "<div><div class='top'></div><div class='middle'><div style='margin-left: 20px;margin-right:10px ;'>"  + query_sqlitedb->value(x).toString() + "</div></div><div class='bas'></div></div>";
                            qDebug() <<  "deux :" << query_sqlitedb->value(x).toString() ;
                            FullLine += toAppend;
                            iteratorcanevol++;
                            totallines++;

                        }
                        else
                        {
                            QString ToAppend = "<div class='sender'><div class='top-up'></div><div class='midle-up'><div style='margin-right: 20px;margin-left:10px ;'>"+ query_sqlitedb->value(x).toString() + "</div></div><div class='bas-up'></div></div>";
                            qDebug() << query_sqlitedb->value(x).toString() ;
                            FullLine += ToAppend;
                            iteratorcanevol++;
                            totallines++;


                        }

                        ui->Progress->setValue(iteratorcanevol);

                    }
                    FullLine += "</body></html>";

                    ui->widget->hide();
                    qDebug() << totallines;
                    QTextStream outstream(&htmlFile);
                    outstream << FullLine;

                }
                else
                {
                    QMessageBox::critical(this, "Erreur", "Impossile d'ourvire la base ... querry \n" + query_sqlitedb->lastError().text());

                }
            }
        }
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
