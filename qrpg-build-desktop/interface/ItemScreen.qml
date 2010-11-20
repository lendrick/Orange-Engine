import Qt 4.7
import "ItemScreen.js" as ItemScreenScript

Box {
  objectName: "itemScreen"
  id: itemScreen
  state: "Hide"
  //property alias inv: inventoryListContainer.inventoryList
  Component.onCompleted: ItemScreenScript.startUp();

  onStateChanged: {
    if(state == "Show")
      updateInventory();
  }

  Item {
    id: inventoryListContainer
    x: 25
    y: 25
    height: parent.height - 50
    width: parent.width - 50
    property alias inv: inventoryList;

    clip: true

    Item {
      id: inventoryList
      width: parent.width
      //height: children.height;
    }
  }

  function updateInventory() {
    console.log("updateInventory");
    dumpInventory();
    while(ItemScreenScript.invList.length > 0) {
      var x = ItemScreenScript.invList.pop();
      x.item = null;
      x.destroy();
    }

    for(var i in inventory) {
      var item = ItemScreenScript.invItemComponent.createObject(inventoryListContainer.inv);

      item.item = inventory[i];

      if(inventory[i] && !inventory[i].destroyed())
        console.log(i + ": " + inventory[i].name);
      else
        console.log(i + ": null");

      item.x = (i % 2) * inventoryListContainer.inv.width / 2;
      item.y = Math.floor(i / 2) * item.height;
      ItemScreenScript.invList.push(item);
    }

  }
}
