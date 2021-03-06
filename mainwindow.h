#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QAction>
#include "action.h"

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
    void setScreensToAuto();
    void setScreensToManuel();
    void openFolder();
    void openFolderPath();
    void execute();
    void cancel();
    void syncOffset(int i);
    void saveAsScript();
    void saveProfile();
    void loadProfile();
    void info(QAction*);

private:
    bool openSnapIsInPath();
    bool validateInput();
    void setOpenSnapConfig();

    Ui::MainWindow *ui;
    QString homevar;
    Action action;
};

#endif // MAINWINDOW_H
