var ui = createObject("../../interface/ui.qml");

rpgx.debug("RUNNING startup.js");

// NOTE TO SELF:
// CAN I DEFINE THE CHARACTER AND OTHER SHARE-ABLE CLASSES IN QML AND THEN
// CREATE THEM THAT WAY?  THEN THEY SHOULD TRANSFER OVER TO THE GUI JUST
// FINE, AND I SHOULD STILL BE ABLE TO CALL THEIR FUNCTIONS


for(var i in party) {
  //rpgx.makeQmlGlobal(party[i]);
  ui.addPartyMember(party[i]);
}

ui.statusScreen.partyScreen.setCurrentPartyMember(0);

function toggleUi() {
  //party[0].equip(items['Dagger'], 'Weapon', 0);
  //party[0].atkChanged();
  ui.statusScreen.toggleVisible();
}

rpgx.menuKey.connect(toggleUi);

inventory.push(items['Staff'].copy());

for(var i = 0; i < 15; i++)
  inventory.push(items['Potion'].copy());

for(var i = 0; i < 15; i++)
  inventory.push(items['Green Tea'].copy());
