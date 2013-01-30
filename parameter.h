#ifndef PARAMETER_H
#define PARAMETER_H

#include <QString>

class Parameter
{
private:
    QString name;
    QString value;
public:
    Parameter(QString n, QString v) { name = n; value = v; };
    QString getName() { return name; };
    void setName(QString n) { name = n; };
    QString getValue() { return value; };
    void setValue(QString v) { value= v; };
};

#endif // PARAMETER_H
