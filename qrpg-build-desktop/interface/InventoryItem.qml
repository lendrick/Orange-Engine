import Qt 4.7

Item {
  id: invItem
  property Item item
  height: 34
  property alias text: txt.text
  width: parent.width / 2

  onItemChanged: if(item) text = item.name;

  Image {
    id: img
    source: if(item) item.portrait; else '';
  }

  SmallText {
    id: txt
    anchors.left: img.right
    anchors.verticalCenter: img.verticalCenter
    width: parent.width / 2;
    wrapMode: Text.NoWrap
  }

  MouseArea {
    id: mouseArea
    anchors.fill: parent;
    onClicked: invItem.displayMenu(mouse);
    z: 50
  }

  function displayMenu(e) {
    var options = new Object();
    var tree = flatTree(characters);
    console.log(serialize(tree));
    var menu = ui.treeMenu(ui.popups, tree);
    menu.x = x + e.x;
    menu.y = y + e.y;
    //menu.z = 200;
    menu.callback = invItem;
    console.log("show menu");
    menu.show();
  }

  function treeSelect(i) {
    console.log("treeSelect: " + i.name);
    item.activateUseAbility(i, Array(i));
    itemScreen.updateInventory();
    //console.log(serialize(i));
  }
}
