#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <string.h>
#include "ui_loginUser.h"

namespace Ui {
    class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    bool authenticationConfirmed();

signals:
    void openAtuhenticationDialog();


private:
    Ui::MainWindow * m_components;
    Ui_Dialog * m_authComponents;
    QDialog * m_authDialog;
};


#endif // MAINWINDOW_H
