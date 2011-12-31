import Qt 4.7

Image {
  id: battleEnemy;
  property Item character;
  source: {
    if(character && character.portrait)
      character.portrait;
    else
      '';
  }

  onCharacterChanged: {
    if(character) {
      character.image = battleEnemy;
    }
  }

  Component.onCompleted: {
    console.log("created battle enemy: " + parent.foo );
  }

  MouseArea {
    anchors.fill: parent;
    onClicked: battleScreen.doTargetSelect(character);
  }


  SequentialAnimation {
    id: deathAnimation
    PropertyAnimation {
      target: battleEnemy;
      property: "opacity";
      to: 0;
      duration: 250
    }
    ScriptAction {
      script: {
        battleScreen.removeEnemy(battleEnemy);
        battleEnemy.destroy(300);
      }
    }
  }


  function die() {
    console.log(character.name + " is slain!")
    deathAnimation.start();
  }
}
