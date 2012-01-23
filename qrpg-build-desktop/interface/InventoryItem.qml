import Qt 4.7
import "InventoryItem.js" as InventoryItemScript;

HideShowContainer {
  id: invItem
  property Item item
  height: 34
  property alias text: txt.text
  property alias color: txt.color
  width: parent.width / 2
  state: "Show"
  property int invIndex
  property bool usable
  Component.onCompleted: InventoryItemScript.startUp();

  onItemChanged: {
    if(item) {
      text = item.name;

      if(!itemScreen.itemSlot) {
        var useAbility = item.getUseAbility();
        if(!itemScreen.inBattle) {
          if(useAbility && useAbility.useOutsideBattle) {
            color = '#fff';
            usable = true;
          } else {
            color = '#999';
            usable = false;
          }
        } else {
          if(useAbility && useAbility.useInBattle) {
            color = '#fff';
            usable = true;
          } else {
            color = '#999';
            usable = false;
          }
        }
      } else {
        if(itemScreen.itemSlot.canEquip(item)) {
          color = '#fff';
          usable = true;
        } else {
          color = '#999';
          usable = false;
        }
      }
    }
  }

  Image {
    id: img
    source: if(item) item.portrait; else '';
  }

  SmallText {
    id: txt
    anchors.left: img.right
    anchors.verticalCenter: img.verticalCenter
    width: parent.width / 2;
    wrapMode: Text.NoWrap;
  }

  MouseArea {
    id: mouseArea
    anchors.fill: parent;
    onClicked: {
      sfx.menublip.play();
      if(!itemScreen.itemSlot) {
        invItem.displayMenu(mouse);
      } else {
        itemScreen.itemSlot.equip(item);
        itemScreen.hide();
        modalItemScreen.destroy(500);
      }
    }

    z: 50
    hoverEnabled: true;
    visible: invItem.usable;

    onEntered: {
      console.log("hover enter " + invItem.text.color);
      invItem.color = "#ff2";
    }

    onExited: {
      console.log("hover exit");
      invItem.color = "#fff";
    }
  }

  function displayMenu(e) {
    var options = new Object();
    var tree = flatTree(characters);
    var menu = ui.treeMenu(ui.popups, tree, invItem);
    menu.x = x + e.x;
    menu.y = y + e.y;
    console.log("show menu");
    menu.show();
  }

  function treeSelect(i) {
    console.log("treeSelect: " + i.name);
    item.activateUseAbility(i, Array(i));
    itemScreen.updateInventory();
    //console.log(serialize(i));
  }

  function deleteObject() {
    state = "Hide";
    invItem.destroy(300);
  }


}
