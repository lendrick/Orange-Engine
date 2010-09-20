#include "rpgscript.h"
#include "globals.h"
#include <QtCore>

RPGScript::RPGScript(int c, QString s) {
  condition = c;
  script = s;
};

QString RPGScript::toXml(int indent) {
  QString output;

  for(int i = 0; i < indent; i++) output += " ";
  output += "<script condition='";
  output += QString::number(condition);
  output += "'><![CDATA[";
  QString s = script;
  escapeCData(s);
  output += s.toAscii().data();
  output += "]]></script>\n";

  return output;
}
