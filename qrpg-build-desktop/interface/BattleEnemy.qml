import Qt 4.7

Image {
  id: battleEnemy;
  property Item character;
  property string status: "normal"
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

  ParallelAnimation {
    id: deathAnimation
    PropertyAnimation {
      target: battleEnemy
      property: "scale"
      to: 0
      easing.type: Easing.InElastic
      duration: 500
    }

    SequentialAnimation {

      PauseAnimation {
        duration: 500
      }
      /*
      PropertyAnimation {
        target: battleEnemy;
        property: "opacity";
        to: 0;
        duration: 100
      }
      */
      ScriptAction {
        script: {
          battleScreen.removeEnemy(battleEnemy);
          battleEnemy.destroy(300);
        }
      }
    }
  }

  SequentialAnimation {
    id: hitAnimation
    PropertyAnimation {
      target: battleEnemy
      property: "scale"
      to: .7
      easing.type: Easing.OutQuart
      duration: 100
    }
    PropertyAnimation {
      target: battleEnemy
      property: "scale"
      to: 1
      easing.type: Easing.InQuart
      duration: 100
    }
  }

  function die() {
    status = "dead";
    console.log(character.name + " is slain!")
    hitAnimation.stop();
    deathAnimation.start();
  }

  function hit() {
    hitAnimation.start();
  }
}
