import QtQuick 1.0

Box {
  objectName: "combatMenuBox"
  id: combatMenuBox
  x: 0
  y: 0
  width: 200
  height: 200
  state: "Show"
  anchors.left: parent.right
  anchors.top: parent.top

  SimpleMenu {
    anchors.fill: parent
    anchors.margins: 25

    objectName: "combatMenu"
    id: combatMenu

    Component.onCompleted: {
      //addOption("Party", partyScreen);
      //addOption("Item", itemScreen);
      //addOption("Magic", magicScreen);
      setSelectedIndex(0);
    }
  }
}
