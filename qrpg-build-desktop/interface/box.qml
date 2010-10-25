import Qt 4.7

BorderImage {
  rotation: 0
  border.bottom: 28
  border.top: 28
  border.right: 28
  border.left: 28
  border.objectName: "Border"
  source: "box-highres.png"
  state: "Hide"
  opacity: 0

  states: [
    State {
      name: "Hide"

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
    }
  ]

  transitions: [
    Transition {
      to: "Hide"
      PropertyAnimation {
        properties: "opacity"
        duration: 150
      }
      PropertyAnimation {
        properties: "scale"
        duration: 350
        easing.type: Easing.Linear
      }
    },

    Transition {
      to: "Show"
      PropertyAnimation {
        properties: "opacity"
        duration: 225
      }
      PropertyAnimation {
        properties: "scale"
        duration: 350
        easing.type: Easing.OutBack
      }
    }
  ]
}

