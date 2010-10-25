function print(string) {
  rpgx.print(string);
}

function alert(string) {
  rpgx.alert(string);
}

function createObject(qmlFile, parent) {
  print("Creating " + qmlFile);
  if(parent) {
    return rpgx.createComponent(qmlFile, parent);
  } else {
    return rpgx.createComponent(qmlFile);
  }
}

function say(string) {
  var object = createObject("../interface/talkbox.qml");
  object.text1.text = string;
  object.state = "Show";
  //alert(object.Border.top);
  //alert("Name: " + object.objectName);
  //alert(object.text1.text);
}
