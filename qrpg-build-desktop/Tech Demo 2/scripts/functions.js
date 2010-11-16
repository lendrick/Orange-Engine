ui = createObject("../../interface/Ui.qml");

function cprint(string) {
  rpgx.print(string);
}

function alert(string) {
  rpgx.alert(string);
}

function createObject(qmlFile, parent) {
  //print("Creating " + qmlFile);
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
  console.log("New character " + name);
  //var o = createObject("../qml/Character.qml");
  var o = ui.newCharacter(name);
  o.itemType = 'Character';
  //o.name = name;
  //rpgx.makeQmlGlobal(o);
  return o;
}

function newAbility(name) {
  var o = Object();
  o.name = name;
  o.targetSelf = false;
  o.targetFriends = false;
  o.targetEnemies = false;
  o.targetMultiple = false;
  o.usableInBattle = false;
  o.usableOutsideBattle = false;
  o.mpcost = 0;

  o.activate = function(user, targets) {
    console.log(caster.name + " uses " + this.name + " on " + targets[0].name +
                " (ABILITY.ACTIVATE() FUNCTION NOT IMPLEMENTED)");
  }

  return o;
}
