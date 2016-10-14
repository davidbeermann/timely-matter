#pragma once

#include "ofMain.h"
#include "ofxGui.h"


struct Particle {
    Particle(float x, float y, float r){
        position.set(x, y);
        radius = r;
        radiusSquared = r * r;
        float speed = ofRandom(2, 4);
        float angle = ofRandom(PI * 2.f);
        velocity.set(cos(angle) * speed, sin(angle) * speed);
    };
    ofVec3f position;
    ofVec3f velocity;
    float radius;
    float radiusSquared;
};

struct CellUnit {
    CellUnit(float x, float y) {
        position.set(x, y);
        reset();
    }
    void reset() {
        value = 0.f;
    }
    ofVec3f position;
    float value;
};

struct Cell {
    Cell(float cell_size){
        size = cell_size;
        half_size = cell_size * 0.5f;
        state = 0;
    }
    void setTopLeftUnit(CellUnit* unit) {
        tl = unit;
    }
    void setTopRightUnit(CellUnit* unit) {
        tr = unit;
    }
    void setBottomRightUnit(CellUnit* unit) {
        br = unit;
    }
    void setBottomLeftUnit(CellUnit* unit) {
        bl = unit;
    }
    void updateState() {
        state = 0;
        state += bl->value >= 1.f ? 1 : 0;
        state += br->value >= 1.f ? 2 : 0;
        state += tr->value >= 1.f ? 4 : 0;
        state += tl->value >= 1.f ? 8 : 0;
    }
    void appendLineVertices(ofMesh& mesh, bool interpolated = false, bool infill = false) {
        vector<ofVec3f> vertices;
        if (interpolated) {
            addInterpolatedVertices(vertices);
        } else {
            addStraightVertices(vertices);
        }
        
        if (infill) {
            addInfillVertices(vertices);
        }
        
        vector<ofVec3f>::iterator v;
        for (v = vertices.begin(); v != vertices.end(); ++v) {
            mesh.addVertex(*v);
        }
    }
    
