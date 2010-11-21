var allAbilities = Array();

{
  var ability;

  ability = newAbility('CurePotion');
  ability.targetSelf = true;
  ability.targetEnemies = true;
  ability.targetFriends = true;
  ability.targetMultiple = false;
  ability.useInBattle = true;
  ability.useOutsideBattle = true;
  ability.portrait = "../Tech Demo 2/images/icons/P_Red01.png";

  ability.activate = function(caster, targets) {
    console.log(caster.name + " uses " + this.name + " on " + targets[0].name);
    target = targets[0];
    target.hp += 30;
    //rpgx.dumpScriptObject(this);
    this.deleteObject();
    console.log("CurePotion done");
  }

  //rpgx.dumpScriptObject(activate);
  //ability.setActivateFunction(activate);

  allAbilities['CurePotion'] = ability;
  console.log("Created ability " + ability.name);

  ability = newAbility('BarehandedFight');
  ability.targetSelf = true;
  ability.targetEnemies = true;
  ability.targetFriends = true;
  ability.targetMultiple = false;
  ability.useInBattle = true;
  ability.useOutsideBattle = false;
  ability.menuPath = new Array('Fight');
  ability.portrait = "../Tech Demo 2/images/icons/W_Fist001.png";

  ability.activate = function(caster, targets) {
    console.log(caster.name + " attacks " + targets[0].name);
    target = targets[0];
    damage = caster.atk - target.def;
    if(damage < 1) damage = 1;
    target.hp -= damage;
    console.log(target.name + " takes " + damage + " damage");
  }


  allAbilities['BarehandedFight'] = ability;

  ability = newAbility('Fire1');
  ability.targetSelf = true;
  ability.targetEnemies = true;
  ability.targetFriends = true;
  ability.targetMultiple = false;
  ability.useInBattle = true;
  ability.useOutsideBattle = false;
  ability.menuPath = new Array('Magic', 'Fire1');
  ability.portrait = "../Tech Demo 2/images/icons/S_Fire01.png";

  ability.activate = function(caster, targets) {
    console.log(caster.name + " casts Fire1 on " + targets[0].name);
    target = targets[0];
    damage = caster.atk - target.def;
    if(damage < 1) damage = 1;
    target.hp -= damage;
    console.log(target.name + " takes " + damage + " damage");
  }

  allAbilities['Fire1'] = ability;

  ability = newAbility('Cure1');

  ability.targetSelf = true;
  ability.targetEnemies = true;
  ability.targetFriends = true;
  ability.targetMultiple = true;
  ability.useInBattle = true;
  ability.useOutsideBattle = true;
  ability.menuPath = new Array('Magic', 'Cure');
  ability.portrait = "../Tech Demo 2/images/icons/S_Holy01.png";

  ability.activate = function(caster, targets) {
    console.log(caster.name + " casts " + this.name + " on " + targets[0].name);
    target = targets[0];
    target.hp += 15 + Math.floor(caster.matk / 8);
    //rpgx.dumpScriptObject(this);
    console.log("Cure1 done");
  }

  //rpgx.dumpScriptObject(activate);
  //ability.setActivateFunction(activate);

  allAbilities['Cure1'] = ability;
  console.log(serialize(allAbilities['Cure1']));
  console.log("Created ability " + ability.name);

}
