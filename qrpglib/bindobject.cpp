#include "bindobject.h"

#include <QtCore>
#include <QtScript>
#include <QtDeclarative>

Q_DECLARE_METATYPE(BindObject*)
Q_DECLARE_METATYPE(QDeclarativePropertyMapPtr)

BindObject::BindObject(QScriptEngine *engine)
  : QObject(engine), QScriptClass(engine)
{
  qScriptRegisterMetaType<QDeclarativePropertyMapPtr>(engine, bindObjectToScriptValue, bindObjectFromScriptValue);
}

QScriptClass::QueryFlags BindObject::queryProperty
  (const QScriptValue & object, const QScriptString & name, QueryFlags flags, uint * id)
{
  return QScriptClass::HandlesReadAccess|QScriptClass::HandlesWriteAccess;
}

void BindObject::setProperty
  (QScriptValue & object, const QScriptString & name, uint id, const QScriptValue & value)
{
  QDeclarativePropertyMapPtr m = qscriptvalue_cast< QDeclarativePropertyMapPtr >(object.data());

  qDebug() << "setProperty " << name.toString() << " " << value.toVariant();

  if(m) {
    (*m)[name] = value.toVariant();
  }
}

QScriptValue BindObject::property
  (const QScriptValue & object, const QScriptString & name, uint id)
{
  QDeclarativePropertyMapPtr m = qscriptvalue_cast< QDeclarativePropertyMapPtr >(object.data());

  qDebug() << "get property " << name.toString() << (*m)[name];
  QScriptValue q = engine()->newVariant((*m)[name]);
  qDebug() << q.toString();
  qDebug() << "done";

  if(!m)
    return QScriptValue();

  if(m->contains(name)) {
    return engine()->newVariant((*m)[name]);
  } else {
    return QScriptValue();
  }
}

//QScriptClassPropertyIterator * newIterator ( const QScriptValue & object );

QScriptValue bindObjectToScriptValue(QScriptEngine *eng, const QDeclarativePropertyMapPtr &pm) {
  QScriptValue ctor = eng->globalObject().property("BindObject");
  BindObject *cls = qscriptvalue_cast<BindObject *>(ctor.data());
  if (!cls)
      return eng->newVariant(qVariantFromValue(pm));

  return eng->newObject(new BindObject(eng), eng->newVariant(qVariantFromValue(pm)));
}

void bindObjectFromScriptValue(const QScriptValue &obj, QDeclarativePropertyMapPtr &pm) {
  pm = qvariant_cast< QDeclarativePropertyMap* >(obj.data().toVariant());
}

QScriptValue bindObjectConstructor(QScriptContext * context, QScriptEngine * engine) {
  try {
    QDeclarativePropertyMapPtr object = new QDeclarativePropertyMap();
    BindObject * bind = new BindObject(engine);
    return engine->newObject(bind, engine->newVariant(qVariantFromValue(object)));
  } catch(QString s) {
    return context->throwError(s);
  }
}
