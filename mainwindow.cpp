#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->homevar = QString(getenv("HOME"));

    QString path;
    if(openSnapIsInPath()){
        path = "opensnap";
    } else {
        path = this->homevar;
        if(QFile::exists(path + "/opensnap/")){
            path += QString("/opensnap/");
        }
    }
    ui->txt_Path->setText(path);

    if(QFile::exists(path + "sample_configs/")){
        ui->txt_ConfigFiles->setText(path + "sample_configs/");
    } else {
        ui->txt_ConfigFiles->setText(path);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::openSnapIsInPath()
{
    bool isInPath = false;
    QString path = QString(getenv("PATH"));
    QStringList pathList = path.split(":");
    foreach (QString var, pathList) {
        if(var.endsWith("opensnap/bin")){
            isInPath = true;
        }
    }
    return isInPath;
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
        //adding parameter for the command
        this->setOpenSnapConfig();

        //execute the command to start OpenSnap
        QString exe = this->action.executeDaemon();
        if(exe==NULL){
            QMessageBox::information(this, "Error", "Could not execute the command.");
        } else {
            QMessageBox::information(this, "Nice", "Command executed: " + exe);
        }
    } else {
        QMessageBox::information(this, "Input", "Validation failed.");
    }
}

void MainWindow::saveAsScript(){
    if(this->validateInput()){
        this->setOpenSnapConfig();
        QMessageBox::information(this, "Information", "Snap-Options will be ignored in the file");
        QString dir = QFileDialog::getSaveFileName(NULL, "Open", this->homevar, NULL, NULL, NULL);
        QString exe = this->action.saveAsScript(dir);
        if(exe==NULL){
            QMessageBox::information(this, "Error", "Could not save the file.");
        } else {
            QMessageBox::information(this, "Nice", "File saved. Content: " + exe);
        }
    } else {
        QMessageBox::information(this, "Input", "Validation failed.");
    }
}

void MainWindow::setOpenSnapConfig(){
    //Set path to OpenSnap (or the Command for opensnap)
    this->action.setOpenSnapPath(ui->txt_Path->text() + "bin/opensnap ");
    //Set path to the config files
    this->action.setConfigPath(ui->txt_ConfigFiles->text());

    //enable or disable snapping function for each edge
    this->action.setEnableSnapping(
                ui->che_Top->isChecked(),
                ui->che_Bottom->isChecked(),
                ui->che_Left->isChecked(),
                ui->che_Right->isChecked()
                );

    //Set Offset
    this->action.setOffset(ui->sli_Offset->value());

    //Set number of screens, if checked
    if(ui->rad_ScreensManuel->isChecked()){
        this->action.setNumberOfScreens(ui->spi_Screens->value());
    } else {
        this->action.setNumberOfScreens(0);
    }
}

bool MainWindow::validateInput(){
    bool a = ui->txt_Path->text().isEmpty();
    bool b = ui->txt_ConfigFiles->text().isEmpty();
    return (!a && !b);
}

void MainWindow::saveProfile(){
    this->setOpenSnapConfig();
    QString filepath = QFileDialog::getSaveFileName(this, "Save", this->homevar, NULL, NULL, NULL);
    bool ok = this->action.save(filepath);
    if(ok){
        QMessageBox::information(this, "Nice", "Profile saved");
    } else {
        QMessageBox::information(this, "Error","Could not save the file. Try again.");
    }
};

void MainWindow::loadProfile(){
    QString filepath = QFileDialog::getOpenFileName(this, "Open", this->homevar, NULL, NULL, NULL);
    bool ok = this->action.load(filepath);
    if(ok){
        ui->txt_Path->setText(this->action.getOpenSnapPath());
        ui->txt_ConfigFiles->setText(this->action.getConfigPath());

        if(this->action.getNumberOfScreens()==0){
            ui->rad_ScreensAuto->setChecked(true);
            ui->spi_Screens->setEnabled(false);
        } else {
            ui->rad_ScreensManuel->setChecked(true);
            ui->spi_Screens->setValue(this->action.getNumberOfScreens());
        }

        ui->spi_Offset->setValue(this->action.getOffset());

        ui->che_Top->setChecked(this->action.getTop());
        ui->che_Bottom->setChecked(this->action.getBottom());
        ui->che_Left->setChecked(this->action.getLeft());
        ui->che_Right->setChecked(this->action.getRight());

        QMessageBox::information(this, "Nice", "Profile loaded");
    } else {
        QMessageBox::information(this, "Error","Could not load the file. Try again.");
    }
};

void MainWindow::info(QAction *a){
    /*TODO: Comming soon*/
}

void MainWindow::cancel(){
    this->close();
}
