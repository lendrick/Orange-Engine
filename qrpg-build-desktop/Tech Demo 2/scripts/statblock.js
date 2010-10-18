function StatBlock() {
  this.atk = 0;
  this.def = 0;
  this.matk = 0;
  this.mdef = 0;
  this.hp = 0;
  this.mp = 0;
  this.spd = 0;
  this.dex = 0;
  
  this.itemType = "";
  this.name = "";
  
  this.slots = new Array();
  
  this.items = new Array();
}

StatBlock.prototype.clearSlots = function() {
  for(var slot in slots) {
    items[slot] = Array();
  }
}

StatBlock.prototype.getStat = function(stat) {
  var total = 0;
  for(var itemSlots in items) {
    for(var item in items[itemSlots]) {
      total += items[itemSlots][item].getStat(stat);
    }
  }
  return total + this["stat"];
}

StatBlock.prototype.getType = function() {
  return itemType;
}

// This function eqips an item if able, or returns false.  If item is equipped,
// it returns the item that *was* equipped.
StatBlock.prototype.equip = function(item, slot, number) {
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

Character.prototype = new StatBlock();
Character.prototype.constructor = Character();
Character.prototype.parent = StatBlock.prototype;

function Character(name) {
  this.itemType = 'Character';
  this.name = name;
}

var test = "Hello, world!";

rpgx.print('statblock loaded');