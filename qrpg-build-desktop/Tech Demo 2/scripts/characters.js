
var characters = new Array();
var party = new Array();

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

characters['Lendrick'].addSlots('Armor', 1);
characters['Lendrick'].addSlots('Weapon', 1);
characters['Lendrick'].addSlots('Shield', 1);
characters['Lendrick'].addSlots('Accessory', 2);

characters['Lendrick'].heal();

//characters['Lendrick'].currentHp = characters['Lendrick'].hp;
//characters['Lendrick'].currentMp = characters['Lendrick'].mp;

characters['Lendrick'].portrait = "../Tech Demo 2/images/lendrick_portrait.png";
characters['Lendrick'].equip(items['Dagger'].copy(), 'Weapon', 0);
characters['Lendrick'].equip(items['Wizard Robe'].copy(), 'Armor', 0);
characters['Lendrick'].equip(items['Wizard Hat'].copy(), 'Accessory', 0);

characters['Lendrick'].addAbility('BarehandedFight');
characters['Lendrick'].addAbility('Cure1');

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
characters['Sithra'].addSlots('Armor', 1);
characters['Sithra'].addSlots('Weapon', 1);
characters['Sithra'].addSlots('Shield', 1);
characters['Sithra'].addSlots('Accessory', 2);

characters['Sithra'].equip(items['Staff'].copy(), 'Weapon', 0);
characters['Sithra'].equip(items['Leather Armor'].copy(), 'Armor', 0);

characters['Sithra'].addAbility('BarehandedFight');

characters['Sithra'].heal();

//characters['Sithra'].currentHp = characters['Sithra'].hp;
//characters['Sithra'].currentMp = characters['Sithra'].mp;

characters['Sithra'].portrait = "../Tech Demo 2/images/sithra_portrait.png";

party.push(characters['Lendrick']);
party.push(characters['Sithra']);
