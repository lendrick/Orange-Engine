import Qt 4.7

Item {
  height: 34
  property alias text: txt.text
  property alias portrait: img.source
  width: parent.width / 2
  //onItemChanged: if(item) text = item.name;

  Image {
    id: img
  }

  SmallText {
    id: txt
    anchors.left: img.right
    anchors.verticalCenter: img.verticalCenter
    text: item.name
    width: parent.width / 2;
    wrapMode: Text.NoWrap
  }
}
