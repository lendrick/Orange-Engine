#ifndef NEWLAYERDIALOG_H
#define NEWLAYERDIALOG_H 1

#include <QtGui>
#include <QCheckBox>
#include <QDialog>
#include <QSpinBox>
#include <QLineEdit>

class NewLayerDialog : public QDialog {
  Q_OBJECT
public:
  NewLayerDialog(QWidget * parent);
  QSpinBox * xspin;
  QSpinBox * yspin;
  QCheckBox * wrapcheck;
  QLineEdit * layername;
public slots:
  int exec();
  void submit();
};

#endif
