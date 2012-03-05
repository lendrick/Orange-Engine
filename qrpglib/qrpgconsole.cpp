#include <QtGui>
#include "qrpgconsole.h"
#include "outlinestyle.h"
#include "globals.h"
#include <QVBoxLayout>


QRPGConsole::QRPGConsole(QWidget * parent) : QFrame(parent) {
  OutlineStyle * outlineStyle = new OutlineStyle();
  currentHistoryItem = -1;

  setContentsMargins(0, 0, 0, 0);
  QVBoxLayout * layout = new QVBoxLayout();
  layout->setContentsMargins(0, 0, 0, 0);
  setLayout(layout);
  
  history = new QTextEdit();
  history->setReadOnly(true);
  layout->addWidget(history);
  
  lineEdit = new QLineEdit();
  //lineEdit->setMinimumHeight(20);
  //lineEdit->setMaximumHeight(20);
  layout->addWidget(lineEdit);
  
  setStyle(outlineStyle);
  setStyleSheet(
    "QFrame {"
      "background-color: rgba(255, 255, 255, 0%);"
      "border-style: none;"
    "}"
    
    "QTextEdit, QLineEdit {"
      "background-color: rgba(0, 0, 0, 20%);"
      "font-size: 14px;"
      "border-style: none;"
      "font-weight: normal;"
      "color: white;"
     // "font-family: Monospace, Lucida Console;"
    "} "
    
    "QScrollBar:vertical, QScrollBar::add-line:vertical, "
    "QScrollBar::sub-line:vertical {"
      "border-style: none;"
      "background-color: rgba(0, 0, 0, 40%);"
    "} "
    
    "QScrollBar::handle:vertical {"
      "border-style: none;"
      "background-color: rgba(255, 255, 255, 40%);"
      "min-height: 20px;"
    "} "
    
    "QScrollBar::vertical {"
      "padding: 25px 0px 25px 0px;"
      "width: 25px;"
    "}"
    
    "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
      "background-color: rgba(128, 128, 128, 40%);"
    "} "
    
    "QLineEdit {"
      "background-color: rgba(0, 0, 0, 50%);"
      //"border: 1px solid rgba(0, 0, 0, 40%);"
    "} "
  );

  connect(lineEdit, SIGNAL(returnPressed()), this, SLOT(execute()));
}

QTextEdit * QRPGConsole::getHistory() {
  return history;
}

QLineEdit * QRPGConsole::getLineEdit() {
  return lineEdit;
}

void QRPGConsole::append(QString s) {
  history->append(s);
}

void QRPGConsole::clear() {
  history->clear();
  lineEdit->clear();
}

void QRPGConsole::execute() {
  currentHistoryItem = -1;
  if(lineEdit->text().length() > 0) {
    history->append("> " + lineEdit->text());
    commandHistory.append(lineEdit->text());
    scriptEngine->evaluate(lineEdit->text());
    if(scriptEngine->hasUncaughtException()) 
      cprint(scriptEngine->uncaughtException().toString());
    lineEdit->clear();
  }
}

void QRPGConsole::keyPressEvent(QKeyEvent * e) {
  if(e->key() == Qt::Key_Up) {
    if(currentHistoryItem == -1) {
      currentHistoryItem = commandHistory.size() - 1;
    } else if (currentHistoryItem > 0) {
      currentHistoryItem--;
    }
    e->accept();
  } else if(e->key() == Qt::Key_Down) {
    if(currentHistoryItem >= commandHistory.size() - 1) {
      currentHistoryItem = -1;
    } else if(currentHistoryItem >= 0) {
      currentHistoryItem++;
    }
    e->accept();
  } else {
    e->ignore();
  }
  
  if(e->isAccepted()) {
    if(currentHistoryItem > -1) 
      lineEdit->setText(commandHistory[currentHistoryItem]);
    else 
      lineEdit->clear();
  }
}