    void addInfillVertices(vector<ofVec3f>& vertices) {
        ofVec3f p1, p2, p3, p4;
        switch (state) {
            /*////|\\\\\\
            //         \\
            //  ○   ○  \\
            //         \\
            //  ○   ○  \\
            //         \\
            //////|\\\\*/
            case 0:
                break;
            /*////|\\\\\\
            //         \\
            //  ○   ○  \\
            //  \      \\
            //  ●\  ○  \\
            //         \\
            //////|\\\\*/
            case 1:
                // complete line to triangle
                vertices.push_back(bl->position);
                break;
            /*////|\\\\\\
            //         \\
            //  ○   ○  \\
            //      /  \\
            //  ○  /●  \\
            //         \\
            //////|\\\\*/
            case 2:
                // complete line to triangle
                vertices.push_back(br->position);
                break;
            /*////|\\\\\\
            //         \\
            //  ○   ○  \\
            //  -----  \\
            //  ●   ●  \\
            //         \\
            //////|\\\\*/
            case 3:
                // complete line to triangle
                vertices.push_back(br->position);
                
                // add missing triangle
                vertices.push_back(br->position);
                vertices.push_back(bl->position);
                vertices.push_back(vertices.at(0));
                break;
            /*////|\\\\\\
            //         \\
            //  ○  \●  \\
            //      \  \\
            //  ○   ○  \\
            //         \\
            //////|\\\\*/
            case 4:
                // complete line to triangle
                vertices.push_back(tr->position);
                break;
            /*////|\\\\\\
            //         \\
            //  ○/  ●  \\
            //  /   /  \\
            //  ●  /○  \\
            //         \\
            //////|\\\\*/
            case 5:
                // store vertices for reference
                p1 = ofVec3f(vertices.at(0));
                p2 = ofVec3f(vertices.at(1));
                p3 = ofVec3f(vertices.at(2));
                p4 = ofVec3f(vertices.at(3));
                
                // clear vector
                vertices.clear();
                
                // add triangles
                vertices.push_back(bl->position);
                vertices.push_back(p1);
                vertices.push_back(p3);
                
                vertices.push_back(p1);
                vertices.push_back(p2);
                vertices.push_back(p3);
                
                vertices.push_back(p2);
                vertices.push_back(p3);
                vertices.push_back(p4);
                
                vertices.push_back(p2);
                vertices.push_back(p4);
                vertices.push_back(tr->position);
                break;
            /*////|\\\\\\
            //         \\
            //  ○ | ●  \\
            //    |    \\
            //  ○ | ●  \\
            //         \\
            //////|\\\\*/
            case 6:
                // complete line to triangle
                vertices.push_back(br->position);
                
                // add missing triangle
                vertices.push_back(br->position);
                vertices.push_back(tr->position);
                vertices.push_back(vertices.at(0));
                break;
            /*////|\\\\\\
            //         \\
            //  ○/  ●  \\
            //  /      \\
            //  ●   ●  \\
            //         \\
            //////|\\\\*/
            case 7:
                // complete line to triangle
                vertices.push_back(br->position);
                
                // add missing triangle
                vertices.push_back(br->position);
                vertices.push_back(bl->position);
                vertices.push_back(vertices.at(0));
                
                vertices.push_back(br->position);
                vertices.push_back(tr->position);
                vertices.push_back(vertices.at(1));
                break;
            /*////|\\\\\\
            //         \\
            //  ●/  ○  \\
            //  /      \\
            //  ○   ○  \\
            //         \\
            //////|\\\\*/
            case 8:
                // complete line to triangle
                vertices.push_back(tl->position);
                break;
            /*////|\\\\\\
            //         \\
            //  ● | ○  \\
            //    |    \\
            //  ● | ○  \\
            //         \\
            //////|\\\\*/
            case 9:
                // complete line to triangle
                vertices.push_back(bl->position);
                
                // add missing triangle
                vertices.push_back(bl->position);
                vertices.push_back(tl->position);
                vertices.push_back(vertices.at(0));
                break;
            /*////|\\\\\\
            //         \\
            //  ●  \○  \\
            //  \   \  \\
            //  ○\  ●  \\
            //         \\
            //////|\\\\*/
            case 10:
                // store vertices for reference
                p1 = ofVec3f(vertices.at(0));
                p2 = ofVec3f(vertices.at(1));
                p3 = ofVec3f(vertices.at(2));
                p4 = ofVec3f(vertices.at(3));
                
                // clear vector
                vertices.clear();
                
                // add triangles
                vertices.push_back(tl->position);
                vertices.push_back(p1);
                vertices.push_back(p3);
                
                vertices.push_back(p1);
                vertices.push_back(p2);
                vertices.push_back(p3);
                
                vertices.push_back(p2);
                vertices.push_back(p3);
                vertices.push_back(p4);
                
                vertices.push_back(p2);
                vertices.push_back(p4);
                vertices.push_back(br->position);
                break;
            /*////|\\\\\\
            //         \\
            //  ●  \○  \\
            //      \  \\
            //  ●   ●  \\
            //         \\
            //////|\\\\*/
            case 11:
                // complete line to triangle
                vertices.push_back(bl->position);
                
                // add missing triangles
                vertices.push_back(tl->position);
                vertices.push_back(bl->position);
                vertices.push_back(vertices.at(0));
                
                vertices.push_back(bl->position);
                vertices.push_back(br->position);
                vertices.push_back(vertices.at(1));
                break;
            /*////|\\\\\\
            //         \\
            //  ●   ●  \\
            //  -----  \\
            //  ○   ○  \\
            //         \\
            //////|\\\\*/
            case 12:
                // complete line to triangle
                vertices.push_back(tl->position);
                
                // add missing triangle
                vertices.push_back(tl->position);
                vertices.push_back(tr->position);
                vertices.push_back(vertices.at(1));
                break;
            /*////|\\\\\\
            //         \\
            //  ●   ●  \\
            //      /  \\
            //  ●  /○  \\
            //         \\
            //////|\\\\*/
            case 13:
                // complete line to triangle
                vertices.push_back(tl->position);
                
                // add missing triangles
                vertices.push_back(tl->position);
                vertices.push_back(bl->position);
                vertices.push_back(vertices.at(0));
                
                vertices.push_back(tl->position);
                vertices.push_back(tr->position);
                vertices.push_back(vertices.at(1));
                break;
            /*////|\\\\\\
            //         \\
            //  ●   ●  \\
            //  \      \\
            //  ○\  ●  \\
            //         \\
            //////|\\\\*/
            case 14:
                // complete line to triangle
                vertices.push_back(tr->position);
                
                // add missing triangles
                vertices.push_back(tr->position);
                vertices.push_back(br->position);
                vertices.push_back(vertices.at(1));
                
                vertices.push_back(vertices.at(0));
                vertices.push_back(tl->position);
                vertices.push_back(tr->position);
                break;
            /*////|\\\\\\
            //         \\
            //  ●   ●  \\
            //         \\
            //  ●   ●  \\
            //         \\
            //////|\\\\*/
            case 15:
                vertices.push_back(tl->position);
                vertices.push_back(bl->position);
                vertices.push_back(tr->position);
                vertices.push_back(bl->position);
                vertices.push_back(tr->position);
                vertices.push_back(br->position);
                break;
        }
    }
    
