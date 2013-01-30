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
    QString openSnapPath;
    QString configPath;
    bool top,bottom,left,right;
    int offset;
    int screens;    //0 = autodetected

    QString genarateExecuteString();
    bool enableSnapping(int side, bool enable);

public:
    Action();
    //Setter
    void setOpenSnapPath(QString path);
    void setConfigPath(QString path);
    void setEnableSnapping(bool top, bool bottom, bool left, bool right);
    void setOffset(int offset);
    void setNumberOfScreens(int number);
    //Getter
    QString getOpenSnapPath();
    QString getConfigPath();
    bool getTop();
    bool getBottom();
    bool getLeft();
    bool getRight();
    int getOffset();
    int getNumberOfScreens();

    //Methods
    QString executeDaemon();
    QString saveAsScript(QString dir);

    //Save an Load a Profile
    bool save(QString path);
    bool load(QString path);
};

#endif // ACTION_H
