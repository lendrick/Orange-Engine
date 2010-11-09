var ui = createObject("../../interface/ui.qml");

//rpgx.makeQmlGlobal(party[0]);

var test = new BindObject();
test['hello'] = "yo";
print("HELLO: " + test['hello']);

rpgx.makeQmlGlobal(test);

for(var i in party) {
  rpgx.makeQmlGlobal(party[i]);
  ui.addPartyMember(party[i]);
}

ui.statusScreen.partyScreen.setCurrentPartyMember(0);

ui.statusScreen.show();
