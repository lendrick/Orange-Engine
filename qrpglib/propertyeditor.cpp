#include "propertyeditor.h"
#include "entity.h"
#include <QtGui>

PropertyEditor::PropertyEditor(ObjectPointer o, QWidget *parent) :
    QDialog(parent)
{
  object = o;
  tableWidget = new QTableWidget(0, 2);
  QVBoxLayout * layout = new QVBoxLayout(this);
  layout->addWidget(tableWidget);

  foreach(const QByteArray & p, object->dynamicPropertyNames()) {
    int r = tableWidget->rowCount();
    tableWidget->insertRow(r);
    tableWidget->setItem(r, 0, new QTableWidgetItem(QString(p)));
    tableWidget->setItem(r, 1, new QTableWidgetItem(object->property(p).toString()));
  }
}

int PropertyEditor::exec() {
}

void PropertyEditor::submit() {
}
