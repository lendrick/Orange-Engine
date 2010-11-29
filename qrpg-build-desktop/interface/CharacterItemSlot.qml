import Qt 4.7
import "CharacterItemSlot.js" as CharacterItemSlotScript

Item {
  visible: false
  id: characterItemSlot;
  property Item item
  property string name;

  Component.onCompleted: CharacterItemSlotScript.startUp();

  function setAllowedTypes(types) {
    CharacterItemSlotScript.allowedTypes = new Object();
    for(var i in types) {
      CharacterItemSlotScript.allowedTypes[types[i]] = 1;
    }
  }

  function canEquip(item) {
    //return(isAllowed(item.itemType));
    var equip = false;

    for(var i in item.getTypes()) {
      if(CharacterItemSlotScript.allowedTypes[i]) equip = true;
    }

    for(var i in item.getTypes()) {
      if(CharacterItemSlotScript.allowedTypes['!' + i]) equip = false;
    }
    return equip;
  }

  function itemScreenObject() {
    var obj = CharacterItemSlotScript.itemScreenObject.createObject(ui);
    /*obj.width = ui.width * 2/3;
    obj.height = ui.height * .5;
    obj.x = ui.width * 1/3;
    obj.y = ui.height * .5; */
    obj.itemScreen.itemSlot = characterItemSlot;
    obj.itemScreen.inBattle = false;
    obj.itemScreen.show();
    return obj;
  }

  function closeMenu() {

  }

  function equip(i) {
    if(canEquip(i)) {
      oldItem = item;
      if(oldItem) {
        oldItem.activateUnequipAbility(oldItem, this);
        oldItem.parent = null;
      }

      removeFromInventory(i);

      i.parent = this;
      item = i;
      parent.updateStats();
      item.activateEquipAbility(item, this);

      if(oldItem) addToInventory(oldItem);
      return true;
    } else {
      console.log(parent.name + " can't equip " + item.name + " in slot " + name);
      return false;
    }
  }
}
