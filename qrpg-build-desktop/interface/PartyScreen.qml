import Qt 4.7
import "PartyScreen.js" as PartyScreenScript

HideShowContainer {
  id: partyScreen
  state: "Show"
  Component.onCompleted: PartyScreenScript.startUp();
  property alias selectedIndex: characterSelect.selectedIndex

  function selectedCharacter() {
    return PartyScreenScript.characterScreens[selectedIndex].character;
  }

  function setCurrentPartyMember(index) {
    //console.log("set party member to " + index)
    characterSelect.setPartyMember(index);
    //console.log("showing character screen " + index)
    PartyScreenScript.characterScreens[index].show();
    selectedIndex = index;
    //console.log("setting party member to " + selectedCharacter().name);
  }

  function setPartyMember(i, character) {
    PartyScreenScript.characterScreens[i].setPartyMember(character);
  }

  function addPartyMember(character) {
    utils.debugObject(character);
    //console.log("adding character to menu: " + character.name);

    var scr = PartyScreenScript.newCharacterScreen(this);
    //console.log("1");
    scr.setPartyMember(character);
    //console.log("2");
    PartyScreenScript.characterScreens.push(scr);

    var currentIndex = PartyScreenScript.characterScreens.length - 1;
    //console.log("adding character to select row");
    characterSelect.addPartyMember(character, PartyScreenScript.characterScreens[currentIndex]);
    //console.log("character added to menu")
  }

  PortraitMenu {
    id: characterSelect;
    width: parent.width
    height: 100
    x: 0
    y: 0
  }
}
