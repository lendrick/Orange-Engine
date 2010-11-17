var items = Array();
var inventory = Array();

{
  var item;


  items['Staff'] = newCharacter('Staff');
  items['Staff'].setTypes('weapon', 'bludgeoning', 'simple', 'non-metal', '2handed');
  items['Staff'].atk = 8;

  items['Dagger'] = newCharacter('Dagger');
  items['Dagger'].setTypes('weapon', 'metal', 'small', 'piercing', '1handed');
  items['Dagger'].atk = 5;

  items['Leather Armor'] = newCharacter('LeatherAr');
  items['Leather Armor'].setTypes('armor', 'non-metal', 'light');
  items['Leather Armor'].def = 8;

  items['Wizard Robe'] = newCharacter('WizRobe');
  items['Wizard Robe'].setTypes('armor', 'non-metal', 'light', 'cloth');
  items['Wizard Robe'].def = 4;
  items['Wizard Robe'].matk = 5;

  items['Wizard Hat'] = newCharacter('WizHat');
  items['Wizard Hat'].setTypes('accessory', 'non-metal', 'light', 'cloth');
  items['Wizard Hat'].mdef = 4;

  item = newCharacter('Potion');
  item.setTypes('consumable', 'hp+');
  item.useAbility = 'CurePotion';
  items['Potion'] = item;
  //console.log("potion ability: " + allAbilities['CurePotion'].name)

  item = newCharacter('Green Tea');
  item.setTypes('consumable', 'mp+');
  items['Green Tea'] = item;
}
