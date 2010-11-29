import Qt 4.7

Text {
  color: "#ffffff"
  clip: false
  font.pixelSize: 25
  font.family: "Liberation Mono"
  smooth: true
  wrapMode: Text.WordWrap
  opacity: 1

  Behavior on color {
    PropertyAnimation {
      duration: 200
    }
  }
}
