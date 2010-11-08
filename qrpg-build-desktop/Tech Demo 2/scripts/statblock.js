
rpgx.print('loading statblock');

function newStatBlock() {
  o = new BindObject();
  o.atk = 0;
  o.def = 0;
  o.matk = 0;
  o.mdef = 0;
  o.hp = 0;
  o.mp = 0;
  o.spd = 0;
  o.dex = 0;
  o.currentHp = 0;
  o.currentMp = 0;
  o.cls = "";
  o.level = 0;
  o.status = new Array();
  
  o.itemType = "";
  o.name = "";
  
  o.slots = new Array();
  
  o.items = new Array();

  o.heal = function() {
    currentMp = mp;
    currentHp = hp;
  }

  o.setDef = function(d) {
   o.def = d;
  }

  o.clearSlots = function() {
    for(var slot in slots) {
      items[slot] = Array();
    }
  }

  o.getStat = function(stat) {
    var total = 0;
    for(var itemSlots in items) {
      for(var item in items[itemSlots]) {
        total += items[itemSlots][item].getStat(stat);
      }
    }
    return total + this["stat"];
  }

  o.getType = function() {
    return itemType;
  }

  // This function eqips an item if able, or returns false.  If item is equipped,
  // it returns the item that *was* equipped.
  o.equip = function(item, slot, number) {
    if(slots[item.getType()] >= number) {
      oldItem = items[item.getType()][number];
      items[item.getType()][number] = item;
      if(!oldItem) {
        return true;
      } else {
        return oldItem;
      }
    }

    return false;
  }

  return o;
}


function newCharacter(name) {
  o = newStatBlock();
  o.itemType = 'Character';
  o.name = name;
  //rpgx.makeQmlGlobal(o);
  return o;
}

var test = "Hello, world!";
rpgx.print("Test: " + test);
