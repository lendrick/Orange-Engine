import Qt 4.7
import "TreeMenu.js" as TreeMenuScript

Item {
  id: treeMenuContainer;
  property alias box: menuBox;

  property string selectSound;
  property bool canCancel: true

  function show() {
    menuBox.show();
  }

  function hide() {
    menuBox.hide();
  }

  function close() {
    menuBox.hide();
    treeMenuContainer.destroy(300);
  }

  MouseArea {
    x: 0
    y: 0
    width: ui.width
    height: ui.height
    onClicked: { if(parent.canCancel) parent.close(); }
  }

  Box {
    id: menuBox
    height: treeMenu.height + 50
    width: treeMenu.width + 50
    //anchors.centerIn: parent
    //anchors.fill: parent
    Column {
      id: treeMenu
      x: 25
      y: 25
    }
  }

  //color: '#444444'

  Component.onCompleted: TreeMenuScript.startUp();
  property variant selectedItem
  property variant callback
  property int selectedIndex
  property bool popup: false
  onSelectedItemChanged: itemSelected(selectedItem);

  function itemSelected(i) {
    if(popup) {
      close();
    }
  }

  function setOptions(options) {
    for(var o in options) {
      addOption(o, options[o]);
    }
    console.log("options set");
  }

  function addOption(option, object) {
    //console.log("adding menu option " + option)
    if(object['$treetype'] == 'node') {
      // Add a child menu and call setOptions on it
    } else {
      var item = TreeMenuScript.TreeMenuItemComponent.createObject(treeMenu);

      item.text = option;
      item.opacity = 1;
      item.object = object['$value'];
      addItem(item);
    }
  }

  function addItem(item) {
    item.index = TreeMenuScript.menuItems.length;
    //console.log("adding ITEM " + item.index);
    TreeMenuScript.menuItems.push(item);
  }

  function getItems() {
    return TreeMenuScript.menuItems;
  }

  function removeItem(index) {

  }

  function clear() {

  }

  function getSelectedItem() {
    return TreeMenuScript.menuItems[selectedIndex].object;
  }

  function setSelectedIndex(i) {
    //console.log("ITEMS: " + serialize(TreeMenuScript.menuItems));
    TreeMenuScript.menuItems[selectedIndex].deselect();
    TreeMenuScript.menuItems[i].select();
    selectedIndex = i;
    selectedItem = TreeMenuScript.menuItems[i].object;
    if(callback && callback.treeSelect)
      callback.treeSelect(selectedItem);
    selected(i);
    close();
  }

  signal selected();
}
