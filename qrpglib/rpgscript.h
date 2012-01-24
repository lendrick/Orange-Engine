#ifndef RPGSCRIPT_H
#define RPGSCRIPT_H

#include <QtCore>

class RPGScript
{
public:
    RPGScript(int c, QString s);
    QString toXml(int indent = 0);
    int condition;
    QString script;
};

#endif // RPGSCRIPT_H
