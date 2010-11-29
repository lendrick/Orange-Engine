import Qt 4.7
import "MagicScreen.js" as MagicScreenScript

HideShowContainer {
  id: magicScreen
  state: "Hide"
  Component.onCompleted: MagicScreenScript.startUp();
  property alias selectedIndex: characterSelect.selectedIndex

  onStateChanged: {
    if(state == "Show")
      MagicScreenScript.characterMagicScreens[selectedIndex].updateMagicList();
  }

  function selectedCharacter() {
    return MagicScreenScript.characterMagicScreens[selectedIndex].character;
  }

  function setCurrentPartyMember(index) {
    //console.log("set party member to " + index)
    characterSelect.setPartyMember(index);
    //console.log("showing character screen " + index)
    MagicScreenScript.characterMagicScreens[index].show();
    selectedIndex = index;
    //console.log("setting party member to " + selectedCharacter().name);
  }

  function setPartyMember(i, character) {
    MagicScreenScript.characterMagicScreens[i].setPartyMember(character);
  }

  function addPartyMember(character) {
    utils.debugObject(character);
    //console.log("adding character to menu: " + character.name);

    var scr = MagicScreenScript.newMagicScreen(this);
    //console.log("1");
    scr.setPartyMember(character);
    //console.log("2");
    MagicScreenScript.characterMagicScreens.push(scr);

    var currentIndex = MagicScreenScript.characterMagicScreens.length - 1;
    //console.log("adding character to select row");
    characterSelect.addPartyMember(character, MagicScreenScript.characterMagicScreens[currentIndex]);
    //console.log("character added to menu")

    if(currentIndex == 0) selectedIndex = 0;
  }

  PortraitMenu {
    id: characterSelect;
    width: parent.width
    height: 100
    x: 0
    y: 0
  }
}
