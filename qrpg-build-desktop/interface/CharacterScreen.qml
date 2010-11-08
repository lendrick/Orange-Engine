import Qt 4.7
//import "CharacterScreen.js" as CharacterScreenScript

Box {
  id: characterScreen
  width: 440
  height: 380
  x: 0
  y: 100
  state: "Hide"
  property variant character

  function setPartyMember(c) {
    console.log("Setting party member to " + c.name);
    utils.debugObject(c);
    character = c;
    console.log("creating bindings");
    console.log(utils);
    //utils.setObjectProperty(c, "def", 30);
    utils.test();
    console.log("DEF: " + c.def);

    console.log("done");
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
        bind: character.name
      }

      BindItem {
        id: classDisplay
        bind: character.cls + " " + character.level
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
        bind: character.currentHp + " / " + character.hp
      }

      StatItem {
        id: mpDisplay
        title: "MP"
        bind: character.currentMp + " / " + character.mp
      }

      Item {
        id: statSpacer2
        height: 20
        width: 1
      }

      StatItem {
        id: strDisplay
        title: "Atk"
        bind: character.atk
      }

      StatItem {
        id: defDisplay
        title: "Def"
        bind: character.def
      }

      StatItem {
        id: matkDisplay
        title: "MAtk"
        bind: character.matk
      }

      StatItem {
        id: mdefDisplay
        title: "MDef"
        bind: character.mdef
      }

      StatItem {
        id: spdDisplay
        title: "Spd"
        bind: character.spd
      }

      StatItem {
        id: dexDisplay
        title: "Dex"
        bind: character.dex
      }
    }

    Column {
      height: parent.height
      width: parent.width / 2 - 25
      x: parent.width / 2 + 25


    }
  }
}
