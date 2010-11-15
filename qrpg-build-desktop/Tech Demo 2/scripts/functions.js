function cprint(string) {
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
  //var object = createObject("../interface/talkbox.qml");
  ui.talkbox.append(string);
  
  //alert(ui.talkbox.text);
  ui.talkbox.show();
  //alert(object.Border.top);
  //alert("Name: " + object.objectName);
  //alert(object.text1.text);
}

function extend(obj1, obj2) {
  for (attrname in obj2) {
    obj1[attrname] = obj2[attrname];
  }
}

function newCharacter(name) {
  //o = newStatBlock();
  var o = createObject("../qml/Character.qml");
  o.itemType = 'Character';
  o.name = name;
  //rpgx.makeQmlGlobal(o);
  return o;
}

function newAbility(name) {
  var o = createObject("../qml/Ability.qml");
  o.name = name;
  return o;
}
