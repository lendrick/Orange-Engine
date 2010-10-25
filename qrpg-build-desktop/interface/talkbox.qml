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

}
