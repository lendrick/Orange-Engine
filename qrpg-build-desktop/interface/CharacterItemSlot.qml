import Qt 4.7
import "CharacterItemSlot.js" as CharacterItemSlotScript

Item {
  visible: false
  property Item item
  property string name;
  property string filter;

  onFilterChanged: setFilter(filter);

  Component.onCompleted: CharacterItemSlotScript.startUp();

  /*
  function setAllowedTypes(types) {
    CharacterItemSlotScript.allowedTypes = new Object();
    for(var i in types) {
      CharacterItemSlotScript.allowedTypes[types[i]] = 1;
    }
  }

  function isAllowed(t) {
    return(CharacterItemSlotScript.allowedTypes[t] == 1);
  }

  function canEquip(item) {
    return(isAllowed(item.itemType));
  }
  */

  function canEquip(item) {
    return CharacterItemSlotScript.slotFilter(item);
  }

  function setFilter(filterName) {
    CharacterItemSlotScript.slotFilter = slotFilters['filterName'];
  }
}
