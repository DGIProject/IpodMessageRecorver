#include "ipodrecorvermain.h"
#include "ui_ipodrecorvermain.h"
#include "ipodconversationrecorvermainwindowsapp.h"
#include "ipodrecorverconversationsubsrib.h"
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <QtSql>
#include <QtGui>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <QCryptographicHash>
#include <QByteArray>
#include <QString>
#include <QFile>

using namespace std;

IpodRecorverMain::IpodRecorverMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IpodRecorverMain)
{
    ui->setupUi(this);
    IpodRecorverMain::connectToBdd();
}

void IpodRecorverMain::connectToBdd()
{

     db = QSqlDatabase::addDatabase("QMYSQL");
     db.setHostName("mysql2.alwaysdata.com");
     db.setUserName("loquii");
     db.setPassword("lemondeducraft");
     db.setDatabaseName("loquii_base");
     query_base = new QSqlQuery(db);


}

void IpodRecorverMain::disconnectFromBdd()
{
    db.close();

}

void IpodRecorverMain::ConnectToService()
{

    ofstream fichier_ident("ident.txt", ios::out | ios::trunc); // ouverture en écriture avec effacement du fichier ouvert
       ifstream verif_ident("ident.txt", ios::in); // on ouvre

       if (ui->IdentLine->text() == "" || ui->PasswordLine->text() == "")
           {

           }
           else
           {



           QString mdp = ui->PasswordLine->text();
           string pseudo_con = ui->IdentLine->text().toStdString();
           QByteArray ba = QCryptographicHash::hash(mdp.toUtf8(), QCryptographicHash::Sha1); // on la hache
           QString mdp_hache=ba.toHex(); // on convertit le hash en QString
             if (db.open())
               {

                       query_base->prepare("SELECT * FROM user WHERE pseudo=:pseudo");
                       query_base->bindValue(":pseudo", ui->IdentLine->text().toUtf8());

                       if(query_base->exec())
                       {
                           while(query_base->next())
                                      {

                                          for(int x=0; x < 1; ++x)
                                          {
                                              if (fichier_ident)
                                              {
                                                  fichier_ident << query_base->record().value("pseudo").toString().toStdString() << ' ' << query_base->record().value("password").toString().toStdString() << ' ' << query_base->record().value("email").toString().toStdString();


                                              }
                                              else
                                              {
                                                  QMessageBox::critical(this,"Erreur",tr("Impossible de créer certain fichier !"));
                                              }

                                          }
                                      }

                               fichier_ident.close();

                                if(verif_ident)
                                   {
                                       string mdp_fichier, pseudo_fichier;
                                       verif_ident >> pseudo_fichier >> mdp_fichier;

                                       if(mdp_fichier == "" || pseudo_fichier == "")
                                           {
                                                QMessageBox::critical(this,"Erreur",tr("Vous n'etes pas inscrit !\n Code erreur 1"));
                                           }
                                       else
                                           {

                                                   if (mdp_hache.toStdString() == mdp_fichier && pseudo_con == pseudo_fichier)
                                                        {

                                                            //QMessageBox::critical(this, "Erreur","ok");
                                                            IpodConversationRecorverMainWindowsApp *b = new IpodConversationRecorverMainWindowsApp(this, db);
                                                                                b->show();

                                                        }
                                                   else
                                                   {
                                                       QMessageBox::critical(this, "Erreur",tr("Votre identifiant ou mot de passe est incorect\nVous etes peut etre pas encore inscrit !\n Code erreur 1"));

                                                   }

                                               verif_ident.close();


                                           }

                                       }
                                       else
                                       {
                                               QMessageBox::critical(this,"Erreur",tr("Une erreur est présente, merci de contacter le developpeur\n Code erreur 3"));
                                       }
                  db.close();

               }
               else
               {
                   QMessageBox::critical(this,"Erreur",tr("Une erreur est présente, merci de contacter le developpeur\n Code erreur 3"));
               }

  // QFile fichier("ident.txt");
   db.close();
           }
   }

}

void IpodRecorverMain::on_ConnectButton_clicked(){

    IpodRecorverMain::ConnectToService();

}

void IpodRecorverMain::on_SubscribButton_clicked()
{
     IpodRecorverConversationSubsrib *subscribWindows = new IpodRecorverConversationSubsrib(this, db);
                        subscribWindows->show();

}

IpodRecorverMain::~IpodRecorverMain()
{
    delete ui;
}
