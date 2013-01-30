#include "action.h"

Action::Action()
{
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
