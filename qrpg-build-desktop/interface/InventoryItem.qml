import Qt 4.7

Item {

  property Item item
  height: 34
  property alias text: txt.text
  width: parent.width / 2

  onItemChanged: if(item) text = item.name;

  Image {
    id: img
    source: if(item) item.portrait; else ''
  }

  SmallText {
    id: txt
    anchors.left: img.right
    anchors.verticalCenter: img.verticalCenter
    width: parent.width / 2;
    wrapMode: Text.NoWrap
  }
}
