
rpgx.debug("RUNNING startup.js");

for(var i in party) {
  ui.addPartyMember(party[i]);
}

ui.statusscreen.partyscreen.setCurrentPartyMember(0);
ui.statusscreen.magicscreen.setCurrentPartyMember(0);

function toggleUi() {
  //dumpInventory();
  //ui.statusscreen.toggleVisible();
  console.log("toggleUi");
  ui.toggleStatusScreen();
  //dumpInventory();
}

rpgx.menuKey.connect(toggleUi);
//console.log("inv " + inventory.length);

addNewItem('Wooden Staff');
addNewItem('Potion');
addNewItem('Potion');
addNewItem('Green Tea');

inventory[1].activateUseAbility(party[1], Array(party[0]));

