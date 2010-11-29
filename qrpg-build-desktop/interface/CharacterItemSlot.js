var allowedTypes;
var itemScreenObject;

function startUp() {
  allowedTypes = new Object();
  itemScreenObject = Qt.createComponent("ModalItemScreen.qml");
}
