import Qt 4.7
import "Ui.js" as UiScript

Item {  //Item
  id: ui
  objectName: "ui"
  //color: Qt.rgba(0, 0, 0, .2);  //test only
  property string test: "testing"

  Component.onCompleted: UiScript.startUp();

  x: 0
  y: 0
  width: 640
  height: 480

  //anchors.fill: parent

  function treeMenu(parent, tree) {
    var menu = UiScript.TreeMenuComponent.createObject(popups);
    menu.setOptions(tree);
    return menu;
  }

  function newCharacter(name) {
    var c = UiScript.CharacterComponent.createObject(ui);
    c.name = name;
    return c;
  }

  function addPartyMember(character) {
    partyScreen.addPartyMember(character);
    magicScreen.addPartyMember(character);
  }

  function setPartyMember(i, character) {
    partyScreen.setPartyMember(i, character);
    Screen.setPartyMember(i, character);
  }

  function battle(enemyParty) {
    battleScreen.setParty(enemyParty);
    battleScreen.show();
    battleScreen.start();
  }

  Box {
    objectName: "talkbox"
    id: talkbox

    /*
    width: 640
    height: 168
    x: 0
    y: 480-height
    z: 0
    */

    /*
    width: parent.width
    height: 168
    x: 0
    y: parent.height - height
    */
    //anchors.fill: parent

    anchors.left: parent.left
    anchors.right: parent.right
    anchors.bottom: parent.bottom
    height: 168

    focus: true
    property list<Item> textArray

    function append(textString) {
      UiScript.appendText(textString);
    }

    function appendScript(textString, script) {
      UiScript.appendScript(textString, script);
    }

    function show() {
      state = "Show";
      UiScript.textBoxArray[0].state = "Show";
      //UiScript.textBoxArray[0].text += " " + parent.objectName;
    }

    function hide() {
      state = "Hide";
    }

    function queueSize() {
      return UiScript.textBoxArray.length;
    }

    Keys.onPressed: {
      if(state == "Show" && !event.isAutoRepeat ) {
        var object = UiScript.textBoxArray.shift();
        object.state = "Hide";
        if(object.script) eval(object.script);
        object.destroy(500);

        if(UiScript.textBoxArray.length > 0) {
          UiScript.textBoxArray[0].state = "Show";
        } else {
          state = "Hide";
        }

        event.accepted = true;
      } else if(state == "Show") {
        event.accepted = true;
      }
    }

    states: [
      State {
        name: "State2"
        PropertyChanges {
          target: talkbox
          opacity: 1
        }

        PropertyChanges {
          target: text1
          opacity: 0
        }
      }
    ]

  }

  HideShowContainer {
    objectName: "statusScreen"
    id: statusScreen

/*
    x: 0
    y: 0
    height: 640
    width: 480
  */

    anchors.fill:  parent

    state: "Hide"

    /*
    function show() {
      state = "Show";
    }

    function hide() {
      state = "Hide";
    }
    */
    Box {
      objectName: "leftSideBar"
      id: leftSideBar
      x: 0
      y: 0
      width: parent.width / 3
      height: parent.height
      state: "Show"

      SimpleMenu {
        anchors.fill: parent
        anchors.margins: 25

        /*
        width: 150
        height: 430
        x: 25
        y: 25
        */

        objectName: "mainMenu"
        id: mainMenu

        Component.onCompleted: {
          addOption("Party", partyScreen);
          addOption("Item", itemScreen);
          addOption("Magic", magicScreen);
          setSelectedIndex(0);
        }
      }
    }

    PartyScreen {
      id: partyScreen
      objectName: "partyScreen"

      width: parent.width * 2/3
      anchors.right:  parent.right
      anchors.top:  parent.top
      anchors.bottom: parent.bottom
    }

    ItemScreen {
      objectName: "itemScreen"
      id: itemScreen

      width: parent.width * 2/3
      anchors.right:  parent.right
      anchors.top:  parent.top
      anchors.bottom: parent.bottom
    }

    MagicScreen {
      objectName: "magicScreen"
      id: magicScreen

      width: parent.width * 2/3
      anchors.right:  parent.right
      anchors.top:  parent.top
      anchors.bottom: parent.bottom
    }
  }

  BattleScreen {
    id: battleScreen
    objectName: "battleScreen"
  }

  Item {
    id: popups
    anchors.fill: parent
  }
}
