import Qt 4.7
import "animations"

Image {
  id: battleEnemy;
  property Item character;
  property string status: "normal"
  state: "Ready"

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
    property Item callback;

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
          battleScreen.next();
        }
      }
    }
  }

  SequentialAnimation {
    id: hitAnimation

    ScriptAction {
      script: console.log("hitAnimation");
    }

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
    ScriptAction {
      script: {
        //animImg.playing = false;
        //battleScreen.next();
      }
    }
  }

  AnimatedImage {
    id: animImg
    playing: false
    anchors.centerIn: parent
  }

  function die() {
    status = "dead";
    console.log(character.name + " is slain!")
    hitAnimation.stop();
    deathAnimation.start();
  }

  function hit(val, anim, text) {
    //CharacterScript.DamageNumberComponent.createObject(image, { text: val })
    var animation = Qt.createQmlObject("import 'animations'; " + anim + " {}", battleEnemy);
    var number = Qt.createQmlObject("DamageNumber { amount: " + val + " }", battleEnemy);
    if(text) {
      var message = Qt.createQmlObject("MessageBox { text: '" + text + "' }", battleScreen);
      message.Component.destruction.connect(battleScreen.next);
    } else {
      animation.Component.destruction.connect(battleScreen.next);
    }
    hitAnimation.start();
  }
}
