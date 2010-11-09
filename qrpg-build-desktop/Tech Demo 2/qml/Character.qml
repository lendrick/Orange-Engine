import Qt 4.7
import "Character.js" as CharacterScript

Item {
  visible: false
  id: characterItem
  property int atk
  property int def
  property int matk
  property int mdef
  property int hp
  property int mp
  property int spd
  property int dex
  property int currentHp
  property int currentMp
  property string cls
  property int level

  property string itemType;
  property string name;

  function heal() {
    mp = currentMp;
    hp = currentHp;
  }

  function addSlots(name, count) {
    CharacterScript.slots[name] = count;
  }


  function getStat(stat) {
    var total = 0;
    for(var itemSlots in CharacterScript.items) {
      for(var item in CharacterScript.items[itemSlots]) {
        total += CharacterScript.items[itemSlots][item].getStat(stat);
      }
    }
    //console.log("getstat " + total + characterItem[stat]);
    return total + characterItem[stat];
  }

  function getType() {
    return itemType;
  }

  // This function eqips an item if able, or returns false.  If item is equipped,
  // it returns the item that *was* equipped.
  function equip(item, slot, number) {
    if(CharacterScript.slots[item.getType()] >= number) {
      oldItem = CharacterScript.items[item.getType()][number];
      CharacterScript.items[item.getType()][number] = item;
      if(!oldItem) {
        return true;
      } else {
        return oldItem;
      }
    }

    return false;
  }
  //o.slots = new Array();
  //o.status = new Array();
  //o.items = new Array();
}
