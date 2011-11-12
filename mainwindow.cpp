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

    std::string user = m_authComponents->UserText->text().toStdString();
    std::string key = m_authComponents->KeyText->text().toStdString();

    SIT_DEV("AUTHENTIFICATION") << "user: "<< user << " key: " << key;


}

void MainWindow::authenticationConfirmed()
{
    SIT_DEBUG("authentificationConfirmed");

    if(m_authComponents->UserText->text().isEmpty())
    {
        m_authComponents->statusLabel->setStyleSheet("QLabel { color: red ; }");
        m_authComponents->statusLabel->setText("You forgot to enter your User-Name");
        return;
    }

    if(m_authComponents->KeyText->text().isEmpty())
    {
        m_authComponents->statusLabel->setStyleSheet("QLabel { color: red ; }");
        m_authComponents->statusLabel->setText("You forgot to enter your Secret-Key");
        return;
    }
    m_authComponents->statusLabel->setText("User OK");
    m_authComponents->statusLabel->setStyleSheet("QLabel { color: black ; }");
    m_authComponents->statusLabel->setText("Please enter your User-Name and Secrete-Key");
}


MainWindow::~MainWindow()
{
    SIT_WARN("HALLO TEST") << "New LogFile";

    delete m_components;
    delete m_authComponents;
    delete m_authDialog;

}
