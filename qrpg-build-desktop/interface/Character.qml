import Qt 4.7
import "Character.js" as CharacterScript

Item {
  visible: false
  id: characterItem
  property int atk: 0
  property int def: 0
  property int matk: 0
  property int mdef: 0
  property int maxHp: 0
  property int maxMp: 0
  property int spd: 0
  property int dex: 0

  onAtkChanged: updateStat('atk');
  onDefChanged: updateStat('def');
  onMatkChanged: updateStat('matk');
  onMdefChanged: updateStat('mdef');
  onMaxHpChanged: updateStat('maxHp');
  onMaxMpChanged: updateStat('maxMp');
  onSpdChanged: updateStat('spd');
  onDexChanged: updateStat('dex');

  property int current_atk: 0
  property int current_def: 0
  property int current_matk: 0
  property int current_mdef: 0
  property int current_maxHp: 0
  property int current_maxMp: 0
  property int current_spd: 0
  property int current_dex: 0

  property int hp: 0
  property int mp: 0
  property string cls: ''
  property int level: 0

  //property string itemType: ''
  property string name: ''
  property string displayName: ''
  property string description: ''

  property string portrait: ''

  property string useAbility: ''
  property bool deleted: false

  Component.onCompleted: CharacterScript.startUp();

  signal typeChanged();

  function copy() {
    var c = newCharacter(name);

    c.atk = atk;
    c.def = def;
    c.matk = matk;
    c.mdef = mdef;
    c.maxHp = maxHp;
    c.maxMp = maxMp;
    c.spd = spd;
    c.dex = dex;
    c.hp = hp;
    c.mp = mp;
    c.cls = cls;
    c.level = level;
    //c.itemType = itemType;
    c.setTypes(getTypeArray());
    c.portrait = portrait;
    c.description = description;
    c.useAbility = useAbility;

    return c;
  }

  function heal() {
    mp = current_maxMp;
    hp = current_maxHp;
  }

  function getAncestor() {
    var x = this;
    while(x.parent && x.parent != ui)
      x = x.parent;
    return x;
  }

  function addSlots(name, count, allowed) {
    CharacterScript.slots[name] = Array();
    for(var i = 0; i < count; i++) {
      //console.log(characterItem.name + " adding slot " + name + " " + i);
      var slot = CharacterScript.CharacterItemSlotComponent.createObject(characterItem);
      slot.name = name;
      slot.setAllowedTypes(allowed);
      CharacterScript.slots[name].push(slot);
      //console.log(characterItem.name + " slot " + name + " " + i + " added");
    }
  }

  function addAbility(a) {
    CharacterScript.abilities.push(a);
  }

  function getEquippedItems() {
    var items = Array();
    var slots = CharacterScript.slots;
    for(s in slots) {
      for(var i in slots[s]) {
        if(slots[s][i].item)
          items.push(slots[s][i].item);
      }
    }
    return items;
  }

  function getStat(stat) {
    //console.log(characterItem.name + " getStat " + stat + ": " + characterItem['current_' + stat]);
    return characterItem['current_' + stat];
  }

  function updateStat(stat) {
    //console.log(characterItem.name + " updateStat " + stat);
    characterItem['current_' + stat] = getChildrenStat(stat) + characterItem[stat];
    updateParentStat(stat);
    //console.log(characterItem.name + " updateStat " + stat + " done: " +
    //            characterItem['current_' + stat]);
  }

  function updateStats() {
    //console.log(characterItem.name + " updateStats");
    var stats = Array('atk', 'def', 'matk', 'mdef', 'maxHp', 'maxMp', 'spd', 'dex');
    for(var i in stats) {
      updateStat(stats[i]);
    }

    updateParent();
    //console.log(characterItem.name + " updateStats done");
  }

  function updateParent() {
    if(parent && parent.updateStats) parent.updateStats();
  }

  function updateParentStat(stat) {
    if(parent && parent.updateStat) parent.updateStat(stat);
  }

  function setStat(stat, val) {
    characterItem[stat] = val;
    //updateStat(stat);
  }

  function getSlot(slot, number) {
    return CharacterScript.slots[slot][number];
  }

  function getChildrenStat(stat) {
    // Iterate through all immediate children and return sum of requested stat,
    // not including root oblect
    var total = 0;
    for(var itemSlots in CharacterScript.slots) {
      for(var slot in CharacterScript.slots[itemSlots]) {
        //console.log("Slot " + itemSlots + " " + slot);
        if(CharacterScript.slots[itemSlots][slot].item)
          total += CharacterScript.slots[itemSlots][slot].item.getStat(stat);
      }
    }

    return total;
  }

  /*
  function getType() {
    return itemType;
  }
  */

  // This function eqips an item if able, or returns false.  If item is equipped,
  // it returns the item that *was* equipped.
  function equip(item, slot, number) {
    console.log(characterItem.name + " equip " + slot + " " + number);

    //rpgx.dumpScriptObject(item);

    if(CharacterScript.slots[slot].length >= number) {
      if(CharacterScript.slots[slot][number].canEquip(item)) {
        oldItem = CharacterScript.slots[slot][number].item;
        CharacterScript.slots[slot][number].item = item;
        item.parent = this;
        updateStats();

        //if(oldItem) inventory.push(oldItem);
        return true;
      } else {
        return false;
      }
    }

    return false;
  }
  //o.slots = new Array();
  //o.status = new Array();
  //o.items = new Array();

  function activateUseAbility(user, targets) {
    //rpgx.dumpScriptObject(this);
    allAbilities[useAbility].activate.call(this, user, targets);
  }

  function getAbilities() {
    var abilities = CharacterScript.abilities;
    var currentAbilities = Array();
    for(var i in abilities) {
      currentAbilities.push(allAbilities[abilities[i]]);
    }
    // TODO: get abilites from each slot and add to list
    // deeper items should supercede earlier ones
    var childAbilities = Array();
    var items = getEquippedItems();
    //console.log("Items: " + serialize(items));
    for(var item in items) {
      //console.log("Item: " + items[item].name);
      var a = items[item].getAbilities();
      for(var i in a) {
        currentAbilities.push(allAbilities[a[i]]);
      }
    }
    return currentAbilities;
  }

  function getAbilityTree() {
    var a = getAbilities();
    var tree = new Object();
    for(var i in a) {
      tree = addBranch(tree, a[i].menuPath, a[i]);
    }

    return tree;
  }

  function deleteObject() {
    characterItem.destroy();
    this = null;
  }

  function setTypes(t) {
    CharacterScript.types = new Object();
    for(var i in t) {
      //console.log("set type " + t + " " + i + " " + t[i]);
      CharacterScript.types[t[i]] = 1;
    }
    typeChanged();
  }

  function setTypeObject(t) {
    CharacterScript.types = t;
  }

  function setType(t) {
    CharacterScript.types = new Object();
    CharacterScript.types[t] = 1;
    typeChanged();
  }

  function hasType(t) {
    return CharacterScript.types[t] == 1;
  }

  function addType(t) {
    CharacterScript.types[t] = 1;
    typeChanged();
  }

  function removeType(t) {
    delete CharacterScript.types[t];
    typeChanged();
  }

  function getTypeArray() {
    var t = Array();
    for(var i in CharacterScript.types) {
      //console.log("Get Type: " + i);
      t.push(i);
    }
    return t;
  }

  function getTypes() {
    return CharacterScript.types;
  }
}
