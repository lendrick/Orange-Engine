var ui = createObject("../../interface/ui.qml");

// NOTE TO SELF:
// CAN I DEFINE THE CHARACTER AND OTHER SHARE-ABLE CLASSES IN QML AND THEN
// CREATE THEM THAT WAY?  THEN THEY SHOULD TRANSFER OVER TO THE GUI JUST
// FINE, AND I SHOULD STILL BE ABLE TO CALL THEIR FUNCTIONS


rpgx.makeQmlGlobal(ui);
ui.rotation = 10;

var test = new BindObject();
test['hello'] = "yo";
print("HELLO: " + test['hello']);

//rpgx.makeQmlGlobal(test);

for(var i in party) {
  //rpgx.makeQmlGlobal(party[i]);
  ui.addPartyMember(party[i]);
}

ui.statusScreen.partyScreen.setCurrentPartyMember(0);

ui.statusScreen.show();
