var CharacterItemSlotComponent;
var status;
var slots;
var abilities;
var useAbility;
var types;

function startUp() {
  CharacterItemSlotComponent = Qt.createComponent("CharacterItemSlot.qml");
  status = Array();
  slots = Array();
  abilities = Array();
  types = new Object();
}
