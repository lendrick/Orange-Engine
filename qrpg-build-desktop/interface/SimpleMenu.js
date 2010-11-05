var menuItems;
var selectedIndex;
var SimpleMenuItemComponent;

function startUp() {
  menuItems = Array();

  SimpleMenuItemComponent = Qt.createComponent("SimpleMenuItem.qml");
  //console.log("created menu item component");
}

