#include "mainwindow.h"

#include "ui_mainwindow.h"

#include "core/sitLog.h"
#include "qpalette.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_components(new Ui::MainWindow),
    m_authComponents(new Ui_Dialog),
    m_authDialog(new QDialog())
{
    m_authComponents->setupUi(m_authDialog);

    m_components->setupUi(this);
    m_components->actionLog_In->setEnabled(true);
    m_components->actionLog_Out->setEnabled(false);
    m_components->actionDecrypt_File->setEnabled(false);
    m_components->actionEncrypt_File->setEnabled(false);
    m_components->actionShare_Key->setEnabled(false);


    connect(this, SIGNAL(openAtuhenticationDialog()), m_authDialog , SLOT(open()) );
    connect(m_authComponents->pushButton, SIGNAL(clicked()),this, SLOT(authenticationConfirmed()));


    openAtuhenticationDialog();
}



bool MainWindow::authenticationConfirmed()
{
    SIT_DEBUG << "AUTHENTICATION";

    if(m_authComponents->UserText->text().isEmpty())
    {
        m_authComponents->statusLabel->setStyleSheet("QLabel { color: red ; }");
        m_authComponents->statusLabel->setText("You forgot to enter your User-Name");
        return false;
    }

    if(m_authComponents->KeyText->text().isEmpty())
    {
        m_authComponents->statusLabel->setStyleSheet("QLabel { color: red ; }");
        m_authComponents->statusLabel->setText("You forgot to enter your Secret-Key");
        return false;
    }

    std::string user = m_authComponents->UserText->text().toStdString();
    std::string userKey = m_authComponents->KeyText->text().toStdString();

    if(false /*!m_userList->exist(user)*/)
    {
        m_authComponents->statusLabel->setStyleSheet("QLabel { color: red ; }");
        m_authComponents->statusLabel->setText("The User dose not exist");
        return false;
    }

    std::string userKeyHash;

    if(false /*!m_userList->getHashValue(user, userKeyHash)*/)
    {
        SIT_ERROR << "NO HASH VALUE FOUND FOR USER: " << user;
        m_authComponents->statusLabel->setStyleSheet("QLabel { color: red ; }");
        m_authComponents->statusLabel->setText("Authentication Problems (Hash-Value)");
        return false;
    }

    if(false /*!m_hash->compare(userKeyHash,userKey) */)
    {
        SIT_ERROR << "COMPAE HASH VALUE FAILE FOR USER: " << user;
        m_authComponents->statusLabel->setStyleSheet("QLabel { color: red ; }");
        m_authComponents->statusLabel->setText("Authentication Problems (Hash-Value)");
        return false;
    }

    m_authComponents->statusLabel->setText("User OK");
    m_authComponents->statusLabel->setStyleSheet("QLabel { color: black ; }");
    m_authComponents->statusLabel->setText("Please enter your User-Name and Secrete-Key");
    m_authDialog->close();

    SIT_DEBUG("AUTHENTIFICATION") << "user: "<< user << " key: " << true;
    return true;

}


MainWindow::~MainWindow()
{
    delete m_components;
    delete m_authComponents;
    delete m_authDialog;
}
