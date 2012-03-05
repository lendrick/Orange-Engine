#ifndef QRPGCONSOLE_H
#define QRPGCONSOLE_H 1

#include <QtGui>
#include <QTextEdit>
#include <QLineEdit>
#include <QFrame>

class QRPGConsole : public QFrame {
  Q_OBJECT
public:
  QRPGConsole(QWidget * parent = 0);
  QTextEdit * getHistory();
  QLineEdit * getLineEdit();
public slots:
  void append(QString s);
  void clear();
  void execute();
private:
  QTextEdit * history;
  QLineEdit * lineEdit;
  QStringList commandHistory;
  int currentHistoryItem;
  void keyPressEvent(QKeyEvent * e);
};

#endif
