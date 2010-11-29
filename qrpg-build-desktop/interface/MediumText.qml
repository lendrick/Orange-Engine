import Qt 4.7

Text {
  color: "#ffffff"
  clip: true
  font.pixelSize: 35
  font.family: "Liberation Mono"
  smooth: true
  font.bold: true
  wrapMode: Text.WordWrap
  opacity: 1

  Behavior on color {
    PropertyAnimation {
      duration: 100
    }
  }
}
