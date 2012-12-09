#include "ipodconversationrecorvermainwindowsapp.h"
#include "ui_ipodconversationrecorvermainwindowsapp.h"
#include <QtGui>
#include "helpwindows.h"
#include "tohtmldialog.h"

IpodConversationRecorverMainWindowsApp::IpodConversationRecorverMainWindowsApp(QWidget *parent, QSqlDatabase db) :
    QMainWindow(parent),
    ui(new Ui::IpodConversationRecorverMainWindowsApp)
{
    ui->setupUi(this);
    db_windwso2 = db;
    query_windows2 = new QSqlQuery(db_windwso2);
    sqlitedb = QSqlDatabase::addDatabase("QSQLITE", "dateFile");
    query_sqlitedb = new QSqlQuery(sqlitedb);


    ui->widget->hide();
    ui->ContactList->hide();
    ui->ConversationView->hide();
    ui->lableConvPres->hide();
    ui->labelContenu->hide();
    ui->actionTo_html_format->setEnabled(false);


}

void IpodConversationRecorverMainWindowsApp::getUserInfo()
{

}

void IpodConversationRecorverMainWindowsApp::on_actionTo_html_format_triggered()
{
    ToHtmlDialog *htmldialog = new ToHtmlDialog(this, sqlitedb);
    htmldialog->show();
}

void IpodConversationRecorverMainWindowsApp::on_actionChoose_the_file_triggered()
{
    QString path_toFile = QFileDialog::getOpenFileName(this,"Ouvrir");
    QFile file(path_toFile);

    if (file.fileName().contains(".db", Qt::CaseInsensitive))
    {
        IpodConversationRecorverMainWindowsApp::VerifyFile(path_toFile);
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Pour focntionner le format doit etre .db");
        ui->actionTo_html_format->setEnabled(false);
    }


}


void IpodConversationRecorverMainWindowsApp::VerifyFile(QString db_file)
{
    sqlitedb.setDatabaseName(db_file);
    int valid = 0;
    if (sqlitedb.open())
    {
        query_sqlitedb->clear();
        query_sqlitedb->prepare("SELECT * FROM madrid_chat;");

        if (query_sqlitedb->exec())
        {
            valid = 0;
            query_sqlitedb->prepare("SELECT * FROM message;");
            if (query_sqlitedb->exec())
            {
                valid = 0;
                query_sqlitedb->prepare("SELECT * FROM group_member;");
                if (query_sqlitedb->exec())
                {
                    valid = 0;
                    query_sqlitedb->prepare("SELECT * FROM madrid_attachment;");
                    if (query_sqlitedb->exec())
                    {
                        valid = 0;
                    }
                    else
                    {
                        valid = 1;
                    }

                }
                else
                {
                    valid = 1;
                }
            }
            else
            {
                valid = 1;
            }
        }
        else
        {
            valid = 1;
        }

    }
    if (valid)
    {
        QMessageBox::critical(this, "Fichier Invalide", "Le fichier que vous avez entre n'est pas utilisable !");
        ui->actionTo_html_format->setEnabled(false);
    }
    else
    {
        IpodConversationRecorverMainWindowsApp::Get_Conv_List();
        ui->textBrowser->hide();
        ui->ContactList->show();
        ui->ConversationView->show();
        ui->labelContenu->show();
        ui->lableConvPres->show();
        ui->actionTo_html_format->setEnabled(true);

    }

    sqlitedb.close();



}

void IpodConversationRecorverMainWindowsApp::Get_Conv_List()
{
    if (sqlitedb.open())
    {
        query_sqlitedb->clear();
        query_sqlitedb->prepare("SELECT * FROM madrid_chat;");

        if (query_sqlitedb->exec())
        {

            while(query_sqlitedb->next())
            {
                QVariant test2 = query_sqlitedb->value(5);
                ui->ContactList->addItem(test2.toString());
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

    sqlitedb.close();

}

void IpodConversationRecorverMainWindowsApp::on_ContactList_clicked()
{
    QString currentSelection = ui->ContactList->currentItem()->text();
    IpodConversationRecorverMainWindowsApp::GetConversations(currentSelection);
}

void IpodConversationRecorverMainWindowsApp::on_actionDonate_triggered()
{
    HelpWindows *b = new HelpWindows(this, "Don");
    b->show();
}

void IpodConversationRecorverMainWindowsApp::on_actionHelp_triggered()
{

    HelpWindows *b = new HelpWindows(this, "hel");
    b->show();

}

void IpodConversationRecorverMainWindowsApp::on_actionUpdates_triggered()
{

}

void IpodConversationRecorverMainWindowsApp::on_actionVersions_triggered()
{
    HelpWindows *b = new HelpWindows(this, "vers");
    b->show();
}


void IpodConversationRecorverMainWindowsApp::on_actionAbout_triggered()
{
    HelpWindows *b = new HelpWindows(this, "Abo");
    b->show();
}


void IpodConversationRecorverMainWindowsApp::GetConversations(QString contact)
{
    ui->widget->show();
    ui->ConversationView->clear();

    if (sqlitedb.open())
    {
        query_sqlitedb->clear();

        query_sqlitedb->prepare("SELECT COUNT(*) AS nb_field FROM message WHERE madrid_handle = ?");
        query_sqlitedb->addBindValue(contact);
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
        query_sqlitedb->addBindValue(contact);

        if (query_sqlitedb->exec())
        {
            int iteratorcanevol = 0;
            QString FullLine = " ";
            int x = 3;
            int x2 = 31;
            int totallines = 0;

            while(query_sqlitedb->next())
            {



                if ( query_sqlitedb->value(x2) == "0")
                {
                    QString toAppend = "<p>" + query_sqlitedb->value(x).toString() + "</p>";
                    qDebug() <<  "deux :" << query_sqlitedb->value(x).toString() ;
                    FullLine += toAppend;
                    iteratorcanevol++;
                    totallines++;

                }
                else
                {
                    QString ToAppend = "<p align='right'>" + query_sqlitedb->value(x).toString() + "</p>";
                    qDebug() << query_sqlitedb->value(x).toString() ;
                    FullLine += ToAppend;
                    iteratorcanevol++;
                    totallines++;


                }

                ui->Progress->setValue(iteratorcanevol);

            }
            FullLine += "</body></html>";
            ui->ConversationView->insertHtml(FullLine);
            ui->widget->hide();
            qDebug() << totallines;

        }
        else
        {
            QMessageBox::critical(this, "Erreur", "Impossile d'ourvire la base ... querry \n" + query_sqlitedb->lastError().text());

        }

    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Impossile d'ourvire la base ... \n" + query_sqlitedb->lastError().text());
    }

}

IpodConversationRecorverMainWindowsApp::~IpodConversationRecorverMainWindowsApp()
{
    delete ui;
}
