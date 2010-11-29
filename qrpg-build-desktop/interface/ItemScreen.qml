import Qt 4.7
import "ItemScreen.js" as ItemScreenScript

Box {
  objectName: "itemScreen"
  id: itemScreen
  state: "Hide"
  //property alias inv: inventoryListContainer.inventoryList
  Component.onCompleted: ItemScreenScript.startUp();
  property bool inBattle;
  property Item itemSlot;
  property string test: 'still testing';

  function doTest() {
    console.log("itemScreen testing");
  }

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
    //dumpInventory();

    /*
    while(ItemScreenScript.invList.length > 0) {
      var x = ItemScreenScript.invList.pop();
      x.item = null;
      x.destroy();
    }
    */

    for(var i in inventory) {
      if(inventory[i]) {
        var name;
        try {
          name = inventory[i].name;
        } catch(e) {
          name = '';
        }
        if(name && !inventory[i].deleted) {
          if(!ItemScreenScript.invList[i] || !rpgx.same(ItemScreenScript.invList[i].item, inventory[i])) {
            var item = ItemScreenScript.invItemComponent.createObject(inventoryListContainer.inv);
            item.item = inventory[i];
            //console.log(typeof(item.item));
            item.x = (i % 2) * inventoryListContainer.inv.width / 2;
            item.y = Math.floor(i / 2) * item.height;
            item.invIndex = i;
            ItemScreenScript.invList[i] = item;
          }
        } else {
          inventory[i] = null;
          if(ItemScreenScript.invList[i]) ItemScreenScript.invList[i].deleteObject();
          ItemScreenScript.invList[i] = null;
        }
      }
    }
    console.log("updateInventory finished");
  }
}
