import Qt 4.7
import "Character.js" as CharacterScript

Item {
  visible: false
  id: characterItem
  property int invIndex: -1

  property int atk: 0
  property int def: 0
  property int matk: 0
  property int mdef: 0
  property int maxHp: 0
  property int maxMp: 0
  property int spd: 0
  property int dex: 0
  property bool deleted: false

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
  property string equipAbility: ''
  property string unequipAbility: ''

  property string turnAI: ''

  property bool alive: (hp > 0)
  property Item image

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
    c.equipAbility = equipAbility;
    c.unequipAbility = unequipAbility;
    c.turnAI = turnAI;

    for(var i in CharacterScript.abilities) {
      console.log("copy ability: " + CharacterScript.abilities[i])
      c.addAbility(CharacterScript.abilities[i]);
    }

    return c;
  }

  function heal() {
    mp = current_maxMp;
    hp = current_maxHp;
  }

  function setInvIndex(x) {
    invIndex = x;
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

  function getAbilityNames() {
    return CharacterScript.abilities;
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
    console.log(characterItem.name + " equip " + item.name + " in " + slot + " " + number);

    //rpgx.dumpScriptObject(item);

    if(CharacterScript.slots[slot].length >= number) {
      /*
      if(CharacterScript.slots[slot][number].canEquip(item)) {
        oldItem = CharacterScript.slots[slot][number].item;
        if(oldItem) {
          oldItem.activateUnequipAbility(oldItem, this);
          oldItem.parent = null;
        }

        item.parent = this;
        CharacterScript.slots[slot][number].item = item;
        updateStats();
        item.activateEquipAbility(item, this);

        if(oldItem) addToInventory(oldItem);
        return true;
      } else {
        console.log(characterItem.name + " can't equip " + item.name + " in " + slot + " " + number + "!");
        return false;
      }
      */
      CharacterScript.slots[slot][number].equip(item);
    }

    return false;
  }
  //o.slots = new Array();
  //o.status = new Array();
  //o.items = new Array();

  function activateEquipAbility(user, target) {
    if(equipAbility)
      allAbilities[equipAbility].activate.call(this, user, targets);
  }

  function activateUnequipAbility(user, target) {
    if(unequipAbility)
      allAbilities[unequipAbility].activate.call(this, user, targets);
  }

  function activateUseAbility(user, targets) {
    //rpgx.dumpScriptObject(this);
    if(useAbility)
      allAbilities[useAbility].activate.call(this, user, targets);
  }

  function getUseAbility() {
    if(useAbility)
      return allAbilities[useAbility];
    else
      return null;
  }

  function getAbilities() {
    var abilities = CharacterScript.abilities;
    var currentAbilities = Array();
    for(var i in abilities) {
      //console.log("getAbilities: " + serialize(allAbilities[abilities[i]]));
      currentAbilities.push(allAbilities[abilities[i]]);
    }
    /*
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
    */
    return currentAbilities;
  }

  function getAbilityTree() {
    var a = this.getAbilities();
    //console.log("Ability list: " + serialize(a));
    var tree = new Object();
    for(var i in a) {
      //console.log("MenuPath " + serialize(a[i].menuPath));
      tree = addBranch(tree, a[i].menuPath, a[i]);
    }

    return tree;
  }

  function deleteObject() {
    deleted = true;
    removeFromInventory(characterItem);
    characterItem.destroy();
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

  function addHp(val) {
    hp += val;
    if(hp > current_maxHp)
      hp = current_maxHp;
    else if(hp < 0)
      hp = 0;

    console.log(name + ".addHp(" + val + "): " + hp)
    if(image) {
      CharacterScript.DamageNumberComponent.createObject(image, { text: val })
      if(val < 0) {
        if(image.hit) {
          image.hit();
        }
      }
    }
  }

  function addMp(val) {
    mp += val;
    if(mp > current_maxMp)
      mp = current_maxMp;
    else if(mp < 0)
      mp = 0;

    console.log(name + ".addMp(" + val + "): " + mp)
  }

}
