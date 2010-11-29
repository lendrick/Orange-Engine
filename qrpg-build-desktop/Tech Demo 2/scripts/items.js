
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
  items['Staff'].portrait = "../Tech Demo 2/images/icons/W_Mace011.png";

  items['Dagger'] = newCharacter('Dagger');
  items['Dagger'].setTypes(Array('weapon', 'metal', 'small', 'piercing', '1handed'));
  items['Dagger'].atk = 5;
  items['Dagger'].portrait = "../Tech Demo 2/images/icons/W_Dagger001.png";

  items['Leather Armor'] = newCharacter('LeatherAr');
  items['Leather Armor'].setTypes(Array('armor', 'non-metal', 'light'));
  items['Leather Armor'].def = 8;
  items['Leather Armor'].portrait = "../Tech Demo 2/images/icons/A_Armour01.png";

  items['Wizard Robe'] = newCharacter('WizRobe');
  items['Wizard Robe'].setTypes(Array('armor', 'non-metal', 'light', 'cloth'));
  items['Wizard Robe'].def = 4;
  items['Wizard Robe'].matk = 5;
  items['Wizard Robe'].description = 'I put on my WizRobe and WizHat...';
  items['Wizard Robe'].portrait = "../Tech Demo 2/images/icons/A_Clothing01.png";

  items['Wizard Hat'] = newCharacter('WizHat');
  items['Wizard Hat'].setTypes(Array('accessory', 'non-metal', 'light', 'cloth'));
  items['Wizard Hat'].mdef = 4;
  items['Wizard Hat'].portrait = "../Tech Demo 2/images/icons/C_Hat01.png";

  item = newCharacter('Potion');
  item.setTypes(Array('consumable', 'hp+'));
  item.useAbility = 'CurePotion';
  item.portrait = "../Tech Demo 2/images/icons/P_Red01.png";
  items['Potion'] = item;
  //console.log("potion ability: " + allAbilities['CurePotion'].name)

  item = newCharacter('Green Tea');
  item.setTypes(Array('consumable', 'mp+'));
  item.useAbility = 'GreenTea';
  item.portrait = "../Tech Demo 2/images/icons/P_Green02.png";
  items['Green Tea'] = item;
}

