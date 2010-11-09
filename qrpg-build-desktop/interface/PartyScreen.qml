import Qt 4.7
import "PartyScreen.js" as PartyScreenScript

HideShowContainer {
  id: partyScreen
  x: 200
  y: 0
  width: 440
  height: 480
  state: "Show"
  Component.onCompleted: PartyScreenScript.startUp();
  property int selectedIndex

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
    characterSelect.addPartyMember(character);
    var scr = PartyScreenScript.newCharacterScreen(this);
    scr.setPartyMember(character);
    PartyScreenScript.characterScreens.push(scr);
    //console.log("character added to menu")
  }

  Box {
    id: characterSelect
    objectName: "characterSelect"
    width: 440
    height: 100
    x: 0
    y: 0
    state: "Show"

    function addPartyMember(character) {

    }

    function setPartyMember(index) {
      console.log("setting characterSelect to " + index);
    }
  }

}
