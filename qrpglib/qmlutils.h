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

#endif // QMLUTILS_H
