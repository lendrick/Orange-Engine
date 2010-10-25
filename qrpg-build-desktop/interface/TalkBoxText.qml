import Qt 4.7

BigText {
  x: 30
  y: 25
  width: 580
  height: 118
  id: bigText
  state: "Hide"

  states: [
    State {
      name: "Hide"

      PropertyChanges {
        target: bigText
        opacity: 0
      }

    },
    State {
      name: "Show"

      PropertyChanges {
        target: bigText
        opacity: 1
      }
    }
  ]

  transitions: [
    Transition {
      PropertyAnimation {
        properties: "opacity"
        duration: 150
      }
    }
  ]
}
