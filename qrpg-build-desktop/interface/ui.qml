import Qt 4.7
import "talkbox.js" as TalkBoxScript

Item {
  id: ui
  objectName: "ui"
  x: 0
  y: 0
  height: 640
  width: 480

  Box {
    objectName: "talkbox"
    id: talkbox
    x: 0
    y: 480-168
    z: 0
    width: 640
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

  Item {
    objectName: "statusScreen"
    id: statusScreen
    x: 0
    y: 0
    height: 640
    width: 480
    state: "Hide"

    function show() {
      state = "Show";
    }

    function hide() {
      state = "Hide";
    }

    Box {
      objectName: "leftSideBar"
      id: leftSideBar
      x: 0
      y: 0
      width: 240
      height: 480
      state: "Show"
    }

    Box {
      objectName: "mainSection"
      id: mainSection
      x: 240
      y: 0
      width: 400
      height: 480
      state: "Show"
    }

    states: [
      State {
        name: "Hide"

        PropertyChanges {
          target: statusScreen
          opacity: 0
          scale: .75
        }

      },
      State {
        name: "Show"

        PropertyChanges {
          target: statusScreen
          opacity: 1
          scale: 1
        }
      }
    ]

    transitions: [
      Transition {
        to: "Hide"
        PropertyAnimation {
          properties: "opacity"
          duration: 150
        }
        PropertyAnimation {
          properties: "scale"
          duration: 350
          easing.type: Easing.Linear
        }
      },

      Transition {
        to: "Show"
        PropertyAnimation {
          properties: "opacity"
          duration: 225
        }
        PropertyAnimation {
          properties: "scale"
          duration: 350
          easing.type: Easing.OutBack
        }
      }
    ]
  }

}
