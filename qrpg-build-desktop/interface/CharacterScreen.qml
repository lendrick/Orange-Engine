import Qt 4.7
//import "CharacterScreen.js" as CharacterScreenScript

Box {
  id: characterScreen
  width: parent.width
  height: parent.height - 100
  x: 0
  y: 100
  state: "Hide"
  property variant character

  function setPartyMember(c) {
    //console.log("Setting party member to " + c.name);
    //utils.debugObject(c);
    character = c;
    //console.log("creating bindings");
    //console.log(utils);
    //utils.setObjectProperty(c, "def", 30);
    //utils.test();
    //console.log("DEF: " + c.def);

    //console.log("done");
  }

  function newBinding(parent) {
    return Qt.createQmlObject("import Qt 4.7; Binding { when: true }", parent);
  }

  Item {
    id: statContainer
    x: 25
    y: 25
    width: parent.width - 50
    height: parent.height - 50

    Column {
      height: parent.height
      width: parent.width / 2 - 25

      BindItem {
        id: characterName
        fmt.color: '#ff2'
        fmt.font.bold: true
        bind: if(character) character.name
      }

      BindItem {
        id: classDisplay
        bind: if(character) character.cls + " " + character.level
        fmt.font.bold: true
      }

      Item {
        id: statSpacer1
        height: 20
        width: 1
      }

      StatItem {
        id: hpDisplay
        title: "HP"
        bind: if(character) character.hp + " / " + character.current_maxHp;
      }

      StatItem {
        id: mpDisplay
        title: "MP"
        bind: if(character) character.mp + " / " + character.current_maxMp;
      }

      Item {
        id: statSpacer2
        height: 20
        width: 1
      }

      StatItem {
        id: strDisplay
        title: "Atk"
        bind: if(character) character.current_atk;
      }

      StatItem {
        id: defDisplay
        title: "Def"
        bind: if(character) character.current_def;
      }

      StatItem {
        id: matkDisplay
        title: "MAtk"
        bind: if(character) character.current_matk;
      }

      StatItem {
        id: mdefDisplay
        title: "MDef"
        bind: if(character) character.current_mdef;
      }

      StatItem {
        id: spdDisplay
        title: "Spd"
        bind: if(character) character.current_spd;
      }

      StatItem {
        id: dexDisplay
        title: "Dex"
        bind: if(character) character.current_dex;
      }
    }

    Column {
      height: parent.height
      width: parent.width / 2 - 25
      x: parent.width / 2 + 25

      Item {
        id: statSpacer3
        height: 25
        width: 1
      }

      SlotItem {
        id: weaponSlot0
        title: "Weapon"
        bind: {
          if(character && character.getSlot("Weapon", 0).item)
            character.getSlot("Weapon", 0).item.name;
          else
            'none';
        }
        slot: if(character) character.getSlot("Weapon", 0); else null;
      }

      SlotItem {
        id: offHandSlot0
        title: "OffHand"
        bind: {
          if(character && character.getSlot("OffHand", 0).item)
            character.getSlot("OffHand", 0).item.name;
          else
            'none';
        }
        slot: if(character) character.getSlot("OffHand", 0); else null;
      }

      SlotItem {
        id: armorSlot0
        title: "Armor"
        bind: if(character && character.getSlot("Armor", 0).item) character.getSlot("Armor", 0).item.name; else 'none';
        slot: if(character) character.getSlot("Armor", 0); else null;
      }

      SlotItem {
        id: accessorySlot0
        title: "Accessory"
        bind: if(character && character.getSlot("Accessory", 0).item) character.getSlot("Accessory", 0).item.name; else 'none';
        slot: if(character) character.getSlot("Accessory", 0); else null;
      }

      SlotItem {
        id: accessorySlot1
        title: "Accessory"
        bind: if(character && character.getSlot("Accessory", 1).item) character.getSlot("Accessory", 1).item.name; else 'none';
        slot: if(character) character.getSlot("Accessory", 1); else null;
      }
    }
  }
}
