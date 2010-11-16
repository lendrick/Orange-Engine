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


  ability.activate = function(caster, targets) {
    console.log(caster.name + " uses " + this.name + " on " + targets[0].name);
    target = targets[0];
    target.hp += 30;
    rpgx.dumpScriptObject(this);
    this.deleteObject();
    console.log("CurePotion done");
  }

  //rpgx.dumpScriptObject(activate);
  //ability.setActivateFunction(activate);

  allAbilities['CurePotion'] = ability;
  console.log("Created ability " + ability.name);
}
