#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>

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
    void openFolder2();
    void execute();
    void cancel();
    void syncOffset(int i);
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
