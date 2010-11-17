
rpgx.debug("RUNNING startup.js");

// NOTE TO SELF:
// CAN I DEFINE THE CHARACTER AND OTHER SHARE-ABLE CLASSES IN QML AND THEN
// CREATE THEM THAT WAY?  THEN THEY SHOULD TRANSFER OVER TO THE GUI JUST
// FINE, AND I SHOULD STILL BE ABLE TO CALL THEIR FUNCTIONS


for(var i in party) {
  ui.addPartyMember(party[i]);
}

ui.statusScreen.partyScreen.setCurrentPartyMember(0);
ui.statusScreen.magicScreen.setCurrentPartyMember(0);

function toggleUi() {
  ui.statusScreen.toggleVisible();
}

rpgx.menuKey.connect(toggleUi);

console.log("inv " + inventory.length);

inventory.push(items['Staff'].copy());
inventory.push(items['Potion'].copy());

for(var i = 0; i < 15; i++)
  inventory.push(items['Potion'].copy());

for(var i = 0; i < 15; i++)
  inventory.push(items['Green Tea'].copy());

//console.log(inventory[1].name + " " + inventory[1].getUseAbility().name);

//inventory[1].getUseAbility().setActivateFunction(toggleUi);

//allAbilities['CurePotion'].setActivateFunction(toggleUi);
//rpgx.dumpScriptObject(toggleUi);

inventory[1].activateUseAbility(party[1], Array(party[0]));

/*
var test1 = Array('Fight');
var test2 = Array('Magic', 'Fire');
var test3 = Array('Magic', 'Cure');
var test4 = Array('Run');

var test = new Object();

test = addBranch(test, test1, 'fight');
test = addBranch(test, test2, 'fire');
test = addBranch(test, test3, 'cure');
test = addBranch(test, test4, 'run');
console.log(serialize(test));

var x = new Object();
x['a'] = 'foo';
x['b'] = new Object();
x['b']['c'] = 'yada';
x['b']['d'] = 'blah';
x['e'] = 'bar';
*/
console.log(serialize(party[0].getAbilityTree()));
