#include "action.h"

Action::Action()
{
    screens = 0;
}

//Setter###########################################################################################
void Action::setOpenSnapPath(QString path){
    this->openSnapPath = path;
}

void Action::setConfigPath(QString path){
    this->configPath = path;
}

void Action::setEnableSnapping(bool top, bool bottom, bool left, bool right){
    this->top = top;
    this->bottom = bottom;
    this->left = left;
    this->right = right;
}

void Action::setOffset(int offset){
    this->offset = offset;
}

void Action::setNumberOfScreens(int number){
    this->screens = number;
}

//Getter###########################################################################################
QString Action::getOpenSnapPath(){
    return this->openSnapPath;
}

QString Action::getConfigPath(){
    return this->configPath;
}

bool Action::getTop(){
    return this->top;
}

bool Action::getBottom(){
    return this->bottom;
}

bool Action::getLeft(){
    return this->left;
}

bool Action::getRight(){
    return right;
}

int Action::getOffset(){
    return this->offset;
}

int Action::getNumberOfScreens(){
    return screens;
}

//Public Methods###################################################################################
QString Action::executeDaemon(){
    QString exe = this->genarateExecuteString();
    enableSnapping(Edge::TOP, this->top);
    enableSnapping(Edge::BOTTOM, this->bottom);
    enableSnapping(Edge::LEFT, this->left);
    enableSnapping(Edge::RIGHT, this->right);

    if(system(NULL)){
        int ok = system(exe.toStdString().data());
        return exe;
    } else {
        return NULL;
    }
}

QString Action::saveAsScript(QString dir){
    QString exe = this->genarateExecuteString();

    QFile f(dir);
    if(f.open(QIODevice::WriteOnly)){
        QTextStream out(&f);

        out << "#!/bin/sh" << endl;
        out << exe << endl;

        f.close();
        return exe;
    }
    return NULL;
}

bool Action::save(QString path){
    QFile f(path);
    if(f.open(QIODevice::WriteOnly)){
        QTextStream out(&f);
        out << "#Profile File for OpenSnap GUI" << endl;
        out << "openSnapPath=" + this->openSnapPath << endl;
        out << "configPath=" + this->configPath << endl;
        out << "edge.top=" + QString(this->top?"1":"0") << endl;
        out << "edge.bottom=" + QString(this->bottom?"1":"0") << endl;
        out << "edge.left=" + QString(this->left?"1":"0") << endl;
        out << "edge.right=" + QString(this->right?"1":"0") << endl;
        out << "offset=" + QString::number(this->offset) << endl;
        out << "screens=" + QString::number(this->screens);
        f.close();
        return true;
    }
    return false;
}

bool Action::load(QString path){
    QFile f(path);
    if(f.open(QIODevice::ReadOnly)){
        QTextStream in(&f);
        while(!in.atEnd()){
            QString line = in.readLine();
            if(line != NULL && line.at(0) != '#'){
                QStringList values = line.split("=");
                QString key = values.at(0);
                QString value = values.at(1);
                QStringList options;
                options << "openSnapPath" << "configPath" << "edge.top" << "edge.bottom" << "edge.left" << "edge.right" << "offset" << "screens";
                switch(options.indexOf(key)){
                    case 0:
                        this->setOpenSnapPath(value.trimmed());
                        break;
                    case 1:
                        this->setConfigPath(value.trimmed());
                        break;
                    case 2:
                        this->top = (value == "1");
                        break;
                    case 3:
                        this->bottom = (value == "1");
                        break;
                    case 4:
                        this->left = (value == "1");
                        break;
                    case 5:
                        this->right = (value == "1");
                        break;
                    case 6:
                        this->setOffset(value.toInt());
                        break;
                    case 7:
                        this->setNumberOfScreens(value.toInt());
                        break;
                }
            }
        }
        f.close();
        return true;
    }
    return false;
}

//Private Helper###################################################################################
QString Action::genarateExecuteString(){
    QVector<Parameter*> paras;
    paras.push_back(new Parameter("-c", this->configPath));
    paras.push_back(new Parameter("-o", QString::number(this->offset)));
    if(this->screens > 0) paras.push_back(new Parameter("-s", QString::number(this->screens)));
    paras.push_back(new Parameter("-d", ""));

    QString exe = "";
    exe.append(this->openSnapPath + " ");

    for(int i = 0; i < paras.size(); i++){
        exe.append(paras.at(i)->getName() + " " + paras.at(i)->getValue() + " ");
    }

    return exe;
}

/**
 * Enable or disable the snapping function of opensnap.
 * It just rename the file. So opensnap can not find the file and so it does nothing.
 *
 * @brief Action::enableSnapping
 * @param side
 * @param enable
 * @return bool
 */
bool Action::enableSnapping(int edge, bool enable){
    QString filename;
    switch(edge){
        case Edge::TOP:
            filename = "hit_top"; break;
        case Edge::BOTTOM:
            filename = "hit_bottom"; break;
        case Edge::LEFT:
            filename = "hit_left"; break;
        case Edge::RIGHT:
            filename = "hit_right"; break;
    }

    bool isEnabled = false;
    QString filepath = this->configPath + "/" + filename;
    if(enable){
        QFile file(filepath + ".disable");
        if(file.exists()){
            isEnabled = file.rename(filepath);
        }
    } else {
        QFile file(filepath);
        if(file.exists()){
            isEnabled = file.rename(filepath + ".disable");
        }
    }
    return isEnabled;
}
