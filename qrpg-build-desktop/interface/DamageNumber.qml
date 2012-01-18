import QtQuick 1.0

Text {
  id: damageNumber
  color: "#ffffff"
  clip: true
  font.pixelSize: 35
  font.family: "Liberation Mono"
  smooth: true
  font.bold: true
  wrapMode: Text.WordWrap
  opacity: 1
  anchors.centerIn: parent;
  style: Text.Outline
  styleColor: "#000000"

  ParallelAnimation {
    running: true
    SequentialAnimation {
      PropertyAnimation {
        target: damageNumber;
        property: "opacity";
        to: 0;
        duration: 900
      }
      ScriptAction {
        script: damageNumber.destroy(300);
      }
    }

    PropertyAnimation {
      target: damageNumber
      property: "anchors.verticalCenterOffset"
      to: 50
      easing.type: Easing.OutBounce;
      duration: 900
    }
  }
}
