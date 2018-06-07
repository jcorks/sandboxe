// Fragment shader
//
// Not as flashy as the previous example, but definitely more colorful 
// Colors based on a field position.
varying vec3   pos;


void main() {
    vec4 finalColor;
    
    finalColor.x = sin(pos.x*10)*.5+1;
    finalColor.y = sin(pos.y*10)*.5+1;
    finalColor.z = sin(pos.z*10)*.5+1;
    
    finalColor = finalColor*finalColor.z;

    finalColor.a = 1.0f;
    gl_FragColor = finalColor;
}
