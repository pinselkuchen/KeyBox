#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sitLog.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    components(new Ui::MainWindow)
{
    components->setupUi(this);
    components->actionLog_In->setEnabled(true);
    components->actionLog_Out->setEnabled(false);
    components->actionDecrypt_File->setEnabled(false);
    components->actionEncrypt_File->setEnabled(false);
    components->actionShare_Key->setEnabled(false);
}


MainWindow::~MainWindow()
{
    SIT_WARN("HALLO TEST") << "New LogFile";

    delete components;

}
