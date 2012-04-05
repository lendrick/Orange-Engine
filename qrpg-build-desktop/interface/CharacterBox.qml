import Qt 4.7
import "CharacterBox.js" as CharacterBoxScript

Box {
  id: characterBox
  property Item character
  property alias treeMenu: menuContainer.treeMenu
  property Item image

  //height: childrenRect.height
  //width: childrenRect.width

  state: "Show"
  height: 190
  width: 220

  onCharacterChanged: {
    if(character) {
      image = characterPortrait
    }
  }

  function showMenu() {
    CharacterBoxScript.startUp();
    treeMenu.show();
    console.log("showmenu for " + character.name);
  }

  Rectangle {
    id: menuContainer
    objectName: "menuContainer"

    anchors.right: parent.right
    anchors.top: parent.bottom
    state: "Show"
    property Item treeMenu
  }

  SequentialAnimation {
    id: hitAnimation
    ScriptAction {
      script: console.log("character hitAnimation")
    }

    ScriptAction {
      script: {
        //animImg.playing = false;
        //battleScreen.next();
      }
    }
  }

  MouseArea {
    anchors.fill: parent;
    onClicked: {
      console.log(characterBox.character.name + " clicked");
      battleScreen.doTargetSelect(characterBox.character);
    }
  }

  Column {
    id: c1
    objectName: "c1"
    x: 25
    y: 25
    //height: parent.height - 50
    //width: parent.width - 50
    spacing: 10

    height: childrenRect.height
    width: parent.width - 50


    Item {
      id: c2
      objectName: "c2"
      height: 56
      width: 200
      Image {
        objectName: "characterPortrait"
        id: characterPortrait
        source: {
          if(character && character.portrait)
            character.portrait;
          else
            '';
        }

        function hit(val, anim, text) {
          //CharacterScript.DamageNumberComponent.createObject(image, { text: val })

          if(text) {
            var message = Qt.createQmlObject("MessageBox { text: '" + text + "' }", battleScreen);
            message.Component.destruction.connect(battleScreen.next);
          }
          var animation = Qt.createQmlObject("import 'animations'; " + anim + " {}", characterPortrait);
          var number = Qt.createQmlObject("DamageNumber { amount: " + val + " }", characterPortrait);

          if(!text) {
            animation.Component.destruction.connect(battleScreen.next);
          }
          console.log("character hit()");
          hitAnimation.start();
        }
      }

      BindItem {
        x: 48
        id: characterName
        fmt.color: '#ff2'
        fmt.font.bold: true
        bind: if(character) character.name
      }
    }

    /*
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
    */

    ProgressBar {
      id: hpDisplay
      current: if(character) {character.hp} else {0}
      total: if(character) {character.current_maxHp} else {0}
      fgSource: "shinybar-green.png"
      bgSource: "bar-grey.png"
      anchors.left: parent.left
      anchors.right: parent.right
      text.color: 'white'
      text.font.pixelSize: 25
      text.font.family: "Liberation Mono"
      text.smooth: true

      height: 30
    }

    ProgressBar {
      id: mpDisplay
      current: if(character) {character.mp} else {0}
      total: if(character) {character.current_maxMp} else {0}
      fgSource: "shinybar-blue.png"
      bgSource: "bar-grey.png"
      anchors.left: parent.left
      anchors.right: parent.right
      text.color: 'white'
      text.font.pixelSize: 25
      text.font.family: "Liberation Mono"
      text.smooth: true
      height: 30
    }
  }


}
