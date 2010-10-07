#ifndef LAYERDIALOG_H
#define LAYERDIALOG_H

#include <QtGui>
#include "map.h"

class LayerDialog : public QDialog {
  Q_OBJECT
public:
  LayerDialog(Map::Layer * l, QWidget * parent);
  QSpinBox * xspin;
  QSpinBox * yspin;
  QCheckBox * wrapcheck;
  QLineEdit * layername;
  Map::Layer * layer;
public slots:
  int exec();
  void submit();
};

#endif // LAYERDIALOG_H
