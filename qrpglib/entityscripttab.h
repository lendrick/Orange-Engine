#ifndef ENTITYSCRIPTTAB_H
#define ENTITYSCRIPTTAB_H

#include "scripttab.h"
class EntityDialog;

class CoordinateWidget : public QFrame {
  Q_OBJECT
public:
  CoordinateWidget(QWidget * parent = 0, int nx = 0, int ny = 0);
  QSpinBox * x;
  QSpinBox * y;
};

class EntityScriptTab : public ScriptTab
{
  Q_OBJECT
  friend class EntityDialog;
public:
  EntityScriptTab(int condition = 0, QString script = "", bool defCoords = true,
            int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0);

signals:

public slots:

protected:
  QCheckBox * useDefaultBoundingBox;
  CoordinateWidget * c1;
  CoordinateWidget * c2;
};

#endif // ENTITYSCRIPTTAB_H
