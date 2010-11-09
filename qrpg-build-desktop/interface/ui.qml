import Qt 4.7
import "talkbox.js" as TalkBoxScript

Item {  //Item
  id: ui
  objectName: "ui"
  //color: Qt.rgba(0, 0, 0, .2);  //test only

  x: 0
  y: 0
  width: 640
  height: 480

  //anchors.fill: parent

  function addPartyMember(character) {
    partyScreen.addPartyMember(character);
  }

  function setPartyMember(i, character) {
    partyScreen.setPartyMember(i, character);
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

    Component.onCompleted: TalkBoxScript.startUp();

    function append(textString) {
      TalkBoxScript.appendText(textString);
    }

    function show() {
      state = "Show";
      TalkBoxScript.textBoxArray[0].state = "Show";
      //TalkBoxScript.textBoxArray[0].text += " " + parent.objectName;
    }

    function hide() {
      state = "Hide";
    }

    function queueSize() {
      return TalkBoxScript.textBoxArray.length;
    }

    Keys.onPressed: {
      if(state == "Show" && !event.isAutoRepeat ) {
        var object = TalkBoxScript.textBoxArray.shift();
        object.state = "Hide";
        object.destroy(500);

        if(TalkBoxScript.textBoxArray.length > 0) {
          TalkBoxScript.textBoxArray[0].state = "Show";
        } else {
          state = "Hide";
        }

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

    Box {
      objectName: "itemScreen"
      id: itemScreen

      /*
      x: parent.width / 3
      y: 0
      width: 440
      height: 480
      */
      width: parent.width * 2/3
      anchors.right:  parent.right
      anchors.top:  parent.top
      anchors.bottom: parent.bottom

      state: "Hide"
      MediumText {
        x: 25
        y: 25
        text: "items"
      }
    }

    Box {
      objectName: "magicScreen"
      id: magicScreen
      width: parent.width * 2/3
      anchors.right:  parent.right
      anchors.top:  parent.top
      anchors.bottom: parent.bottom

      state: "Hide"
      MediumText {
        x: 25
        y: 25
        text: "magic"
      }
    }
  }
}
