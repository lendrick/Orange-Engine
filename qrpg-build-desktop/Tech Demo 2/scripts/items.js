var items = Array();
var inventory = Array();

{
  var item;


  items['Staff'] = newCharacter('Staff');
  items['Staff'].itemType = 'Weapon';
  items['Staff'].atk = 8;

  items['Dagger'] = newCharacter('Dagger');
  items['Dagger'].itemType = 'Weapon';
  items['Dagger'].atk = 5;

  items['Leather Armor'] = newCharacter('LeatherAr');
  items['Leather Armor'].itemType = 'Armor';
  items['Leather Armor'].def = 8;

  items['Wizard Robe'] = newCharacter('WizRobe');
  items['Wizard Robe'].itemType = 'Armor';
  items['Wizard Robe'].def = 4;
  items['Wizard Robe'].matk = 5;

  items['Wizard Hat'] = newCharacter('WizHat');
  items['Wizard Hat'].itemType = 'Accessory';
  items['Wizard Hat'].mdef = 4;

  item = newCharacter('Potion');
  item.itemType = 'Consumable';
  item.useAbility = 'CurePotion';
  items['Potion'] = item;
  //console.log("potion ability: " + allAbilities['CurePotion'].name)

  item = newCharacter('Green Tea');
  item.itemType = 'Consumable';
  items['Green Tea'] = item;
}
