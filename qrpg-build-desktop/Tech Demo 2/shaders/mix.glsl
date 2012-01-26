uniform sampler2D source;
uniform highp float ratio;
void main(void) {
   vec2 uv = gl_TexCoord[0].xy;
   lowp vec4 textureColor = texture2D(source, uv);
   lowp float gray = dot(textureColor, vec4(0.299, 0.587, 0.114, 0.0));
   gl_FragColor = vec4(gray * ratio + textureColor.r * (1.0 - ratio), gray * ratio + textureColor.g * (1.0 - ratio), gray * ratio + textureColor.b * (1.0 - ratio), textureColor.a);
}
