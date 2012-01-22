#include "globals.h"
#include "qmlutils.h"
#include <QtCore>

QmlUtils::QmlUtils(QObject *parent) :
    QObject(parent)
{
}

void QmlUtils::setObjectProperty(QObject * object, QString property, QVariant value) {
  //object->setProperty(property.toAscii(), value);
  qDebug() << object;
}

void QmlUtils::test() {
  qDebug() << "QmlUtils::test()";
}

void QmlUtils::debugObject(QVariant o) {
  qDebug() << o.type() << ": " << o;
  //if(o.canConvert(QVariant::QObject*)) {
  QObject * obj = o.value< QObject* >();

  if(obj) {
    qDebug() << o.value< QObject* >();
    //}

    QList<QByteArray> prop = obj->dynamicPropertyNames();
    foreach(QByteArray a, prop) {
      qDebug() << "  " << a << ": " << obj->property(a);
    }
  }
}


ScriptObjectWrapper::ScriptObjectWrapper(QObject * object) : QObject(object->parent()) {
  thisObject = object;
}

bool ScriptObjectWrapper::invoke(const char * methodName, QGenericReturnArgument returnValue, QGenericArgument val0, QGenericArgument val1, QGenericArgument val2, QGenericArgument val3, QGenericArgument val4, QGenericArgument val5, QGenericArgument val6, QGenericArgument val7, QGenericArgument val8, QGenericArgument val9) const {
  int i = thisObject->metaObject()->indexOfMethod(methodName);
  return thisObject->metaObject()->method(i).invoke(thisObject, returnValue, val0, val1, val2, val3, val4, val5, val6, val7, val8, val9);
}
