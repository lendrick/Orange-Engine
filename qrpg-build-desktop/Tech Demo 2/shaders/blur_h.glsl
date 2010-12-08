#version 120
uniform sampler2D sceneTex; // 0

uniform float rtw; // render target width
//uniform float rth; // render target height

float offset[3] = float[]( 0.0, 1.3846153846, 3.2307692308 );
float weight[3] = float[]( 0.2270270270, 0.3162162162, 0.0702702703 );

void main()
{
  vec3 tc = vec3(1.0, 0.0, 0.0);

  vec2 uv = gl_TexCoord[0].xy;
  tc = texture2D(sceneTex, uv).rgb * weight[0];
  for (int i=1; i<3; i++)
  {
    tc += texture2D(sceneTex, uv + vec2(offset[i])/rtw, 0.0).rgb
            * weight[i];
    tc += texture2D(sceneTex, uv - vec2(offset[i])/rtw, 0.0).rgb
           * weight[i];
  }

  gl_FragColor = vec4(tc, 1.0);
}
