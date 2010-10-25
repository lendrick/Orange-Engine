import Qt 4.7

BorderImage {
    objectName: "talkBox"
    id: talkbox
    x: 0
    y: 480-168
    width: 640
    height: 168
    rotation: 0
    border.bottom: 28
    border.top: 28
    border.right: 28
    border.left: 28
    border.objectName: "Border"
    source: "box-highres.png"
    state: "New"
    opacity: 0

    Text {
      objectName: "text1"
      id: text1
      x: 30
      y: 25
      width: 580
      height: 118
      color: "#ffffff"
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
            name: "New"

            PropertyChanges {
                target: talkbox
                opacity: 0
                scale: .75
            }
        },
        State {
            name: "Show"

            PropertyChanges {
                target: talkbox
                opacity: 1
                scale: 1
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

    transitions: Transition {
      PropertyAnimation {
        properties: "opacity"
        duration: 500
      }
      PropertyAnimation {
        properties: "scale"
        duration: 500
        easing.type: Easing.OutBack
      }
    }

}
