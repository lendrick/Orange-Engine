import QtQuick 1.0
import "BaseItem.js" as BaseItemScript

Item {
  id: baseItem

  Component.onCompleted: BaseItemScript.startUp();

  function attr(name, val) {
    if(val === undefined) {
      return BaseItemScript.attributes[name];
    } else {
      BaseItemScript.attributes[name] = val;
      attrChanged(name, val);
    }
  }

  signal attrChanged(string name, variant val)
}
