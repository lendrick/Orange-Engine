var uiComponent = createObject("../interface/Ui.qml");
ui = uiComponent.createObject(mapBox);
mapScene.addItem(ui);
var items = Array();
var inventory = Array();
var allAbilities = Array();
var currentBGM;
var BGMStack = Array();
var flags = new Object();
ui.gold = 500;

function playBGM(name) {
    console.log("playBGM: " + name);
    var bgm = allSounds[name];
    if(bgm) {
        BGMStack = Array();
        if(bgm && bgm.isPlaying()) {
            return;
        }
        
        _playBGM(name);
    } else {
        console.log("No music named " + name);
    }
}

function menu(caption, options, callback) {
    var m = ui.treeMenu(ui.popups, flatTree(options))
    m.setCallback(callback);
    m.caption = caption;
    m.center();
    m.show();
}

function _playBGM(name) {
    if(allSounds[currentBGM]) {
        allSounds[currentBGM].stop();
    }
    currentBGM = name;
    allSounds[currentBGM].setLoop(true);
    allSounds[currentBGM].play();
}

function pushBGM(name) {
    console.log("pushBGM: " + name);
    var bgm = allSounds[name];
    if(bgm) {
        if(allSounds[currentBGM] && allSounds[currentBGM].isPlaying) {
            console.log("Pushing BGM " + currentBGM + " onto stack");
            BGMStack.push(currentBGM);
        }
        _playBGM(name);
    } else {
        console.log("No music named " + name);
    }
}

function popBGM() {
    console.log("popBGM");
    if(BGMStack.length > 0) {
        var name = BGMStack[0];
        BGMStack.pop();    
        console.log("Popped BGM " + name);
        _playBGM(name);
    } else {
        console.log("BGM stack is empty");
        allSounds[currentBGM].stop();
    }
}

function playSound(name) {
    var sound = allSounds[name];
    if(sound) {
        sound.play();
    } else {
        console.log("No sound named " + sound);
    }
}

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

