import Qt 4.7

Item {
  id: statItem
  height: childrenRect.height
  width: parent.width
  property alias title: statTitle.text
  property alias value: statValue.text
  property alias bind: statBinding.value

  SmallText {
    id: statTitle
  }

  SmallText {
    id: statValue
    x: parent.width - width
  }

  Binding {
    id: statBinding
    target: statValue
    property: "text"
    when: true
  }
}
