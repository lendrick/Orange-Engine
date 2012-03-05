#include <QtGui>
#include <QFileDialog>
#include "filebrowser.h"

FileBrowser::FileBrowser(QString filter, QWidget * parent) : QFrame(parent) {
  init(filter);
}

FileBrowser::FileBrowser(QString filter, const QString & contents, QWidget * parent) : QFrame(parent) {
  init(filter);
  fileName->setText(contents);
}

void FileBrowser::init(QString filter) {
  setContentsMargins(0, 0, 0, 0);
  fileName = new QLineEdit;
  browseButton = new QPushButton("Browse");
  layout = new QHBoxLayout;
  setLayout(layout);
  layout->setContentsMargins(0, 0, 0, 0);
  this->filter = filter;
  
  layout->addWidget(fileName);
  layout->addWidget(browseButton);
  
  connect(browseButton, SIGNAL(clicked()), this, SLOT(browse()));
}

void FileBrowser::setText(QString t) {
  fileName->setText(t);
}

FileBrowser::~FileBrowser() {
  delete fileName;
  delete browseButton;
}

QString FileBrowser::text() const {
  return fileName->text();
}

void FileBrowser::browse() {
  fileName->setText(QFileDialog::getOpenFileName(0, "Select file", ".", filter));
}

void FileBrowser::clear() {
  fileName->clear();
}
