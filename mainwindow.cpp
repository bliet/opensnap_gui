#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->homevar = QString(getenv("HOME"));
    QString path = this->homevar + QString("/opensnap/");
    if(QFile::exists(path)){
        ui->txt_Path->setText(path);
    } else {
        ui->txt_Path->setText(this->homevar);
    }
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

void MainWindow::openFolderPath(){
    QString dir = QFileDialog::getExistingDirectory(this, "Open", ui->txt_Path->text(), NULL);
    ui->txt_Path->setText(dir);
}

void MainWindow::syncOffset(int i){
    ui->sli_Offset->setValue(i);
    ui->spi_Offset->setValue(i);
}

void MainWindow::execute(){
    this->fillParameterList();
    this->action.executeDaemon();
}

void MainWindow::saveAsScript(){
    this->fillParameterList();
    this->action.saveAsScript();
}

void MainWindow::fillParameterList(){
    this->action.clear();
    if(!ui->txt_Path->text().isEmpty()){
        this->action.addOpenSnapPath(ui->txt_Path->text() + "bin/opensnap ");

        if(!ui->txt_ConfigFiles->text().isEmpty()){
            this->action.addParameter("-c", ui->txt_ConfigFiles->text());
        }

        this->action.addParameter("-o", QString("%1").arg(ui->sli_Offset->value()));

        if(ui->rad_ScreensManuel->isChecked()){
            this->action.addParameter("-s", QString("%1").arg(ui->spi_Screens->value()));
        }

        this->action.addParameter("-d", "");
    } else {
        QMessageBox::information(this, "Error", "Path empty");
    }
}

void MainWindow::cancel(){
    this->close();
}
