#ifndef FILEBROWSER_H
#define FILEBROWSER_H 1

#include <QtGui>
#include <QHBoxLayout>
#include <QFrame>
#include <QLineEdit>
#include <QPushButton>

class FileBrowser : public QFrame {
  Q_OBJECT
public:
  FileBrowser(QString filter = "", QWidget * parent = 0);
  FileBrowser(QString filter, const QString & contents, QWidget * parent = 0);
  ~FileBrowser();
  QString text() const;
  void setText(QString t);
private:
  void init(QString filter);
  QLineEdit * fileName;
  QPushButton * browseButton;
  QHBoxLayout * layout;
  QString filter;
public slots:
  void browse();
  void clear();
};
  
#endif
