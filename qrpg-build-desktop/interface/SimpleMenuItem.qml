import Qt 4.7

MediumText {
  id: simpleMenuItem
  wrapMode: Text.NoWrap
  property int index
  property bool selected: false
  property Item object;
  state: "Normal"

  function setSelected() {
    parent.setSelectedIndex(index);
  }

  function select() {
    selected = true;
    object.show();
    if(state != "Hover") resetState();
  }

  function deselect() {
    selected = false;
    object.hide();
    if(state != "Hover") resetState();
  }

  MouseArea {
    hoverEnabled: true
    anchors.fill: parent
    acceptedButtons: Qt.LeftButton

    onEntered: {
      parent.state = "Hover";
    }

    onExited: {
      parent.resetState();
    }

    onClicked: {
      //console.log("click");
      sfx.menublip.play();
      parent.setSelected();
    }
  }

  function resetState() {
    if(selected)
      state = "Selected";
    else
      state = "Normal";
  }

  states: [
    State {
      name: "Normal"
      PropertyChanges {
        target: simpleMenuItem
        color: '#fff'
      }
    },

    State {
      name: "Hover"
      PropertyChanges {
        target: simpleMenuItem
        color: '#ff2'
      }
    },

    State {
      name: "Selected"
      PropertyChanges {
        target: simpleMenuItem
        color: '#ff2'
      }
    }
  ]

  /*
  transitions: [
    Transition {
      PropertyAnimation {
        properties: "color"
        duration: 100
      }
    }
  ]
  */
}
