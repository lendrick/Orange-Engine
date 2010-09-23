#ifndef ENTITYSCRIPTTAB_H
#define ENTITYSCRIPTTAB_H

#include "scripttab.h"
class EntityDialog;
class CoordinateWidget;

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
