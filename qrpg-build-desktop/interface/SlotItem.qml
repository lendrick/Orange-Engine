import Qt 4.7

StatItem {
  property Item slot;
  id: statItem;
  height: childrenRect.height
  width: parent.width
  property alias title: statTitle.text
  property alias value: statValue.text
  property alias bind: statBinding.value

  property alias statValueItem: statValue
  property alias statTitleItem: statTitle

  SmallText {
    id: statTitle
    font.bold: true
  }

  SmallText {
    id: statValue
    x: 40
    y: statTitleItem.height
    color: if(value == 'none') '#999'; else '#fff';
  }

  Binding {
    id: statBinding
    target: statValue
    property: "text"
    when: true
  }


  Image {
    id: img
    source: if(slot && slot.item) slot.item.portrait; else '';
    y: 26
  }

  MouseArea {
    anchors.fill: parent
    onClicked: {
      var scr = slot.itemScreenObject();
      sfx.menublip.play();
    }
  }
}
