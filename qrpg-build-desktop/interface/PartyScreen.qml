import Qt 4.7
import "PartyScreen.js" as PartyScreenScript

HideShowContainer {
  id: partyScreen
  x: 200
  y: 0
  width: 440
  height: 480
  state: "Show"
  Component.onCompleted: PartyScreenScript.startUp();
  property int selectedIndex

  function selectedCharacter() {
    return PartyScreenScript.characterScreens[selectedIndex].character;
  }

  function setCurrentPartyMember(index) {
    console.log("set party member to " + index)
    characterSelect.setPartyMember(index);
    console.log("showing character screen " + index)
    PartyScreenScript.characterScreens[index].show();
    selectedIndex = index;
    console.log("setting party member to " + selectedCharacter().name);
  }

  function setPartyMember(i, character) {
    PartyScreenScript.characterScreens[i].setPartyMember(character);
  }

  function addPartyMember(character) {
    utils.debugObject(character);
    console.log("adding character to menu: " + character.name);

    var scr = PartyScreenScript.newCharacterScreen(this);
    console.log("1");
    scr.setPartyMember(character);
    console.log("2");
    PartyScreenScript.characterScreens.push(scr);

    var currentIndex = PartyScreenScript.characterScreens.length - 1;
    console.log("adding character to select row");
    characterSelect.addPartyMember(character, currentIndex);
    console.log("character added to menu")
  }

  Box {
    id: characterSelect
    objectName: "characterSelect"
    width: 440
    height: 100
    x: 0
    y: 0
    state: "Show"

    Rectangle {
      width: 50
      height: 50
      visible: (PartyScreenScript.menuItems.length > 0)
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

      property alias selectedIndex: partyScreen.selectedIndex;
      property int selectedPos: x + PartyScreenScript.menuItems[partyScreen.selectedIndex].x + PartyScreenScript.menuItems[partyScreen.selectedIndex].width/2

      function setOptions(options) {
        for(var o in options) {
          addOption(o);
        }
      }

      function addOption(portrait, object) {
        console.log("adding menu image " + portrait);
        var item = PartyScreenScript.ImageMenuItemComponent.createObject(portraitMenu);
        console.log("1");
        item.source = portrait;
        console.log("2");
        item.opacity = 1;
        console.log("3 object " + object);
        item.object = object;
        console.log("4");
        addItem(item);
        console.log("5");
      }

      function addItem(item) {
        console.log("addItem " + item);
        item.index = PartyScreenScript.menuItems.length;
        console.log("adding ITEM " + item.index);
        PartyScreenScript.menuItems.push(item);
        console.log("item added");
        for(var i in PartyScreenScript.menuItems) {
          console.log(SimpleMenuScript.menuItems[i].opacity);
        }
      }

      function getItems() {
        return PartyScreenScript.menuItems;
      }

      function removeItem(index) {

      }

      function clear() {

      }

      function getSelectedItem() {

      }

      function setSelectedIndex(i) {
        console.log("setSelectedIndex " + i);
        PartyScreenScript.menuItems[selectedIndex].deselect();
        PartyScreenScript.menuItems[i].select();
        selectedIndex = i;
        selected(i);
      }

      signal selected();
    }


    function addPartyMember(character, index) {
      console.log("adding portrait menu option " + index + ": " + character.name)
      portraitMenu.addOption(character.portrait,
        PartyScreenScript.characterScreens[index]);
    }

    function setPartyMember(index) {
      console.log("setting characterSelect to " + index);
      selectedIndex = index;
    }
  }

}
