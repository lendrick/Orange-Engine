import QtQuick 1.0

Rectangle {
  property alias bgSource: bgImage.source
  property alias fgSource: fgImage.source
  property int current
  property int total
  property alias text: text

  Image {
    id: bgImage
    fillMode: Image.Stretch
    anchors.fill: parent
  }

  Image {
    id: fgImage
    fillMode: Image.Stretch
    anchors.top: parent.top
    anchors.left: parent.left
    anchors.bottom: parent.bottom
    width: parent.width * (parent.current / parent.total)
  }

  Text {
    id: text
    text: current + "/" + total
    anchors.centerIn: parent
  }
}
