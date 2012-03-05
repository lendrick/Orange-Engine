#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H 1

#include <QtGui>
#include <QDialog>
#include <QLineEdit>

class NewProjectDialog : public QDialog {
  Q_OBJECT
public:
  NewProjectDialog(QWidget * parent);
  QLineEdit * projectname;
public slots:
  void submit();
  int exec();
};

#endif
