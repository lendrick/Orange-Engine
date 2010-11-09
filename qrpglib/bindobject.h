#ifndef BINDOBJECT_H
#define BINDOBJECT_H

#include <QtCore>
#include <QtScript>
#include <QtDeclarative>

typedef QDeclarativePropertyMap* QDeclarativePropertyMapPtr;

class BindObject : public QObject, public QScriptClass
{
  Q_OBJECT
public:
  BindObject(QScriptEngine *engine);
  QueryFlags queryProperty ( const QScriptValue & object, const QScriptString & name, QueryFlags flags, uint * id );
  void setProperty ( QScriptValue & object, const QScriptString & name, uint id, const QScriptValue & value );
  QScriptValue property ( const QScriptValue & object, const QScriptString & name, uint id );
  //QScriptClassPropertyIterator * newIterator ( const QScriptValue & object );

private:

signals:

public slots:

};

QScriptValue bindObjectToScriptValue(QScriptEngine *eng, const QDeclarativePropertyMapPtr &pm);
void bindObjectFromScriptValue(const QScriptValue &obj, QDeclarativePropertyMapPtr &pm);

QScriptValue bindObjectConstructor(QScriptContext * context, QScriptEngine * engine);

#endif // BINDOBJECT_H
