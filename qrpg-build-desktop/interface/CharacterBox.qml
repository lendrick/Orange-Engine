import Qt 4.7

Box {
  id: characterBox
  property Item character

  //height: childrenRect.height
  //width: childrenRect.width

  state: "Show"
  height: 140
  width: 220

  Column {
    x: 25
    y: 25
    height: parent.height - 50
    width: parent.width - 50
    /*
    height: childrenRect.height
    width: childrenRect.width
    */

    Item {
      height: 36
      width: 200
      Image {
        source: {
          if(character && character.portrait)
            character.portrait;
          else
            '';
        }
      }

      BindItem {
        x: 48
        id: characterName
        fmt.color: '#ff2'
        fmt.font.bold: true
        bind: if(character) character.name
      }
    }

    StatItem {
      id: hpDisplay
      title: "HP"
      bind: if(character) character.hp + " / " + character.current_maxHp;
    }

    StatItem {
      id: mpDisplay
      title: "MP"
      bind: if(character) character.mp + " / " + character.current_maxMp;
    }

  }
}
