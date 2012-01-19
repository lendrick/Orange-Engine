import QtQuick 1.0

Box {
  objectName: "messageBox"
  id: messageBox

  anchors.left: if(parent) parent.left
  anchors.right: if(parent) parent.right
  anchors.bottom: if(parent) parent.bottom
  height: 168

  focus: true
  property string text
  state: "Hide"
  opacity: 1

  Component.onCompleted: {
    state = "Show"
  }

  BigText {
    opacity: 1
    anchors.fill: messageBox
    anchors.topMargin: 25
    anchors.bottomMargin: 25
    anchors.leftMargin: 30
    anchors.rightMargin: 30
    text: messageBox.text
  }

  SequentialAnimation {
    running: true;
    PauseAnimation {
      duration: 800
    }
    ScriptAction {
      script: {
        state = "Hide"
        messageBox.destroy(200);
      }
    }
  }
}
