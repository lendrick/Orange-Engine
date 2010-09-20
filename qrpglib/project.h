#ifndef PROJECT_H
#define PROJECT_H 1

#include <QtCore>

class Project : public QObject {
  Q_OBJECT
public:
  Project(QString projname = "");
  ~Project();
  void SetName(QString projname);
  void Load(QString filename);
  void Save(QString filename);
private:
  QString name;
signals:
  void UpdateName(QString);
};

#endif
