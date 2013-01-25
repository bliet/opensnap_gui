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
    path.append("sample_configs/");
    if(QFile::exists(path)){
        ui->txt_ConfigFiles->setText(path);
    } else {
        ui->txt_ConfigFiles->setText(this->homevar);
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
    if(this->validateInput()){
        //enable or disable snapping function for each edge
        this->action.addConfigPath(ui->txt_ConfigFiles->text());
        this->action.enableSnapping(Edge::TOP, ui->che_Top->isChecked());
        this->action.enableSnapping(Edge::BOTTOM, ui->che_Bottom->isChecked());
        this->action.enableSnapping(Edge::LEFT, ui->che_Left->isChecked());
        this->action.enableSnapping(Edge::RIGHT, ui->che_Right->isChecked());

        //adding parameter for the command
        this->fillParameterList();

        //execute the command to start OpenSnap
        QString exe = this->action.executeDaemon();
        if(exe==NULL){
            QMessageBox::information(this, "Error", "Could not execute the command.");
        } else {
            QMessageBox::information(this, "Nice", "Command executed.");
        }
    } else {
        QMessageBox::information(this, "Input", "Validation failed.");
    }
}

void MainWindow::saveAsScript(){
    if(this->validateInput()){
        this->fillParameterList();
        QMessageBox::information(this, "Information", "Snap-Options will be ignored in the file");
        QString dir = QFileDialog::getSaveFileName(NULL, "Open", this->homevar, NULL, NULL, NULL);
        QString exe = this->action.saveAsScript(dir);
        if(exe==NULL){
            QMessageBox::information(this, "Error", "Could not save the file");
        } else {
            QMessageBox::information(this, "Nice", "File saved.");
        }
    } else {
        QMessageBox::information(this, "Input", "Validation failed.");
    }
}

void MainWindow::info(QAction *a){
    /*Comming soon*/
}

void MainWindow::fillParameterList(){
    this->action.clear();

    this->action.addOpenSnapPath(ui->txt_Path->text() + "bin/opensnap ");

    if(!ui->txt_ConfigFiles->text().isEmpty()){
        this->action.addParameter("-c", ui->txt_ConfigFiles->text());
    }

    this->action.addParameter("-o", QString("%1").arg(ui->sli_Offset->value()));

    if(ui->rad_ScreensManuel->isChecked()){
        this->action.addParameter("-s", QString("%1").arg(ui->spi_Screens->value()));
    }

    this->action.addParameter("-d", "");
}

bool MainWindow::validateInput(){
    bool a = ui->txt_Path->text().isEmpty();
    bool b = ui->txt_ConfigFiles->text().isEmpty();
    return (!a && !b);
}

void MainWindow::cancel(){
    this->close();
}
