#include "action.h"

Action::Action()
{
}

void Action::addOpenSnapPath(QString path){
    this->path = path;
}

void Action::addParameter(QString name, QString value){
    Parameter *p = new Parameter();
    p->setName(name);
    p->setValue(value);
    this->paras.push_back(p);
}

bool Action::executeDaemon(){
    QString exe = this->genarateExecuteString();
    if(system(NULL)){
        int ok = system(exe.toStdString().data());
        QMessageBox::information(NULL, "Folgender Befehl wurde ausgeführt:", exe);
        return true;
    } else {
        QMessageBox::information(NULL, "Fehler", "Prozess kann nicht gestartet werden. Versuch es nochmal.");
        return false;
    }
}

bool Action::saveAsScript(){
    QString exe = this->genarateExecuteString();
    QString dir = QFileDialog::getSaveFileName(NULL, "Open", this->path, NULL, NULL, NULL);

    QFile f(dir);
    if(f.open(QIODevice::WriteOnly)){
        QTextStream out(&f);

        out << "#!/bin/sh" << endl;
        out << exe << endl;

        f.close();
        return true;
    }
    return false;
}

QString Action::genarateExecuteString(){
    QString exe = "";
    exe.append(path + " ");

    for(int i = 0; i < paras.size(); i++){
        exe.append(paras.at(i)->getName() + " " + paras.at(i)->getValue() + " ");
    }

    return exe;
}

void Action::clear(){
    paras.clear();
}
