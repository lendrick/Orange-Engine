import Qt 4.7

SmallText {
  id: treeMenuItem
  wrapMode: Text.NoWrap
  property int index
  property bool selected: false
  property variant object;
  property Item subMenu;

  state: "Normal"

  function setSelected() {
    parent.parent.parent.setSelectedIndex(index);
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
      if(treeMenuContainer.selectSound != '')
        sfx[selectsound].play();
      console.log("submenu: " + treeMenuItem.subMenu);
      treeMenuItem.subMenu.show();
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
        target: treeMenuItem
        color: '#fff'
      }
    },

    State {
      name: "Hover"
      PropertyChanges {
        target: treeMenuItem
        color: '#ff2'
      }
    },

    State {
      name: "Selected"
      PropertyChanges {
        target: treeMenuItem
        color: '#ff2'
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
