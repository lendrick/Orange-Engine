import Qt 4.7

MediumText {
  id: simpleMenuItem
  wrapMode: Text.NoWrap
  property int index
  property bool selected: false
  state: "Normal"

  function setSelected() {
    parent.setSelectedIndex(index);
  }

  function select() {
    selected = true;
    if(state != "Hover") resetState();
  }

  function deselect() {
    selected = false;
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
        color: '#bbbbbb'
      }
    },

    State {
      name: "Hover"
      PropertyChanges {
        target: simpleMenuItem
        color: '#ffff55'
      }
    },

    State {
      name: "Selected"
      PropertyChanges {
        target: simpleMenuItem
        color: '#ffffff'
      }
    }
  ]

  transitions: [
    Transition {
      PropertyAnimation {
        properties: "color"
        duration: 100
      }
    }
  ]
}
