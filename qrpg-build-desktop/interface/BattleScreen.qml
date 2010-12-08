import Qt 4.7
import "BattleScreen.js" as BattleScreenScript

HideShowContainer {
  id: battleScreen
  anchors.fill: parent
  Component.onCompleted: BattleScreenScript.startUp();
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

  Keys.onPressed: {
    if(state == "Show") {
      event.accepted = true;
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

}
