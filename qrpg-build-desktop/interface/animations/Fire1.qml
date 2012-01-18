import QtQuick 1.0

Rectangle {
  id: rect
  height: 30
  width: 30
  color: "red"
  anchors.centerIn: parent
  opacity: 1


  SequentialAnimation {
    running: true;
    PropertyAnimation {
      target: rect
      properties: "scale, opacity"
      from: 1.0
      to: 0.0
      duration: 300
      easing.type: Easing.Linear
    }
    ScriptAction {
      script: rect.destroy(1000);
    }
  }
}

