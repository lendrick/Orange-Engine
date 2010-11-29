import Qt 4.7
import "CharacterMagicScreen.js" as CharacterMagicScreenScript

Box {
  id: characterMagicScreen
  width: parent.width
  height: parent.height - 100
  x: 0
  y: 100
  state: "Hide"
  property variant character

  Component.onCompleted: CharacterMagicScreenScript.startUp();


  Item {
    id: inventoryListContainer
    x: 25
    y: 25
    height: parent.height - 50
    width: parent.width - 50
    property alias inv: inventoryList;

    clip: true

    Item {
      id: inventoryList
      width: parent.width
      //height: children.height;
    }
  }

  function setPartyMember(c) {
    character = c;
  }

  onCharacterChanged: updateMagicList();
  onStateChanged: if(state == "Show") updateMagicList();

  function updateMagicList() {
    //console.log("Magic list for " + character.name);

    var abilities = character.getAbilityTree();

    //console.log("Abilities: " + serialize(abilities));
    if(abilities['Magic']) {
      var magic = abilities['Magic']['$value'];
      //console.log("Magic: " + serialize(magic));

      while(CharacterMagicScreenScript.invList.length > 0) {
        var x = CharacterMagicScreenScript.invList.pop();
        x.destroy();
      }

      var count = 0;
      for(var i in magic) {
        //console.log("Adding magic: " + magic[i].name);
        var item = CharacterMagicScreenScript.invItemComponent.createObject(inventoryListContainer.inv);
        item.text = magic[i]['$value'].name
        item.portrait = magic[i]['$value'].portrait

        item.x = (count % 2) * inventoryListContainer.inv.width / 2;
        item.y = Math.floor(count / 2) * item.height;
        item.ability = magic[i]['$value']['name'];
        CharacterMagicScreenScript.invList.push(item);
        count++;
      }
    }
  }
}