function sayScript(string, script) {
  ui.talkbox.appendScript(string, script);
  ui.talkbox.show();
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

function flatTree(o) {
  var tree = new Object();
  for(var i in o) {
    tree[i] = new Object();
    tree[i]['$treetype'] = 'leaf';
    tree[i]['$value'] = o[i];
  }
  return tree;
}

function addBranch(obj, arr_orig, value) {

  var arr = new Array();

  for(var x = 0; x < arr_orig.length; x++) {
    arr.push(arr_orig[x]);
  }

  if(arr.length == 0) {
    return obj;
  } else if(arr.length == 1) {
    var key = arr.shift();
    obj[key] = new Object();
    obj[key]['$treetype'] = 'leaf';
    obj[key]['$value'] = value;
    //console.log("Leaf: " + obj);
  } else {
    var key = arr.shift();
    //console.log("Node: " + key);
    if(sizeof(obj[key]) == 0) {
      obj[key] = new Object();
      obj[key]['$value'] = new Object();
    }
    obj[key]['$treetype'] = 'node';
    obj[key]['$value'] = addBranch(obj[key]['$value'], arr, value);
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
  o.mpCost = 0;
  o.description = '';
  o.menuPath = null;
  o.isAbility = true;
  o.portrait = '';

  o.condition = function() {
    return true;
  }

  o.activate = function(user, targets) {
    console.log(caster.name + " uses " + this.name + " on " + targets[0].name +
                " (ABILITY.ACTIVATE() FUNCTION NOT IMPLEMENTED)");
  }

  return o;
}

function addNewItem(name) {
  if(!items[name]) {
    console.log("No item named " + name);
    return;
  }
  addToInventory(items[name].copy());
}

function addToInventory(item) {
  var added = false;
  console.log("addToInventory: " + item.name);
  for(var x = 0; x < inventory.length; x++) {
    if(!inventory[x]) {
      //console.log("addToInventory: " + x + " is empty");
      inventory[x] = item;
      //console.log("setting invIndex");
      item.setInvIndex(x);
      //console.log("setting added to true");
      added = true;
    } else {
      //console.log("addToInventory: " + x + " is occupied");
      var name;
      try {
        //console.log("addToInventory: " + x + " has item");
        name = inventory[x].name;
      } catch(e) {
        //console.log("addToInventory: " + x + " has deleted object");
        name = null;
      }

      if(!name) {
        //console.log("addToInventory: adding to slot " + x);
        inventory[x] = item;
        added = true;
      }

      //console.log(x + " " + inventory[x].name);
    }
    if(added) x = inventory.length;
  }
  if(!added) {
    //console.log("addToInventory: appending in slot " + inventory.length);
    inventory.push(item);
    item.setInvIndex(inventory.length - 1);
  }

  //console.log("addToInventory done");
}

function removeFromInventory(item) {
  console.log("removeFromInventory: " + item.name + " " + item.invIndex);
  if(item.invIndex >= 0) {
    inventory[item.invIndex] = null;
    item.setInvIndex(-1);
  }
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

function serialize(obj) {
  return JSON.stringify(obj, null, '\t');
}

function battle(enemyParty) {
  console.log("initiating battle: " + enemyParty);
  var p = enemyParties[enemyParty];
  ui.battle(p);
}

function healAll() {
    for(var c in characters) {
        characters[c].heal();
    }
}

function loadItems(file) {
    console.log("Loading items from " + file);
    var data = rpgx.loadJSON(file).rows;
    //console.log(serialize(data));
    for(var i in data) {
        var itemData = data[i];
        var name = itemData.name;
        
        console.log("loading item: " + name);
        console.log(serialize(types));
        
        var item = newCharacter(name);

        delete itemData.name;
        
        if(itemData.types !== null) {
            var types = itemData.types.split(" ");
            item.setTypes(types);            
            delete itemData.types;
        }
        
        if(itemData.portrait !== null) {
            itemData.portrait = rpgx.projectDir() + "/" + itemData.portrait;
        }
        
        for(var prop in itemData) {
            if(itemData[prop] !== null) {
                item[prop] = itemData[prop];
                console.log("  " + prop + ": " + item[prop]);
            }
        }
        items[name] = item;
    }
    console.log("Items loaded!");
}

function loadEnemies(file) {
    console.log("Loading enemies from " + file);
    var data = rpgx.loadJSON(file).rows;
    //console.log(serialize(data));
    for(var i in data) {
        var itemData = data[i];
        var name = itemData.name;
        
        console.log("loading enemy: " + name);
        
        var item = newCharacter(name);
        
        delete itemData.name;

        if(itemData.abilities !== null) {
            var abilities = itemData.abilities.split(" ");
            item.addAbilities(abilities);
            delete itemData.abilities;
        }
        
        if(itemData.portrait !== null) {
            itemData.portrait = rpgx.projectDir() + "/" + itemData.portrait;
        }
        
        for(var prop in itemData) {
            if(itemData[prop] !== null) {
                item[prop] = itemData[prop];
                console.log("  " + prop + ": " + item[prop]);
            }
        }
        
        item.heal();
        enemies[name] = item;
    }
    console.log("Enemies loaded!");
}

function loadCharacters(file) {
    console.log("Loading characters from " + file);
    var data = rpgx.loadJSON(file).rows;
    //console.log(serialize(data));
    for(var i in data) {
        var itemData = data[i];
        var name = itemData.name;
        var start_exp = 0;
        var levels;
        
        console.log("loading character: " + name);
        
        var character = newCharacter(name);
        
        delete itemData.name;
        
        if(itemData.portrait !== null) {
            itemData.portrait = rpgx.projectDir() + "/" + itemData.portrait;
        }

        if(itemData.start_exp !== null) {
            start_exp = itemData.start_exp;
            delete itemData.start_exp;
        }
        
        if(itemData.levels !== null) {
            levels = itemData.levels;
            delete itemData.levels;
        }

        if(itemData.slots !== null) {
            var slots = itemData.slots.split(/\s*\n\s*/);
            for(i in slots) {
                var slot = slots[i].split(/:\s*/);
                var slotData = slot[0].split(/\s+/);
                var num = slotData[0];
                var slotName = slotData[1];
                var slotTypes = slot[1].split(/\s+/);
                character.addSlots(slotName, num, slotTypes);
            }
            delete itemData.slots;
        }

        if(itemData.equipment !== null) {
            var equipment = itemData.equipment.split(/\s*\n\s*/);
            for(i in equipment) {
                var thing = equipment[i].split(/:\s*/);
                var itemSlot = thing[0];
                var itemName = thing[1];
                character.equip(items[itemName].copy(), itemSlot, 0);
            }
            delete itemData.equipment;
        }
        
        for(var prop in itemData) {
            if(itemData[prop] !== null) {
                character[prop] = itemData[prop];
                console.log("  " + prop + ": " + character[prop]);
            }
        }
        
        characters[name] = character;        
        loadLevels(name, levels);
        characters[name].addExp(start_exp);
    }
    console.log("Characters loaded!");
}

function loadLevels(character, file) {
    console.log("Loading level file for " + character);
    var data = rpgx.loadJSON(file).rows;
    var levels = new Object();
    
    for(i in data) {
        var level = data[i].level;
        delete data[i].level;

        if(data[i].abilities !== null) {
            data[i].abilities = data[i].abilities.split(" ");
        }
        levels[level] = data[i];
    }
        
    characters[character].levels = levels;
}

function random(max) {
    return Math.floor(Math.random() * max);
}

function shop(items) {
}

function wander(npc) {
    var distance = random(100) + 50;
    if(random(2) == 0) {
        distance = -distance;
    }
    if(random(2) == 0) {
        npc.queueMove(0, distance, 20);
    } else {
        npc.queueMove(distance, 0, 20);
    }
    npc.queueWait(1);
    npc.queueScript(function() { wander(this) });
}

/*
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
*/
