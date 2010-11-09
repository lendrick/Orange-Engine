var CharacterScreenComponent;
var characterScreens;

function startUp() {
  CharacterScreenComponent = Qt.createComponent("CharacterScreen.qml");
  characterScreens = Array();
  console.log("character screen initialized");
}

function newCharacterScreen(parent) {
  console.log("creating character screen");
  console.log(CharacterScreenComponent.status + " " + Component.Ready);
  var scr = CharacterScreenComponent.createObject(parent);
  console.log("screen created");
  return scr;
}
