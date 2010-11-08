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
