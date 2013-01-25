#ifndef ACTION_H
#define ACTION_H

#include <QVector>
#include "parameter.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include "edge.h"

class Action
{
private:
    QString path;
    QString configPath;
    QVector<Parameter*> paras;
    QString genarateExecuteString();
    bool top,bottom,left,right;
public:
    Action();
    void addOpenSnapPath(QString path);
    void addConfigPath(QString path);
    void enableSnapping(int side, bool enable);
    void addParameter(QString,QString);
    void clear();
    QString executeDaemon();
    QString saveAsScript(QString dir);
};

#endif // ACTION_H
