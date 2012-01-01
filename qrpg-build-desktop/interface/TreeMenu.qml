import Qt 4.7
import "TreeMenu.js" as TreeMenuScript

Item {
  id: treeMenuContainer;
  property alias box: menuBox;

  property string selectSound;
  property bool canCancel: true
  property string optionName: 'root'
  property bool isSubMenu: false

  function show() {
    menuBox.show();
    mouseArea.enabled = true;
  }

  function hide() {
    menuBox.hide();
    mouseArea.enabled = false;
  }

  function close() {
    menuBox.hide();
    console.log("closing tree menu: " + optionName);
    treeMenuContainer.destroy(300);
  }

  MouseArea {
    id: mouseArea;
    x: mapFromItem(ui, 0, 0).x
    y: mapFromItem(ui, 0, 0).y
    z: 999;
    enabled: false
    width: ui.width
    height: ui.height
    onClicked: {
      console.log('click');
      if(parent.canCancel) parent.close();
    }
    onPressed: {
      console.log('click');
      if(parent.canCancel) parent.close();
    }
  }

  Box {
    id: menuBox
    height: treeMenu.height + 50
    width: treeMenu.width + 50
    z: 1000
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
      var item = TreeMenuScript.TreeMenuNodeComponent.createObject(treeMenu);
      item.subMenu = TreeMenuScript.TreeMenuComponent.createObject(item);
      item.text = option;
      item.opacity = 1;
      item.subMenu.setOptions(object['$value']);
      item.subMenu.optionName = option;
      item.subMenu.isSubMenu = true;
      item.subMenu.anchors.left = item.right;
      item.subMenu.anchors.top = item.top;
      console.log(option + ": " + item.subMenu);
      addItem(item);
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
    if(TreeMenuScript.menuItems[selectedIndex].subMenu) {
      return TreeMenuScript.menuItems[selectedIndex].subMenu.getSelectedItem();
    } else {
      return TreeMenuScript.menuItems[selectedIndex].object;
    }
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
    if(isSubMenu) {
      parent.setSelected();
    }
  }

  signal selected();
}
