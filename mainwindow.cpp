#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->txt_Path->setText(QString(getenv("HOME")).append("/opensnap"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setScreensToAuto(){
    ui->spi_Screens->setEnabled(false);
}

void MainWindow::setScreensToManuel(){
    ui->spi_Screens->setEnabled(true);
}

void MainWindow::openFolder(){
    QString dir = QFileDialog::getExistingDirectory(this, "Open", ui->txt_ConfigFiles->text(), NULL);
    ui->txt_ConfigFiles->setText(dir);
}

void MainWindow::openFolder2(){
    QString dir = QFileDialog::getExistingDirectory(this, "Open", ui->txt_Path->text(), NULL);
    ui->txt_Path->setText(dir);
}

void MainWindow::syncOffset(int i){
    ui->sli_Offset->setValue(i);
    ui->spi_Offset->setValue(i);
}

void MainWindow::execute(){
    if(!ui->txt_Path->text().isEmpty()){
        QString exe = ui->txt_Path->text() + "/bin/opensnap ";

        if(!ui->txt_ConfigFiles->text().isEmpty()){
            exe.append("-c ");
            exe.append(ui->txt_ConfigFiles->text() + " ");
        }

        exe.append("-o ");
        exe.append(QString("%1").arg(ui->sli_Offset->value()) + " ");

        if(ui->rad_ScreensManuel->isChecked()){
            exe.append("-s ");
            exe.append(QString("%1").arg(ui->spi_Screens->value()) + " ");
        }

        exe.append("-d");

        if(system(NULL)){
            system(exe.toStdString().data());
            QMessageBox::information(this, "Folgender Befehl wurde ausgeführt:", exe);
            this->close();
        } else {
            QMessageBox::information(this, "Fehler", "Prozess kann nicht gestartet werden. Versuch es nochmal.");
        }
    } else {
        QMessageBox::information(this, "Fehler", "Path nicht angegeben");
    }

}

void MainWindow::cancel(){
    this->close();
}
