var characters = new Array();
var party = new Array();

characters['Lendrick'] = newCharacter('Lendrick');

characters['Lendrick'].atk =  4;
characters['Lendrick'].def =  5;
characters['Lendrick'].matk = 8;
characters['Lendrick'].mdef = 8;
characters['Lendrick'].hp =   30;
characters['Lendrick'].mp =   20;
characters['Lendrick'].spd =  5;
characters['Lendrick'].dex =  5;
characters['Lendrick'].cls = "Wizard";
characters['Lendrick'].level = 1;

characters['Lendrick'].slots['Armor'] = 1;
characters['Lendrick'].slots['Weapon'] = 1;
characters['Lendrick'].slots['Shield'] = 1;
characters['Lendrick'].slots['Accessory'] = 2;

characters['Lendrick'].currentHp = characters['Lendrick'].hp;
characters['Lendrick'].currentMp = characters['Lendrick'].mp;
//characters['Lendrick'].setDef(20);

characters['Sithra'] = newCharacter('Sithra');

characters['Sithra'].atk =  6;
characters['Sithra'].def =  4;
characters['Sithra'].matk = 4;
characters['Sithra'].mdef = 8;
characters['Sithra'].hp =   25;
characters['Sithra'].mp =   25;
characters['Sithra'].spd =  4;
characters['Sithra'].dex =  7;
characters['Sithra'].cls = "Priest";
characters['Sithra'].level = 1;

characters['Sithra'].slots['Armor'] = 1;
characters['Sithra'].slots['Weapon'] = 1;
characters['Sithra'].slots['Shield'] = 1;
characters['Sithra'].slots['Accessory'] = 2;

characters['Sithra'].currentHp = characters['Sithra'].hp;
characters['Sithra'].currentMp = characters['Sithra'].mp;

party.push(characters['Lendrick']);
party.push(characters['Sithra']);
