import Qt 4.7

StatItem {
  statValueItem.x: 0
  statValueItem.y: statTitleItem.height
  statTitleItem.font.bold: true
  statValueItem.color: if(value == 'none') '#999'; else '#fff';
  property Item slot;
  id: statItem;

  MouseArea {
    anchors.fill: parent
    onClicked: {
      var scr = slot.itemScreenObject();
      sfx.menublip.play();
    }
  }
}
