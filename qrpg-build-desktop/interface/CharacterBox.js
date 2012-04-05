var TreeMenuComponent;
var currentAbility;

function abilitySelected() {
  currentAbility = characterBox.treeMenu.getSelectedItem();
  //console.log(characterBox.character.name + " selected: " + serialize(currentAbility));

  if(currentAbility.targetEnemies && currentAbility.targetFriends) {

  } else if(currentAbility.targetEnemies) {

  } else if(currentAbility.targetFriends) {

  } else {
    allAbilities[currentAbility.name].activate(characterBox.character);
    return;
  }

  characterBox.treeMenu.hide();
  battleScreen.selectTarget.connect(targetSelected);
}

function targetSelected() {
  var target = battleScreen.selectedTarget;
  console.log("target selected: " + target.name);
  allAbilities[currentAbility.name].activate(characterBox.character, [target]);
  battleScreen.selectTarget.disconnect(targetSelected);
}

function startUp() {
  console.log("CharacterBox: character changed");

  TreeMenuComponent = Qt.createComponent("TreeMenu.qml");
  characterBox.treeMenu = TreeMenuComponent.createObject(characterBox);

  characterBox.treeMenu.canCancel = false;
  characterBox.treeMenu.selectSound = 'menublip';
  characterBox.treeMenu.setOptions(characterBox.character.getAbilityTree());
  // = ui.treeMenu(characterBox, characterBox.character.getAbilityTree());
  characterBox.treeMenu.anchors.left = characterBox.treeMenu.parent.left;
  characterBox.treeMenu.anchors.top = characterBox.treeMenu.parent.bottom;
  characterBox.treeMenu.selected.connect(abilitySelected);
  characterBox.character.image = characterBox.image;
  //characterBox.treeMenu.callback = abilitySelected;
}

