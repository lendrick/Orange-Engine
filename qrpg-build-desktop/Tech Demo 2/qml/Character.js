var CharacterItemSlotComponent;
var status;
var slots;

function startUp() {
  CharacterItemSlotComponent = Qt.createComponent("CharacterItemSlot.qml");
  status = Array();
  slots = Array();
}
