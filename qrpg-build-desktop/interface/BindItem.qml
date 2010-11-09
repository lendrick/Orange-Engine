import Qt 4.7

Item {
  id: bindItem
  height: childrenRect.height
  width: parent.width
  property alias fmt: statValue;
  property alias value: statValue.text
  property alias bind: statBinding.value

  SmallText {
    id: statValue
  }

  Binding {
    id: statBinding
    target: statValue
    property: "text"
    when: true
  }
}
