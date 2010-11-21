import Qt 4.7
import "PortraitMenu.js" as PortraitMenuScript;

Box {
  id: characterSelect
  objectName: "characterSelect"
  state: "Show"
  Component.onCompleted: PortraitMenuScript.startUp();
  property alias selectedIndex: portraitMenu.selectedIndex
  property alias showRect: rect.visible

  Rectangle {
    id: rect
    width: 50
    height: 50
    visible: false
    anchors.verticalCenter: characterSelect.verticalCenter
    border.width: 2
    border.color: '#ff2'
    radius: 6
    smooth: true
    color: Qt.rgba(1, 1, 1, 0)
    x: portraitMenu.selectedPos - width / 2

    Behavior on x {
      PropertyAnimation {
        duration: 200
        easing.type: Easing.InOutQuad
      }
    }

  }

  Row {
    id: portraitMenu
    anchors.centerIn: parent
    spacing: 40
    //color: '#444444'

    property int selectedIndex
    property int selectedPos: getSelectedPos();

    function getSelectedPos() {
      if(PortraitMenuScript.menuItems && PortraitMenuScript.menuItems[partyScreen.selectedIndex])
        return x + PortraitMenuScript.menuItems[characterSelect.selectedIndex].x +
          PortraitMenuScript.menuItems[characterSelect.selectedIndex].width/2;
      //else
        //return x;
      else
        return x;
    }

    function setOptions(options) {
      for(var o in options) {
        addOption(o);
      }
    }

    function addOption(portrait, object) {
      //console.log("adding menu image " + portrait);
      var item = PortraitMenuScript.ImageMenuItemComponent.createObject(portraitMenu);
      //console.log("1");
      item.source = portrait;
      //console.log("2");
      item.opacity = 1;
      //console.log("3 object " + object);
      item.object = object;
      //console.log("4");
      addItem(item);
      //console.log("5");
    }

    function addItem(item) {
      //console.log("addItem " + item);
      item.index = PortraitMenuScript.menuItems.length;
      //console.log("adding ITEM " + item.index);
      PortraitMenuScript.menuItems.push(item);
      //console.log("item added");
      //for(var i in PortraitMenuScript.menuItems) {
        //console.log(PortraitMenuScript.menuItems[i].opacity);
      //}
      if(PortraitMenuScript.menuItems.length > 0)
        characterSelect.showRect = true;
    }

    function getItems() {
      return PortraitMenuScript.menuItems;
    }

    function removeItem(index) {

    }

    function clear() {

    }

    function getSelectedItem() {

    }

    function setSelectedIndex(i) {
      //console.log("setSelectedIndex " + i);
      PortraitMenuScript.menuItems[selectedIndex].deselect();
      PortraitMenuScript.menuItems[i].select();
      selectedIndex = i;
      selected(i);
    }

    signal selected();
  }


  function addPartyMember(character, object) {
    //console.log("adding portrait menu option " + index + ": " + character.name)
    portraitMenu.addOption(character.portrait, object);
  }

  function setPartyMember(index) {
    //console.log("setting characterSelect to " + index);
    selectedIndex = index;
  }
}
