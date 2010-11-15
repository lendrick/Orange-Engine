var abilities = Array();

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
    target = targets[0];
    target.hp += 30;
  }

  abilities['CurePotion'] = ability;
}