    void addInterpolatedVertices(vector<ofVec3f>& vertices) {
//        mesh.usingColors();
//        switch (state) {
//            case 5:
//            case 10:
//                mesh.addColor(ofFloatColor(1.f, 1.f, 1.f, 1.f));
//                mesh.addColor(ofFloatColor(1.f, 1.f, 1.f, 1.f));
//                mesh.addColor(ofFloatColor(1.f, 1.f, 1.f, 1.f));
//                mesh.addColor(ofFloatColor(1.f, 1.f, 1.f, 1.f));
//                break;
//            default:
//                mesh.addColor(ofFloatColor(1.f, 1.f, 1.f, 1.f));
//                mesh.addColor(ofFloatColor(1.f, 1.f, 1.f, 1.f));
//                break;
//        }
        switch (state) {
            /*////|\\\\\\
            //         \\
            //  ○   ○  \\
            //         \\
            //  ○   ○  \\
            //         \\
            //////|\\\\*/
            case 0:
                break;
            /*/////////||\\\\\\\\\\\
            //         ||         \\
            //  ○   ○  ||  ●   ●  \\
            //  \      ||  \      \\
            //  ●\  ○  ||  ○\  ●  \\
            //         ||         \\
            ///////////||\\\\\\\\\*/
            case 1:
            case 14:
                vertices.push_back(ofVec3f(
                    bl->position.x,
                    tl->position.y + size * ((1.f - tl->value)/(bl->value - tl->value))
                ));
                vertices.push_back(ofVec3f(
                    br->position.x - size * ((1.f - br->value)/(bl->value - br->value)),
                    bl->position.y
                ));
                break;
            /*/////////||\\\\\\\\\\\
            //         ||         \\
            //  ○   ○  ||  ●   ●  \\
            //      /  ||      /  \\
            //  ○  /●  ||  ●  /○  \\
            //         ||         \\
            ///////////||\\\\\\\\\*/
            case 2:
            case 13:
                vertices.push_back(ofVec3f(
                    bl->position.x + size * ((1.f - bl->value)/(br->value - bl->value)),
                    br->position.y
                ));
                vertices.push_back(ofVec3f(
                    br->position.x,
                    tr->position.y + size * ((1.f - tr->value)/(br->value - tr->value))
                ));
                break;
            /*/////////||\\\\\\\\\\\
            //         ||         \\
            //  ○   ○  ||  ●   ●  \\
            //  -----  ||  -----  \\
            //  ●   ●  ||  ○   ○  \\
            //         ||         \\
            ///////////||\\\\\\\\\*/
            case 3:
            case 12:
                vertices.push_back(ofVec3f(
                    bl->position.x,
                    tl->position.y + size * ((1.f - tl->value)/(bl->value - tl->value))
                ));
                vertices.push_back(ofVec3f(
                    br->position.x,
                    tr->position.y + size * ((1.f - tr->value)/(br->value - tr->value))
                ));
                break;
            /*/////////||\\\\\\\\\\\
            //         ||         \\
            //  ○  \●  ||  ●  \○  \\
            //      \  ||      \  \\
            //  ○   ○  ||  ●   ●  \\
            //         ||         \\
            ///////////||\\\\\\\\\*/
            case 4:
            case 11:
                vertices.push_back(ofVec3f(
                    tl->position.x + size * ((1.f - tl->value)/(tr->value - tl->value)),
                    tr->position.y
                ));
                vertices.push_back(ofVec3f(
                    tr->position.x,
                    br->position.y - size * ((1.f - br->value)/(tr->value - br->value))
                ));
                break;
            /*////|\\\\\\
            //         \\
            //  ○/  ●  \\
            //  /   /  \\
            //  ●  /○  \\
            //         \\
            //////|\\\\*/
            case 5: // saddle
                vertices.push_back(ofVec3f(
                    bl->position.x,
                    tl->position.y + size * ((1.f - tl->value)/(bl->value - tl->value))
                ));
                vertices.push_back(ofVec3f(
                    tl->position.x + size * ((1.f - tl->value)/(tr->value - tl->value)),
                    tr->position.y
                ));
                vertices.push_back(ofVec3f(
                    br->position.x - size * ((1.f - br->value)/(bl->value - br->value)),
                    bl->position.y
                ));
                vertices.push_back(ofVec3f(
                    tr->position.x,
                    br->position.y - size * ((1.f - br->value)/(tr->value - br->value))
                ));
                break;
            /*/////////||\\\\\\\\\\\
            //         ||         \\
            //  ○ | ●  ||  ● | ○  \\
            //    |    ||    |    \\
            //  ○ | ●  ||  ● | ○  \\
            //         ||         \\
            ///////////||\\\\\\\\\*/
            case 6:
            case 9:
                vertices.push_back(ofVec3f(
                    tl->position.x + size * ((1.f - tl->value)/(tr->value - tl->value)),
                    tr->position.y
                ));
                vertices.push_back(ofVec3f(
                    bl->position.x + size * ((1.f - bl->value)/(br->value - bl->value)),
                    br->position.y
                ));
                break;
            /*/////////||\\\\\\\\\\\
            //         ||         \\
            //  ○/  ●  ||  ●/  ○  \\
            //  /      ||  /      \\
            //  ●   ●  ||  ○   ○  \\
            //         ||         \\
            ///////////||\\\\\\\\\*/
            case 7:
            case 8:
                vertices.push_back(ofVec3f(
                    tl->position.x,
                    bl->position.y - size * ((1.f - bl->value)/(tl->value - bl->value))
                ));
                vertices.push_back(ofVec3f(
                    tr->position.x - size * ((1.f - tr->value)/(tl->value - tr->value)),
                    tl->position.y
                ));
                break;
            /*////|\\\\\\
            //         \\
            //  ●  \○  \\
            //  \   \  \\
            //  ○\  ●  \\
            //         \\
            //////|\\\\*/
            case 10: // saddle
                vertices.push_back(ofVec3f(
                    tl->position.x,
                    bl->position.y - size * ((1.f - bl->value)/(tl->value - bl->value))
                ));
                vertices.push_back(ofVec3f(
                    bl->position.x + size * ((1.f - bl->value)/(br->value - bl->value)),
                    br->position.y
                ));
                vertices.push_back(ofVec3f(
                    tr->position.x - size * ((1.f - tr->value)/(tl->value - tr->value)),
                    tl->position.y
                ));
                vertices.push_back(ofVec3f(
                    br->position.x,
                    tr->position.y + size * ((1.f - tr->value)/(br->value - tr->value))
                ));
                break;
            /*////|\\\\\\
            //         \\
            //  ●   ●  \\
            //         \\
            //  ●   ●  \\
            //         \\
            //////|\\\\*/
            case 15:
                break;
        }
    }
    void addStraightVertices(vector<ofVec3f>& vertices) {
//        mesh.usingColors();
//        switch (state) {
//            case 5:
//            case 10:
//                mesh.addColor(ofFloatColor(0.f, 1.f, 0.f, 1.f));
//                mesh.addColor(ofFloatColor(0.f, 1.f, 0.f, 1.f));
//                mesh.addColor(ofFloatColor(0.f, 1.f, 0.f, 1.f));
//                mesh.addColor(ofFloatColor(0.f, 1.f, 0.f, 1.f));
//                break;
//            default:
//                mesh.addColor(ofFloatColor(0.f, 1.f, 0.f, 1.f));
//                mesh.addColor(ofFloatColor(0.f, 1.f, 0.f, 1.f));
//                break;
//        }
        switch (state) {
            /*////|\\\\\\
            //         \\
            //  ○   ○  \\
            //         \\
            //  ○   ○  \\
            //         \\
            //////|\\\\*/
            case 0:
                break;
            /*/////////||\\\\\\\\\\\
            //         ||         \\
            //  ○   ○  ||  ●   ●  \\
            //  \      ||  \      \\
            //  ●\  ○  ||  ○\  ●  \\
            //         ||         \\
            ///////////||\\\\\\\\\*/
            case 1:
            case 14:
//                mesh.addVertex(ofVec3f(bl->position.x, bl->position.y - half_size));
//                mesh.addVertex(ofVec3f(bl->position.x + half_size, bl->position.y));
                vertices.push_back(ofVec3f(bl->position.x, bl->position.y - half_size));
                vertices.push_back(ofVec3f(bl->position.x + half_size, bl->position.y));
                break;
            /*/////////||\\\\\\\\\\\
            //         ||         \\
            //  ○   ○  ||  ●   ●  \\
            //      /  ||      /  \\
            //  ○  /●  ||  ●  /○  \\
            //         ||         \\
            ///////////||\\\\\\\\\*/
            case 2:
            case 13:
//                mesh.addVertex(ofVec3f(br->position.x - half_size, br->position.y));
//                mesh.addVertex(ofVec3f(br->position.x, br->position.y - half_size));
                vertices.push_back(ofVec3f(br->position.x - half_size, br->position.y));
                vertices.push_back(ofVec3f(br->position.x, br->position.y - half_size));
                break;
            /*/////////||\\\\\\\\\\\
            //         ||         \\
            //  ○   ○  ||  ●   ●  \\
            //  -----  ||  -----  \\
            //  ●   ●  ||  ○   ○  \\
            //         ||         \\
            ///////////||\\\\\\\\\*/
            case 3:
            case 12:
//                mesh.addVertex(ofVec3f(bl->position.x, bl->position.y - half_size));
//                mesh.addVertex(ofVec3f(br->position.x, br->position.y - half_size));
                vertices.push_back(ofVec3f(bl->position.x, bl->position.y - half_size));
                vertices.push_back(ofVec3f(br->position.x, br->position.y - half_size));
                break;
            /*/////////||\\\\\\\\\\\
            //         ||         \\
            //  ○  \●  ||  ●  \○  \\
            //      \  ||      \  \\
            //  ○   ○  ||  ●   ●  \\
            //         ||         \\
            ///////////||\\\\\\\\\*/
            case 4:
            case 11:
//                mesh.addVertex(ofVec3f(tr->position.x - half_size, tr->position.y));
//                mesh.addVertex(ofVec3f(tr->position.x, tr->position.y + half_size));
                vertices.push_back(ofVec3f(tr->position.x - half_size, tr->position.y));
                vertices.push_back(ofVec3f(tr->position.x, tr->position.y + half_size));
                break;
            /*////|\\\\\\
            //         \\
            //  ○/  ●  \\
            //  /   /  \\
            //  ●  /○  \\
            //         \\
            //////|\\\\*/
            case 5: // saddle
//                mesh.addVertex(ofVec3f(bl->position.x, bl->position.y - half_size));
//                mesh.addVertex(ofVec3f(tr->position.x - half_size, tr->position.y));
//                mesh.addVertex(ofVec3f(bl->position.x + half_size, bl->position.y));
//                mesh.addVertex(ofVec3f(tr->position.x, tr->position.y + half_size));
                vertices.push_back(ofVec3f(bl->position.x, bl->position.y - half_size));
                vertices.push_back(ofVec3f(tr->position.x - half_size, tr->position.y));
                vertices.push_back(ofVec3f(bl->position.x + half_size, bl->position.y));
                vertices.push_back(ofVec3f(tr->position.x, tr->position.y + half_size));
                break;
            /*/////////||\\\\\\\\\\\
            //         ||         \\
            //  ○ | ●  ||  ● | ○  \\
            //    |    ||    |    \\
            //  ○ | ●  ||  ● | ○  \\
            //         ||         \\
            ///////////||\\\\\\\\\*/
            case 6:
            case 9:
//                mesh.addVertex(ofVec3f(tl->position.x + half_size, tl->position.y));
//                mesh.addVertex(ofVec3f(bl->position.x + half_size, bl->position.y));
                vertices.push_back(ofVec3f(tl->position.x + half_size, tl->position.y));
                vertices.push_back(ofVec3f(bl->position.x + half_size, bl->position.y));
                break;
            /*/////////||\\\\\\\\\\\
            //         ||         \\
            //  ○/  ●  ||  ●/  ○  \\
            //  /      ||  /      \\
            //  ●   ●  ||  ○   ○  \\
            //         ||         \\
            ///////////||\\\\\\\\\*/
            case 7:
            case 8:
//                mesh.addVertex(ofVec3f(tl->position.x, tl->position.y + half_size));
//                mesh.addVertex(ofVec3f(tl->position.x + half_size, tl->position.y));
                vertices.push_back(ofVec3f(tl->position.x, tl->position.y + half_size));
                vertices.push_back(ofVec3f(tl->position.x + half_size, tl->position.y));
                break;
            /*////|\\\\\\
            //         \\
            //  ●  \○  \\
            //  \   \  \\
            //  ○\  ●  \\
            //         \\
            //////|\\\\*/
            case 10: // saddle
//                mesh.addVertex(ofVec3f(bl->position.x, bl->position.y - half_size));
//                mesh.addVertex(ofVec3f(bl->position.x + half_size, bl->position.y));
//                mesh.addVertex(ofVec3f(tr->position.x - half_size, tr->position.y));
//                mesh.addVertex(ofVec3f(tr->position.x, tr->position.y + half_size));
                vertices.push_back(ofVec3f(bl->position.x, bl->position.y - half_size));
                vertices.push_back(ofVec3f(bl->position.x + half_size, bl->position.y));
                vertices.push_back(ofVec3f(tr->position.x - half_size, tr->position.y));
                vertices.push_back(ofVec3f(tr->position.x, tr->position.y + half_size));
                break;
            /*////|\\\\\\
            //         \\
            //  ●   ●  \\
            //         \\
            //  ●   ●  \\
            //         \\
            //////|\\\\*/
            case 15:
                break;
        }
    }
    CellUnit* tl = nullptr;
    CellUnit* tr = nullptr;
    CellUnit* br = nullptr;
    CellUnit* bl = nullptr;
    float size;
    float half_size;
    unsigned int state;
};

class ofApp : public ofBaseApp{
    
    unsigned int m_particle_count;
    vector<Particle> m_particles;
    vector<CellUnit> m_cell_units;
    vector<Cell> m_cells;
    ofMesh m_mesh;
    bool m_show_gui;
    ofxPanel m_panel;
    ofParameter<float> m_fitting;
    ofParameter<bool> m_show_particles;
    ofParameter<bool> m_move_particles;
    ofParameter<bool> m_show_cells;
    ofParameter<bool> m_show_mesh;
    ofParameter<bool> m_interpolate;
    ofParameter<bool> m_infill;
    
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
		
};
