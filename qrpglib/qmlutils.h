#ifndef QMLUTILS_H
#define QMLUTILS_H

#include <QObject>
#include <QtCore>

class QmlUtils : public QObject
{
  Q_OBJECT
public:
  explicit QmlUtils(QObject *parent = 0);

signals:

public slots:
  void setObjectProperty(QObject * object, QString property, QVariant value);
  void test();
  void debugObject(QVariant o);
};

class ScriptObjectWrapper : public QObject
{
  Q_OBJECT
public:
  QObject * thisObject;

  ScriptObjectWrapper(QObject * object);
  bool invoke (const char * methodName, QGenericReturnArgument returnValue, QGenericArgument val0 = QGenericArgument( 0 ), QGenericArgument val1 = QGenericArgument(), QGenericArgument val2 = QGenericArgument(), QGenericArgument val3 = QGenericArgument(), QGenericArgument val4 = QGenericArgument(), QGenericArgument val5 = QGenericArgument(), QGenericArgument val6 = QGenericArgument(), QGenericArgument val7 = QGenericArgument(), QGenericArgument val8 = QGenericArgument(), QGenericArgument val9 = QGenericArgument() ) const;
};

#endif // QMLUTILS_H
