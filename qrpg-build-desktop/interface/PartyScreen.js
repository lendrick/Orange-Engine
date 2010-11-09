var CharacterScreenComponent;
var characterScreens;

var ImageMenuItemComponent;
var menuItems;

function startUp() {
  CharacterScreenComponent = Qt.createComponent("CharacterScreen.qml");
  characterScreens = Array();
  console.log("character screen initialized");

  ImageMenuItemComponent = Qt.createComponent("ImageMenuItem.qml");
  menuItems = Array();
}

function newCharacterScreen(parent) {
  console.log("creating character screen");
  console.log(CharacterScreenComponent.status + " " + Component.Ready);
  var scr = CharacterScreenComponent.createObject(parent);
  console.log("screen created");
  return scr;
}

function newPortrait(parent) {
  var port = ImageMenuItemComponent.createObject(parent);
  return port;
}
