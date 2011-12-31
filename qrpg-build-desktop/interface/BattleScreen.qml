import Qt 4.7
import "BattleScreen.js" as BattleScreenScript

HideShowContainer {
  id: battleScreen
  anchors.fill: parent
  Component.onCompleted: BattleScreenScript.startUp();
  property Item selectedTarget;
  property alias boxes: enemyBoxRow;

  function setParty(p) {
    /*
    for(i in BattleScreenScript.enemyParty) {
      var e = BattleScreenScript.enemyParty.shift();
      e.destroy();
    }
    */

    console.log("Setting enemy party.");

    var party = enemyParties[p];
    for(i in party) {
      console.log("  enemy: " + party[i]);
      BattleScreenScript.enemyParty.push(BattleScreenScript.newBattleEnemy(enemyBoxRow.boxes, party[i]));
    }
  }

  function start() {
    turn();
  }

  function next() {
    BattleScreenScript.nextCombatant();
    turn();
  }

  function turn() {
    if(BattleScreenScript.enemyParty.length == 0) {
      state = "Hide";
    } else {
      for(var i = BattleScreenScript.enemyParty.length - 1; i >= 0; i--) {
        console.log(BattleScreenScript.enemyParty[i].character.name + " hp: " + BattleScreenScript.enemyParty[i].character.hp)
        if(BattleScreenScript.enemyParty[i].character.hp == 0) {
          BattleScreenScript.enemyParty[i].die();
        }
      }

      if(BattleScreenScript.currentTurn == "Characters") {
        console.log("showing menu for " + BattleScreenScript.characterBoxes[BattleScreenScript.currentIndex].character.name);
        BattleScreenScript.characterBoxes[BattleScreenScript.currentIndex].showMenu();
      } else {

      }
    }
  }

  Keys.onPressed: {
    if(state == "Show") {
      event.accepted = true;
      state = "Hide";
    }
  }

  onStateChanged: {
    if(state == "Show") {
      focus = true;
      console.log("showing battle screen");
      for(i = 0; i < party.length; i++) {
        console.log("creating box for " + party[i].name);
        var box = BattleScreenScript.characterBoxComponent.createObject(partyBoxes);
        box.character = party[i];
        BattleScreenScript.characterBoxes.push(box);
        console.log("created box for " + box.character.name);
      }
    }

    if(state == "Hide") {
      focus = false;
      for(i = 0; i < BattleScreenScript.characterBoxes.length; i++) {
        var box = BattleScreenScript.characterBoxes.pop();
        x.destroy(300);
      }
    }
  }

  Rectangle {
    anchors.fill: parent
    color: '#000'
    opacity: .5
  }

  Column {
    id: partyBoxes
    anchors.left: parent.left
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    width: parent.width / 4
  }

  Item {
    id: enemyBoxRow
    objectName: 'enemyBoxRow'
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.right: parent.right
    anchors.left: partyBoxes.right
    property alias boxes: enemyBoxes;

    Row {
      id: enemyBoxes
      objectName: 'boxes'
      anchors.centerIn: parent
      spacing: 32
    }
  }

  function removeEnemy(e) {
    var idx = BattleScreenScript.enemyParty.indexOf(e);
    console.log("removing index " + idx)
    if(idx!=-1) {
      BattleScreenScript.enemyParty.splice(idx, 1);
    }
  }

  function doTargetSelect(target) {
    console.log("doTargetSelect: " + target.name);
    selectedTarget = target;
    selectTarget();
  }

  signal selectTarget()
}
