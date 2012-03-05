#ifndef PROPERTYEDITOR_H
#define PROPERTYEDITOR_H

#include <QtGui>
#include <QDialog>
#include <QTableWidget>
#include "entity.h"

class PropertyEditor : public QDialog
{
  Q_OBJECT
public:
  PropertyEditor(ObjectPointer o, QWidget *parent = 0);

protected:
  ObjectPointer object;
  QTableWidget * tableWidget;

signals:

public slots:
  int exec();
  void submit();

};

#endif // PROPERTYEDITOR_H
