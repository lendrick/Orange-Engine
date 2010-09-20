#ifndef RPGSCRIPT_H
#define RPGSCRIPT_H

#include <QtCore>

struct RPGScript
{
    RPGScript(int c, QString s);

    int condition;
    QString script;
};

#endif // RPGSCRIPT_H
