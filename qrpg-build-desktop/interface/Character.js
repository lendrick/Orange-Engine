var CharacterItemSlotComponent;
var DamageNumberComponent;
var status;
var slots;
var abilities;
var useAbility;
var types;
var levels;

function startUp() {
  CharacterItemSlotComponent = Qt.createComponent("CharacterItemSlot.qml");
  DamageNumberComponent = Qt.createComponent("DamageNumber.qml");
  status = Array();
  slots = Array();
  abilities = Array();
  types = new Object();
  levels = Array();
}

function showDamage() {

}
