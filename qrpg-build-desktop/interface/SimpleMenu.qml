import Qt 4.7
import "SimpleMenu.js" as SimpleMenuScript

Item {
  id: simpleMenu
  Component.onCompleted: SimpleMenuScript.startUp();

  function setItems(items) {
    SimpleMenuScript.menuItems = items;
  }

  function addItem(item) {
    SimpleMenuScript.menuItems.push(item);
  }

  function getItems() {
    return SimpleMenuScript.menuItems;
  }

  function removeItem(index) {

  }

  function clear() {

  }

  signal selected();
}
