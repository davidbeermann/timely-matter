#include "GeneratedMeshFxModule.hpp"


void GeneratedMeshFxModule::doInit(const unsigned int width, const unsigned int height) {
    float half_width = (float) width * 0.5f;
    float half_height = (float) height * 0.5f;
    
    m_texture.allocate(width, height, GL_RGBA, 8);
    
    // colored mesh to be drawn to the texture fbo.
    // texture fbo is the image texture for the dynamic mesh.
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    mesh.addVertex(ofVec3f(0.f, 0.f, 0.f));
    mesh.addVertex(ofVec3f(width, 0.f, 0.f));
    mesh.addVertex(ofVec3f(width, height, 0.f));
    mesh.addVertex(ofVec3f(0.f, height, 0.f));
    mesh.usingColors();
    mesh.addColors({
        ofFloatColor(1.f, 0.f, 0.f, 1.f),
        ofFloatColor(1.f, 1.f, 0.f, 1.f),
        ofFloatColor(0.f, 0.f, 1.f, 1.f),
        ofFloatColor(1.f, 0.f, 1.f, 1.f)
    });
    mesh.usingIndices();
    vector<unsigned int> indices = {0,1,3,1,2,3};
    mesh.addIndices(indices);
    
    m_texture.begin();
    ofClear(0.f);
    mesh.draw();
    m_texture.end();
    
    // create single point mesh to act as starting point for generated mesh
    m_mesh.setMode(OF_PRIMITIVE_POINTS);
    m_mesh.addVertex(ofVec3f(half_width, half_height, 0.f));
    
    m_shader.load("shaders/generated_mesh.vert", "shaders/generated_mesh.frag", "shaders/generated_mesh.geom");
    
    m_params.setName("Generated Mesh");
    m_params.add(m_param_enabled.set("enabled", true));
    m_params.add(m_param_wireframe.set("wireframe", false));
    m_params.add(m_param_resolution.set("resolution", 4, 3, 48));
    m_params.add(m_param_radius.set("radius", 50.f, 10.f, width >= height ? half_width : half_height));
}


void GeneratedMeshFxModule::doRender(ofFbo& input) {
    if (m_param_enabled) {
        input.begin();
        
        m_texture.getTexture().bind();
        m_shader.begin();
        m_shader.setUniform2f("uTexSize", m_texture.getWidth(), m_texture.getHeight());
        m_shader.setUniform1i("uResolution", m_param_resolution);
        m_shader.setUniform1f("uRadius", m_param_radius);
        if (m_param_wireframe) {
            m_mesh.drawWireframe();
        } else {
            m_mesh.draw();
        }
        m_shader.end();
        m_texture.getTexture().unbind();
        
        input.end();
    }
}