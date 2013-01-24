#ifndef ACTION_H
#define ACTION_H

#include <QVector>
#include "parameter.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>

class Action
{
private:
    QString path;
    QVector<Parameter*> paras;
    QString genarateExecuteString();
public:
    Action();
    void addOpenSnapPath(QString path);
    void addParameter(QString,QString);
    void clear();
    bool executeDaemon();
    bool saveAsScript();
};

#endif // ACTION_H
