import Qt 4.7
import "SimpleMenu.js" as SimpleMenuScript

Column {
  id: simpleMenu
  //color: '#444444'

  Component.onCompleted: SimpleMenuScript.startUp();
  property int selectedIndex: 0;

  function setOptions(options) {
    for(var o in options) {
      addOption(o);
    }
  }

  function addOption(option) {
    //console.log("adding menu option " + option)
    var item = SimpleMenuScript.SimpleMenuItemComponent.createObject(simpleMenu);
    item.text = option;
    item.opacity = 1;
    addItem(item);
  }

  function addItem(item) {
    item.index = SimpleMenuScript.menuItems.length;
    //console.log("adding ITEM " + item.index);
    SimpleMenuScript.menuItems.push(item);
    for(var i in SimpleMenuScript.menuItems) {
      //console.log(SimpleMenuScript.menuItems[i].opacity);
    }
  }

  function getItems() {
    return SimpleMenuScript.menuItems;
  }

  function removeItem(index) {

  }

  function clear() {

  }

  function getSelectedItem() {

  }

  function setSelectedIndex(i) {
    SimpleMenuScript.menuItems[selectedIndex].deselect();
    SimpleMenuScript.menuItems[i].select();
    selectedIndex = i;
    selected(i);
  }

  signal selected();
}
