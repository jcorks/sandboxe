// Here is our vertex shader.
// Here, we calculate the transformed
// vertex from the geometry, and pass along information 
// about the vertex to the fragment shader. In GLSL, the 
// passed information is, by default, interpolated between 
// the vertices.

varying vec3 pos;

void main() {

    // Since Dynacoe_Position is just the input vertex,
    // we need to transform it based on the current transform matrices:
    //
    // - Dynacoe_ProjectionTransform:  the projection matrix from the current camera 
    // - Dynacoe_ViewTransform:        the view matrix from the current camera 
    // - Dynacoe_ModelTransform;       the matrix from the AspectMesh's local transformation (or Mesh)

    gl_Position = Dynacoe_ProjectionTransform * (Dynacoe_ViewTransform  * (Dynacoe_ModelTransform * vec4(Dynacoe_Position, 1.f)));
    
    pos        = gl_Position.xyz;
}
