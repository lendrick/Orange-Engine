import Qt 4.7

BorderImage {
    id: talkbox
    x: 0
    y: 0
    width: 640
    height: 168
    rotation: 0
    border.bottom: 25
    border.top: 25
    border.right: 25
    border.left: 25
    source: "box-highres.png"

    Text {
      id: text1
      x: 30
      y: 25
      width: 580
      height: 118
      color: "#ffffff"
      text: "Hello, world!  Hello, world!  Hello, world!  Hello, world!  Hello, world!  Hello, world!  Hello, world!  Hello, world!  Hello, world!  Hello, world!  "
      clip: true
      style: Text.Outline
      font.pixelSize: 34
      styleColor: "#000000"
      font.bold: true
      font.family: "DejaVu Sans"
      smooth: true
      wrapMode: Text.WordWrap
    }
    states: [
        State {
            name: "State1"

            PropertyChanges {
                target: talkbox
                opacity: 0
            }
        },
        State {
            name: "State2"
            PropertyChanges {
                target: talkbox
                opacity: 1
            }

            PropertyChanges {
                target: text1
                opacity: 0
            }
        }
    ]
}
