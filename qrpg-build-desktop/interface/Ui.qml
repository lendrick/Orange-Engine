import Qt 4.7
import "Ui.js" as UiScript

Item {  //Item
  id: ui
  objectName: "ui"
  //color: Qt.rgba(0, 0, 0, .2);  //test only
  property string test: "testing"
  property alias statusscreen: statusScreen
  property alias talkbox: talkBox
  property alias battlescreen: battleScreen;

  Component.onCompleted: UiScript.startUp();

  x: 0
  y: 0
  width: 640
  height: 480

  //anchors.fill: parent

  function callbackTest(func) {
    func();
  }

  function toggleStatusScreen() {
    console.log("ui.toggleStatusScreen()");
    statusScreen.toggleVisible();
  }

  function script() {
    return UiScript;
  }

  function self() {
    return this;
  }

  function runTest() {
    var foo = new Object();
    foo.test = function() {
        console.log("FOO TEST");
    }
    foo.blah = "blah";
    console.log("blah: " + foo.blah);
    ui.testMe(foo);
  }

  function testMe(foo) {
    console.log("*******************");
    rpgx.dumpScriptObject(foo);
    for(var x in foo) {
      console.log(x + ": " + foo[x]);
    }

    try {
      foo.test();
    } catch(e) {
      console.log("FAILED");
    }
  }

  function treeMenu(parent, tree, cb) {
    var menu = UiScript.TreeMenuComponent.createObject(popups);
    menu.setOptions(tree);
    menu.callback = cb;
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
    battlescreen.setParty(enemyParty);
    battlescreen.show();
    battlescreen.start();
  }

  Box {
    objectName: "talkBox"
    id: talkBox

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
      console.log("textbox length: " + UiScript.textBoxArray.length);
    }

    function appendScript(textString, script) {
      UiScript.appendScript(textString, script);
    }

    function show() {
      state = "Show";
      UiScript.textBoxArray[0].state = "Show";
      focus = true;
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

        if(object.hasCallback) {
          console.log("running script");
          object.runCallback();
        }

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

    property alias partyscreen: partyScreen
    property alias itemscreen: itemScreen
    property alias magicscreen: magicScreen
/*
    x: 0
    y: 0
    height: 640
    width: 480
  */

    anchors.fill:  parent

    state: "Hide"

    onStateChanged: {
      if(state == "Hide") {
        rpgx.unPause();
      } else if(state == "Show") {
        rpgx.pause();
      }
    }

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
