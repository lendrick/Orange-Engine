
/*
inventory.add = function(item) {
  var added = false;
  for(var i in this) {
    if(!this[i]) {
      this[i] = item;
      added = true;
    }
  }

  if(!added) this.push(item);
}
*/

// Item definitions
{
  var item;

  items['Staff'] = newCharacter('Staff');
  items['Staff'].setTypes(Array('weapon', 'bludgeoning', 'simple', 'non-metal', '2handed'));
  items['Staff'].atk = 8;

  items['Dagger'] = newCharacter('Dagger');
  items['Dagger'].setTypes(Array('weapon', 'metal', 'small', 'piercing', '1handed'));
  items['Dagger'].atk = 5;

  items['Leather Armor'] = newCharacter('LeatherAr');
  items['Leather Armor'].setTypes(Array('armor', 'non-metal', 'light'));
  items['Leather Armor'].def = 8;

  items['Wizard Robe'] = newCharacter('WizRobe');
  items['Wizard Robe'].setTypes(Array('armor', 'non-metal', 'light', 'cloth'));
  items['Wizard Robe'].def = 4;
  items['Wizard Robe'].matk = 5;
  items['Wizard Robe'].description = 'I put on my WizRobe and WizHat...';

  items['Wizard Hat'] = newCharacter('WizHat');
  items['Wizard Hat'].setTypes(Array('accessory', 'non-metal', 'light', 'cloth'));
  items['Wizard Hat'].mdef = 4;

  item = newCharacter('Potion');
  item.setTypes(Array('consumable', 'hp+'));
  item.useAbility = 'CurePotion';
  items['Potion'] = item;
  //console.log("potion ability: " + allAbilities['CurePotion'].name)

  item = newCharacter('Green Tea');
  item.setTypes(Array('consumable', 'mp+'));
  items['Green Tea'] = item;
}

