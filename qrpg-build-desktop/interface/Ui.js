var TalkBoxTextComponent;
var textBoxArray;
var CharacterComponent;
var TreeMenuComponent;

function startUp() {
  CharacterComponent = Qt.createComponent("Character.qml");
  TalkBoxTextComponent = Qt.createComponent("TalkBoxText.qml");
  TreeMenuComponent = Qt.createComponent("TreeMenu.qml");
  textBoxArray = Array();
}

function appendText(string) {
  console.log("adding dialog");
  var object = TalkBoxTextComponent.createObject(talkbox);
  object.text = string;
  //console.log("object created");
  textBoxArray.push(object);
  //talkbox.textArray[0] = object;
  //console.log("text appended " + talkbox.textArray.length);
}

function appendScript(string, script) {
  console.log("adding dialog w/ script");
  var object = TalkBoxTextComponent.createObject(talkbox);
  object.text = string;
  object.setCallback(script);
  textBoxArray.push(object);
}
