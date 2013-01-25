#include "action.h"

Action::Action()
{
}

void Action::addOpenSnapPath(QString path){
    this->path = path;
}

void Action::addConfigPath(QString path){
    this->configPath = path;
}

void Action::addParameter(QString name, QString value){
    Parameter *p = new Parameter();
    p->setName(name);
    p->setValue(value);
    this->paras.push_back(p);
}

QString Action::executeDaemon(){
    QString exe = this->genarateExecuteString();
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

QString Action::genarateExecuteString(){
    QString exe = "";
    exe.append(path + " ");

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
 */
void Action::enableSnapping(int side, bool enable){
    QString filename;
    switch(side){
        case Edge::TOP:
            filename = "hit_top"; break;
        case Edge::BOTTOM:
            filename = "hit_bottom"; break;
        case Edge::LEFT:
            filename = "hit_left"; break;
        case Edge::RIGHT:
            filename = "hit_right"; break;
    }

    QString filepath = this->configPath + "/" + filename;
    if(enable){
        QFile file(filepath + ".disable");
        if(file.exists()){
            file.rename(filepath);
        }
    } else {
        QFile file(filepath);
        if(file.exists()){
            file.rename(filepath + ".disable");
        }
    }
}

void Action::clear(){
    paras.clear();
}
