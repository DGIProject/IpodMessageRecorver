#include "ipodrecorverconversationsubsrib.h"
#include "ui_ipodrecorverconversationsubsrib.h"
#include <QtGui>
#include <QCryptographicHash>
#include <QByteArray>

using namespace std;

IpodRecorverConversationSubsrib::IpodRecorverConversationSubsrib(QWidget *parent, QSqlDatabase db) :
    QMainWindow(parent),
    ui(new Ui::IpodRecorverConversationSubsrib)
{
    ui->setupUi(this);
    db_subscrib = db;
    query_subscrib = new QSqlQuery(db_subscrib);
}

void IpodRecorverConversationSubsrib::on_CanceBtn_clicked()
{
    IpodRecorverConversationSubsrib::close();
}
void IpodRecorverConversationSubsrib::on_ValidBtn_clicked()
{
    if (ui->InputPseudo->text().count() >= 4)
    {
        if (ui->InputMdp->text() == ui->InputMdpConf->text() && ui->InputMdp->text().count() >= 4)
        {
            if (ui->InputAge->text().toInt() >= 7)
            {
                if (ui->InputEmail->text().count() >=2)
                {
                    QRegExp mailExp ("^[\\w|\\.]+@[\\w]+\\.[\\w]{2,4}$");
                    if (ui->InputEmail->text().contains(mailExp))
                    {
                        QString mdp_nohach = ui->InputMdp->text().toUtf8();
                        QByteArray ba = QCryptographicHash::hash(mdp_nohach.toUtf8(), QCryptographicHash::Sha1);
                        QString mdp_hache = ba.toHex();

                        if(db_subscrib.open())
                        {
                            query_subscrib->prepare("SELECT COUNT(pseudo) as nbpseudo FROM user WHERE pseudo=:pseudo");
                            query_subscrib->bindValue(":pseudo", ui->InputPseudo->text());
                            if (query_subscrib->exec())
                            {
                                QString exist;
                                while(query_subscrib->next())
                                {
                                    for(int x=0; x < query_subscrib->record().count(); ++x)
                                    {
                                        exist = query_subscrib->record().value("nbpseudo").toString();
                                    }
                                }
                                if (exist.toInt() > 1)
                                {
                                    QMessageBox::critical(this, "erreur", "Ce pseudo est deja pris");
                                }
                                else
                                {
                                    query_subscrib->prepare("INSERT INTO user(id, email, pseudo, age, mdp, modelName, rang) values('',:email, :pseudo,:age,:mdp,:modelName, 'normale')  ");
                                    query_subscrib->bindValue(":pseudo", ui->InputPseudo->text());
                                    query_subscrib->bindValue(":age", ui->InputAge->text());
                                    query_subscrib->bindValue(":email", ui->InputEmail->text());
                                    query_subscrib->bindValue(":modelName", ui->InputModelName->currentText());
                                    query_subscrib->bindValue(":mdp", mdp_hache);

                                    if (!query_subscrib->exec())
                                    {
                                        QMessageBox::critical(this, "erreur", "impossible d'executer la requette");
                                    }
                                    else
                                    {
                                        QMessageBox::information(this, "Inscription reussi !", "L'inscription au service s'est deroule avec succes. \n cette fenetre va se fermer puis vous pourrez vous connecter.");
                                        IpodRecorverConversationSubsrib::close();
                                    }
                                }
                            }
                            else
                            {
                                QMessageBox::critical(this, "erreur", "impossible d'executer la requette");

                            }


                        }
                    }
                    else
                    {
                        QMessageBox::critical(this, "erreur", "Votre adresse n'a pas une forme Valide.");
                    }
                }
                else
                {
                    QMessageBox::critical(this, "erreur", "Un email de deux carracteres n'existe pas !");
                }
            }
            else
            {
                QMessageBox::critical(this, "erreur", "Veuillez donner un age realiste");
            }
        }
        else
        {
            QMessageBox::critical(this, "erreur", "les mot de passe ne sont pas identique\nVotre mot de passe est peut etre trop court, Verrifiez qu'il fasse au moin 5 carracteres");
        }
    }
    else
    {
        QMessageBox::critical(this, "erreur", "Le pseudo que vous avez choisi est trop court");
    }
}

IpodRecorverConversationSubsrib::~IpodRecorverConversationSubsrib()
{
    delete ui;
}
