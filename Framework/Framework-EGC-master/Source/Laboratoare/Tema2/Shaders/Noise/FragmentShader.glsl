precision highp float;
precision highp int;

uniform vec3 object_color;

varying float vNoise;

void main() {
    
    gl_FragColor = vec4( object_color, 1.0 );

}
  