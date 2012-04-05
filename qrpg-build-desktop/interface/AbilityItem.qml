import Qt 4.7

Item {
  height: 34
  property alias text: txt.text
  property alias portrait: img.source
  property alias color: txt.color
  width: parent.width / 2
  property bool usable
  property string ability
  id: abilityItem;

  onAbilityChanged: updateAbility();
  Component.onCompleted: updateAbility();

  function updateAbility() {
    console.log("Ability updated");
    if(ability) {
      usable = allAbilities[ability].useOutsideBattle &&
          characterMagicScreen.character.mp >= allAbilities[ability].mpCost;
      console.log(allAbilities[ability].name + " " + usable);
    } else {
      usable = false;
    }
    if(usable)
      color = '#fff';
    else
      color = '#999';
  }

  //onItemChanged: if(item) text = item.name;

  onUsableChanged: {
    console.log("update color: " + usable);
    if(usable)
      color = '#fff';
    else
      color = '#999';
  }

  Image {
    id: img
  }

  SmallText {
    id: txt
    anchors.left: img.right
    anchors.verticalCenter: img.verticalCenter
    //text: if(item) { item.name }
    width: parent.width / 2;
    wrapMode: Text.NoWrap
  }

  MouseArea {
    id: mouseArea
    anchors.fill: parent;
    onClicked: {
      sfx.menublip.play();
      abilityItem.displayMenu(mouse);
    }
    z: 50
    hoverEnabled: true;
    visible: abilityItem.usable;

    onEntered: {
      console.log("hover enter " + abilityItem.text.color);
      abilityItem.color = "#ff2";
    }

    onExited: {
      console.log("hover exit");
      abilityItem.color = "#fff";
    }
  }

  function displayMenu(e) {
    var options = new Object();
    var tree = flatTree(characters);
    //console.log(serialize(tree));
    var menu = ui.treeMenu(ui.popups, tree);
    menu.x = x + e.x;
    menu.y = y + e.y;
    //menu.z = 200;
    menu.callback = abilityItem;
    console.log("show menu");
    menu.show();
  }

  function treeSelect(i) {
    var character = characterMagicScreen.character;
    console.log("treeSelect: " + i.name + character.name);
    if(character.mp >= allAbilities[ability].mpCost) {
      character.mp -= allAbilities[ability].mpCost;
      allAbilities[ability].activate(character, Array(i));
      updateAbility();
      console.log("treeSelect(): used " + ability);
    }
  }
}
