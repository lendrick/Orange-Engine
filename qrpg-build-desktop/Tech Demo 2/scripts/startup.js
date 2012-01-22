
rpgx.debug("RUNNING startup.js");

// NOTE TO SELF:
// CAN I DEFINE THE CHARACTER AND OTHER SHARE-ABLE CLASSES IN QML AND THEN
// CREATE THEM THAT WAY?  THEN THEY SHOULD TRANSFER OVER TO THE GUI JUST
// FINE, AND I SHOULD STILL BE ABLE TO CALL THEIR FUNCTIONS


for(var i in party) {
  ui.addPartyMember(party[i]);
}


// var foo = new Object();
// foo.test = function() {
//     console.log("FOO TEST");
// }
// foo.blah = "blah";
// console.log("blah: " + foo.balqobh);
// ui.testMe(foo);
/*
console.log("****************UI DUMP");
rpgx.dumpScriptObject(ui);

var foo = new Object();
foo.test = function() {
    console.log("FOO TEST");
}
foo.blah = "blah";
console.log("blah: " + foo.blah);
ui.testMe(foo);
ui.self().testMe(foo);
var rt = ui.testMe;
console.log("type ui: " + typeof ui);
console.log("type ui.self(): " + typeof ui.self());
console.log("type rt: " + typeof rt);
rt(foo);
*/

ui.statusscreen.partyscreen.setCurrentPartyMember(0);
ui.statusscreen.magicscreen.setCurrentPartyMember(0);
ui.callbackTest(function() {
    console.log("************************** PLEASE WORK *******************************");
});

function toggleUi() {
  //dumpInventory();
  //ui.statusscreen.toggleVisible();
  console.log("toggleUi");
  ui.toggleStatusScreen();
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
