
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
  //dumpInventory();
  ui.statusScreen.toggleVisible();
  //dumpInventory();
}

rpgx.menuKey.connect(toggleUi);

//console.log("inv " + inventory.length);

addNewItem('Staff');
addNewItem('Potion');
addNewItem('Potion');
addNewItem('Green Tea');

inventory[1].activateUseAbility(party[1], Array(party[0]));

//rpgx.dumpScriptObject(inventory[1]);

/*
for(var x = 0; x < 30; x++) {
  addToInventory(items['Green Tea'].copy());
}

for(var x = 0; x < 15; x++) {
  addToInventory(items['Potion'].copy());
}*/

//dumpInventory();
