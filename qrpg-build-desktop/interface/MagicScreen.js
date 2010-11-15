var CharacterMagicScreenComponent;
var characterMagicScreens;

function startUp() {
  rpgx.debug("CHARACTER SCREEN LOADING");
  CharacterMagicScreenComponent = Qt.createComponent("CharacterScreen.qml");
  characterMagicScreens = Array();
  console.log("magic screen initialized");
}

function newMagicScreen(parent) {
  console.log("creating character screen");
  console.log(CharacterMagicScreenComponent.status + " " + Component.Ready);
  var scr = CharacterMagicScreenComponent.createObject(parent);
  console.log("screen created");
  return scr;
}
