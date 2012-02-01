var enemies = new Object();
var characters = new Object();
var party = new Array();

var enemyParties = new Object();


characters['Lendrick'] = newCharacter('Lendrick');

characters['Lendrick'].atk = 4;
characters['Lendrick'].setStat('def', 5);
characters['Lendrick'].setStat('matk', 8);
characters['Lendrick'].setStat('mdef', 8);
characters['Lendrick'].setStat('maxHp', 30);
characters['Lendrick'].setStat('maxMp', 20);
characters['Lendrick'].setStat('spd', 5);
characters['Lendrick'].setStat('dex', 5 );
characters['Lendrick'].cls = "Wizard";
characters['Lendrick'].level = 1;

/*
characters['Lendrick'].slots['Armor'] = 1;
characters['Lendrick'].slots['Weapon'] = 1;
characters['Lendrick'].slots['Shield'] = 1;
characters['Lendrick'].slots['Accessory'] = 2;
*/

characters['Lendrick'].addSlots('Armor', 1, Array('armor', 'cloth'));
characters['Lendrick'].addSlots('Weapon', 1, Array('weapon', 'simple'));
characters['Lendrick'].addSlots('OffHand', 1, Array('offhand', '!shield'));
characters['Lendrick'].addSlots('Accessory', 2, Array('accessory', '!heavy'));

characters['Lendrick'].heal();

//characters['Lendrick'].currentHp = characters['Lendrick'].hp;
//characters['Lendrick'].currentMp = characters['Lendrick'].mp;

characters['Lendrick'].portrait = rpgx.projectDir() + "/images/lendrick_portrait.png";
characters['Lendrick'].equip(items['Iron Dagger'].copy(), 'Weapon', 0);
characters['Lendrick'].equip(items['Wizard Robe'].copy(), 'Armor', 0);
characters['Lendrick'].equip(items['Wizard Hat'].copy(), 'Accessory', 0);

characters['Lendrick'].addAbility('BarehandedFight');
characters['Lendrick'].addAbility('Cure1');
characters['Lendrick'].addAbility('Fire1');
characters['Lendrick'].addAbility('Run');

characters['Sithra'] = newCharacter('Sithra');

characters['Sithra'].setStat('atk', 6);
characters['Sithra'].setStat('def', 4);
characters['Sithra'].setStat('matk', 4);
characters['Sithra'].setStat('mdef', 8);
characters['Sithra'].setStat('maxHp', 25);
characters['Sithra'].setStat('maxMp', 25);
characters['Sithra'].setStat('spd', 4);
characters['Sithra'].setStat('dex', 7);
characters['Sithra'].cls = "Priest";
characters['Sithra'].level = 1;

/*
characters['Sithra'].slots['Armor'] = 1;
characters['Sithra'].slots['Weapon'] = 1;
characters['Sithra'].slots['Shield'] = 1;
characters['Sithra'].slots['Accessory'] = 2;
*/

characters['Sithra'].addSlots('Armor', 1, Array('armor', 'light'));
characters['Sithra'].addSlots('Weapon', 1, Array('weapon', 'bludgeoning'));
characters['Sithra'].addSlots('OffHand', 1, Array('offhand'));
characters['Sithra'].addSlots('Accessory', 2, Array('accessory'));

characters['Sithra'].equip(items['Wooden Staff'].copy(), 'Weapon', 0);
characters['Sithra'].equip(items['Leather Armor'].copy(), 'Armor', 0);

characters['Sithra'].addAbility('BarehandedFight');
characters['Sithra'].addAbility('Run');

characters['Sithra'].heal();

//characters['Sithra'].currentHp = characters['Sithra'].hp;
//characters['Sithra'].currentMp = characters['Sithra'].mp;

characters['Sithra'].portrait = rpgx.projectDir() + "/images/sithra_portrait.png";

party.push(characters['Lendrick']);
party.push(characters['Sithra']);

{
  var enemy = newCharacter('Slime');
  enemy.atk = 5;
  enemy.def = 2;
  enemy.matk = 0;
  enemy.mdef = 0;
  enemy.maxHp = 5;
  enemy.maxMp = 0;
  enemy.spd = 1;
  enemy.dex = 1;
  enemy.cls = "Slime";
  enemy.level = 1;
  enemy.addAbility('BarehandedFight');
  enemy.heal();
  enemy.portrait = rpgx.projectDir() + "/images/slime_blue.png";
  enemy.turnAI = 'random'

  enemies['Slime'] = enemy;
}

enemyParties['OneSlime'] = new Array('Slime');
enemyParties['TwoSlimes'] = new Array('Slime', 'Slime');
enemyParties['ThreeSlimes'] = new Array('Slime', 'Slime', 'Slime');

loadLevels('Lendrick', 'data/lendrick-levels.json');
characters['Lendrick'].addExp(6000);