#include "mainwindow.h"
#include "ui_mainwindow.h"


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

    //connect(components->actionLog_In, S)



}



MainWindow::~MainWindow()
{
    delete components;
}
