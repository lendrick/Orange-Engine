var ui = createObject("../../interface/ui.qml");

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
  ui.statusScreen.toggleVisible();
}

rpgx.menuKey.connect(toggleUi);
