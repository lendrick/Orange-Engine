import Qt 4.7

MouseArea {
  id: modalItemScreen
  anchors.fill: parent
  property alias itemScreen: itemscreen

  function close() {
    itemScreen.hide();
    modalItemScreen.destroy(300);
  }

  onClicked: close();

  ItemScreen {
    id: itemscreen
    width: parent.width * 2/3
    height: parent.height * 2/3
    anchors.centerIn: parent
  }
}
