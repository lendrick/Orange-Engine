#ifndef NEWMAPDIALOG_H
#define NEWMAPDIALOG_H 1

#include <QtGui>
#include <QDialog>
#include <QComboBox>
#include <QLineEdit>

class NewMapDialog : public QDialog {
  Q_OBJECT
public:
  NewMapDialog(QWidget * parent);
  QComboBox * tileset;
  QLineEdit * mapname;
public slots:
  int exec();
  void submit();
};

#endif
