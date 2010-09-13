#ifndef NEWBITMAPDIALOG_H
#define NEWBITMAPDIALOG_H 1

#include <QtGui>
#include "filebrowser.h"

class NewBitmapDialog : public QDialog {
  Q_OBJECT
public:
  NewBitmapDialog(QWidget * parent);
  QSpinBox * xspin;
  QSpinBox * yspin;
  FileBrowser * image;
  QLineEdit * bitmapname;
public slots:
  void submit();
  int exec();
};

#endif
