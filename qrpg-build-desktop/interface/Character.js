var CharacterItemSlotComponent;
var status;
var slots;
var abilities;
var useAbility;

function startUp() {
  CharacterItemSlotComponent = Qt.createComponent("CharacterItemSlot.qml");
  status = Array();
  slots = Array();
  abilities = Array();
}
