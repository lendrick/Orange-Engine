import Qt 4.7

Image {
  id: imageMenuItem
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
      parent.setSelected();
    }
  }

  function resetState() {
    if(selected)
      state = "Selected";
    else
      state = "Normal";
  }

  /*
  states: [
    State {
      name: "Normal"
      PropertyChanges {
        target: imageMenuItem
        scale: 1
      }
    },

    State {
      name: "Hover"
      PropertyChanges {
        target: imageMenuItem
        scale: 1.1
      }
    },

    State {
      name: "Selected"
      PropertyChanges {
        target: imageMenuItem
        scale: 1.1
      }
    }
  ]

  transitions: [
    Transition {
      PropertyAnimation {
        properties: "scale"
        duration: 100
      }
    }
  ]
  */
}
