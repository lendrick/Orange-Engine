import Qt 4.7
//import Qt.labs.shaders 1.0

HideShowContainer {
  id: container
  property alias rect: boxrect

  Rectangle {
    id: boxrect
    anchors.fill: parent
    opacity: 0
  }

  BorderImage {


    rotation: 0
    id: box
    border.bottom: 28
    border.top: 28
    border.right: 28
    border.left: 28
    border.objectName: "Border"
    //source: "box-highres.png"
    source: "box-highres.png"
    anchors.fill: parent
  }

  states: [
    State {
      name: "Highlight"
      PropertyChanges {
        target: box;
        source: "box-highres-highlighted.png"
      }
    }
  ]

  /*
  ShaderEffectItem  {
      property variant source: ShaderEffectSource  { sourceItem: rect; hideSource: true }
      //property variant box: ShaderEffectSource  { sourceItem: box; hideSource: false }
      property real ratio: 0.9
      blending: true
      anchors.fill: parent

      fragmentShader: "
      uniform sampler2D source;
      uniform sampler2D box;
      uniform highp float ratio;
      void main(void) {
         vec2 uv = gl_TexCoord[0].xy;
         lowp vec4 textureColor = texture2D(source, uv);
         lowp float gray = dot(textureColor, vec4(0.299, 0.587, 0.114, 0.0));
         gl_FragColor = vec4(gray * ratio + textureColor.r * (1.0 - ratio), gray * ratio + textureColor.g * (1.0 - ratio), gray * ratio + textureColor.b * (1.0 - ratio), textureColor.a);
      }
      "
  }
  */
}
