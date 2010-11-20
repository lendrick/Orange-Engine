ui = createObject("../../interface/Ui.qml");
var items = Array();
var inventory = Array();

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

function sizeof(obj) {
  if(typeof(obj) != 'object') {
    //console.log("sizeof: " + typeof(obj) + " " + obj);
    return 0;
  }
  var count = 0;
  for(var i in obj) {
    //console.log("sizeof: " + i + " " + typeof(obj) + " " + obj[i]);
    count++;
  }
  return count;
}

function merge(obj1, obj2) {
  if(sizeof(obj2) > 0) {
    for(var i in obj2)
      merge(obj1[i], obj2[i]);
  } else if(sizeof(obj1) == 0) {
    obj1 = obj2;
  }

  // Do nothing if obj1 is an object and obj2 is not.
}

function addBranch(obj, arr, value) {

  if(arr.length == 0) {
    return obj;
  } else if(arr.length == 1) {
    var key = arr.shift();
    obj[key] = value;
    //console.log("Leaf: " + obj);
  } else {
    var key = arr.shift();
    //console.log("Node: " + key);
    if(sizeof(obj[key]) == 0) obj[key] = new Object();
    obj[key] = addBranch(obj[key], arr, value);
  }

  return obj;
}



function newCharacter(name) {
  console.log("New character " + name);
  //var o = createObject("../qml/Character.qml");
  var o = ui.newCharacter(name);
  o.setType('character');
  //o.name = name;
  //rpgx.makeQmlGlobal(o);
  return o;
}

function newAbility(name) {
  var o = Object();
  o.name = name;
  o.displayName = name;
  o.description = '';
  o.targetSelf = false;
  o.targetFriends = false;
  o.targetEnemies = false;
  o.targetMultiple = false;
  o.usableInBattle = false;
  o.usableOutsideBattle = false;
  o.mpcost = 0;
  o.description = '';
  o.menuPath = Array();
  o.isAbility = true;

  o.condition = function() {
    return true;
  }

  o.activate = function(user, targets) {
    console.log(caster.name + " uses " + this.name + " on " + targets[0].name +
                " (ABILITY.ACTIVATE() FUNCTION NOT IMPLEMENTED)");
  }

  return o;
}

function addToInventory(item) {
  var added = false;
  for(var x = 0; x < inventory.length; x++) {
    if(!inventory[x]) {
      inventory[x] = item;
      added = true;
      //console.log(x + " " + empty);
    } else {
      //console.log(x + " " + inventory[x].name);
    }
  }
  if(!added) inventory.push(item);
}

function dumpInventory() {
  for(var i in inventory) {
    var name;
    if(inventory[i]) {
      try {
        name = inventory[i].name;
      }
      catch(e) {
        name = '';
      }
    } else {
      name = '';
    }

    console.log(i + ": " + name);
  }
}

function JavaScriptStringEncode(sString) {
        return (sString+"").replace(/[\0-\x1F\"\\\x7F-\xA0\u0100-\uFFFF]/g, function (sChar) {
                switch (sChar) {
                        case "\b": return "\\b";
                        case "\t": return "\\t";
                        case "\n": return "\\n";
                        case "\f": return "\\f";
                        case "\r": return "\\r";
                        case "\\": return "\\\\";
                        case "\"": return "\\\"";
                }
                var iChar = sChar.charCodeAt(0);
                if (iChar < 0x10) return "\\x0" + iChar.toString(16);
                if (iChar < 0x100) return "\\x" + iChar.toString(16);
                if (iChar < 0x1000) return "\\u0" + iChar.toString(16);
                return "\\u" + iChar.toString(16);
        });
}

function serialize(xValue) {
        switch (typeof(xValue)) {
                case "undefined": return "void(0)";
                case "boolean":   return xValue.toString();
                case "number":    return xValue.toString();
                case "string":    return "\"" + JavaScriptStringEncode(xValue) + "\"";
                case "function":  return "eval(\"" + JavaScriptStringEncode(xValue.toString()) + "\")";
                case "object":
                        if (xValue == null) return "null";
                        var bArray = true;
                        var asObjectValues = [], asArrayValues = [], iCounter = 0, iLength = null;
                        for (var i in xValue) {
                                if (bArray) switch (i) {
                                        case "length":
                                                // Part of an array but not stored, keep so we can check
                                                // if the length is correct
                                                break;
                                        case iCounter.toString():
                                                // Part of an array and stored, but he index must be sequential starting at 0.
                                                iCounter++;
                                                asArrayValues.push(serialize(xValue[i]));
                                                break;
                                        default:
                                                // Not an array
                                                bArray = false;
                                }
                                asObjectValues.push(serialize(i) + ":" + serialize(xValue[i]));
                        }
                        if (bArray) {
                                try {
                                        bArray &= (xValue.length == iCounter);
                                } catch (e) {
                                        bArray = false;
                                }
                        }
                        return (bArray ?
                                "[" + asArrayValues.join(",") + "]":
                                "{" + asObjectValues.join(",") + "}"
                        );
                default:
                        throw new Error("Objects of type " + typeof(xValue) + " cannot be serialized.");
        }
}
