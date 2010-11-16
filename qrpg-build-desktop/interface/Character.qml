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

  property string itemType: ''
  property string name: ''
  property string description: ''

  property string portrait: ''

  property string useAbility: ''

  Component.onCompleted: CharacterScript.startUp();

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
    c.itemType = itemType;
    c.portrait = portrait;
    c.description = description;
    c.useAbility = useAbility;

    return c;
  }

  function heal() {
    mp = current_maxMp;
    hp = current_maxHp;
  }

  function addSlots(name, count) {
    CharacterScript.slots[name] = Array();
    for(var i = 0; i < count; i++) {
      //console.log(characterItem.name + " adding slot " + name + " " + i);
      var slot = CharacterScript.CharacterItemSlotComponent.createObject(characterItem);
      slot.name = name;
      CharacterScript.slots[name].push(slot);
      //console.log(characterItem.name + " slot " + name + " " + i + " added");
    }
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

  function getType() {
    return itemType;
  }

  // This function eqips an item if able, or returns false.  If item is equipped,
  // it returns the item that *was* equipped.
  function equip(item, slot, number) {
    console.log(characterItem.name + " equip " + item.getType() + " " + number);

    //rpgx.dumpScriptObject(item);

    if(CharacterScript.slots[item.getType()].length >= number) {
      oldItem = CharacterScript.slots[item.getType()][number].item;
      CharacterScript.slots[item.getType()][number].item = item;
      updateStats();

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

  function activateUseAbility(user, targets) {
    //rpgx.dumpScriptObject(this);
    allAbilities[useAbility].activate.call(this, user, targets);
  }

  function getAbilities() {

  }

  function deleteObject() {
    this.destroy();
  }
}
