var enemies = new Object();
var characters = new Object();
var party = new Array();

var enemyParties = new Object();

loadItems('data/items.json');
loadEnemies('data/enemies.json');
loadCharacters('data/characters.json');

party.push(characters['Lendrick']);
party.push(characters['Sithra']);

enemyParties['OneSlime'] = new Array('Slime');
enemyParties['TwoSlimes'] = new Array('Slime', 'Icky Slime');
enemyParties['ThreeSlimes'] = new Array('Slime', 'Icky Slime', 'Acid Slime');
