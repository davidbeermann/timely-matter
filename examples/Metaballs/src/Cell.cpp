#include "Cell.hpp"


const unsigned int& Cell::updateState() {
    m_state = 0;
    m_state += m_blu->getValue() >= 1.f ? 1 : 0;
    m_state += m_bru->getValue() >= 1.f ? 2 : 0;
    m_state += m_tru->getValue() >= 1.f ? 4 : 0;
    m_state += m_tlu->getValue() >= 1.f ? 8 : 0;
    return m_state;
}


void Cell::calculateMesh(ofMesh& mesh, bool interpolated, bool infill) {
//    // create vector to temporarily store mesh vertices
//    vector<ofVec3f> vertices;
    
    // clear vertices
    m_vertices.clear();
    
    // add line vertices
    if (interpolated) {
//        calculateInterpolatedLines(vertices);
        calculateInterpolatedLines(m_vertices);
    } else {
//        calculateStraightLines(vertices);
        calculateStraightLines(m_vertices);
    }
    
    // m_truansform line vertices to m_truiangles to create solid mesh
    if (infill) {
//        transformLinesToInfill(vertices);
        transformLinesToInfill(m_vertices);
    }
    
    // add vertices to mesh
    vector<ofVec3f>::iterator v;
//    for (v = vertices.begin(); v != vertices.end(); ++v) {
    for (v = m_vertices.begin(); v != m_vertices.end(); ++v) {
        mesh.addVertex(*v);
    }
}


void Cell::calculateStraightLines(vector<ofVec3f>& vertices) {
    ofVec3f p0, p1, p2, p3;
    switch (m_state) {
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
             // 0○   ○  || 1●   ●  \\
             //  \      ||  \      \\
             //  ●\  ○  ||  ○\  ●  \\
             //    1    ||    0    \\
             ///////////||\\\\\\\\\*/
        case 1:
        case 14:
//            vertices.push_back(ofVec3f(m_blu->getPosition().x, m_blu->getPosition().y - m_half_size_y));
//            vertices.push_back(ofVec3f(m_blu->getPosition().x + m_half_size_x, m_blu->getPosition().y));
            p0.set(m_blu->getPosition().x, m_blu->getPosition().y - m_half_size_y);
            p1.set(m_blu->getPosition().x + m_half_size_x, m_blu->getPosition().y);
            vertices.push_back(m_state == 1 ? p0 : p1);
            vertices.push_back(m_state == 1 ? p1 : p0);
            break;
            /*/////////||\\\\\\\\\\\
             //         ||         \\
             //  ○   ○1 ||  ●   ●0 \\
             //      /  ||      /  \\
             //  ○  /●  ||  ●  /○  \\
             //    0    ||    1    \\
             ///////////||\\\\\\\\\*/
        case 2:
        case 13:
//            vertices.push_back(ofVec3f(m_bru->getPosition().x - m_half_size_x, m_bru->getPosition().y));
//            vertices.push_back(ofVec3f(m_bru->getPosition().x, m_bru->getPosition().y - m_half_size_y));
            p0.set(m_bru->getPosition().x - m_half_size_x, m_bru->getPosition().y);
            p1.set(m_bru->getPosition().x, m_bru->getPosition().y - m_half_size_y);
            vertices.push_back(m_state == 2 ? p0 : p1);
            vertices.push_back(m_state == 2 ? p1 : p0);
            break;
            /*/////////||\\\\\\\\\\\
             //         ||         \\
             //  ○   ○  ||  ●   ●  \\
             // 0-----1 || 1-----0 \\
             //  ●   ●  ||  ○   ○  \\
             //         ||         \\
             ///////////||\\\\\\\\\*/
        case 3:
        case 12:
//            vertices.push_back(ofVec3f(m_blu->getPosition().x, m_blu->getPosition().y - m_half_size_y));
//            vertices.push_back(ofVec3f(m_bru->getPosition().x, m_bru->getPosition().y - m_half_size_y));
            p0.set(m_blu->getPosition().x, m_blu->getPosition().y - m_half_size_y);
            p1.set(m_bru->getPosition().x, m_bru->getPosition().y - m_half_size_y);
            vertices.push_back(m_state == 3 ? p0 : p1);
            vertices.push_back(m_state == 3 ? p1 : p0);
            break;
            /*/////////||\\\\\\\\\\\
             //    0    ||    1    \\
             //  ○  \●  ||  ●  \○  \\
             //      \  ||      \  \\
             //  ○   ○1 ||  ●   ●0 \\
             //         ||         \\
             ///////////||\\\\\\\\\*/
        case 4:
        case 11:
//            vertices.push_back(ofVec3f(m_tru->getPosition().x - m_half_size_x, m_tru->getPosition().y));
//            vertices.push_back(ofVec3f(m_tru->getPosition().x, m_tru->getPosition().y + m_half_size_y));
            p0.set(m_tru->getPosition().x - m_half_size_x, m_tru->getPosition().y);
            p1.set(m_tru->getPosition().x, m_tru->getPosition().y + m_half_size_y);
            vertices.push_back(m_state == 4 ? p0 : p1);
            vertices.push_back(m_state == 4 ? p1 : p0);
            break;
            /*////|\\\\\\
             //    1    \\
             //  ○/  ●2 \\
             //  /   /  \\
             // 0●  /○  \\
             //    3    \\
             //////|\\\\*/
        case 5: // saddle
//            vertices.push_back(ofVec3f(m_blu->getPosition().x, m_blu->getPosition().y - m_half_size_y));
//            vertices.push_back(ofVec3f(m_tru->getPosition().x - m_half_size_x, m_tru->getPosition().y));
//            vertices.push_back(ofVec3f(m_blu->getPosition().x + m_half_size_x, m_blu->getPosition().y));
//            vertices.push_back(ofVec3f(m_tru->getPosition().x, m_tru->getPosition().y + m_half_size_y));
            p0.set(m_blu->getPosition().x, m_blu->getPosition().y - m_half_size_y);
            p1.set(m_tru->getPosition().x - m_half_size_x, m_tru->getPosition().y);
            p2.set(m_tru->getPosition().x, m_tru->getPosition().y + m_half_size_y);
            p3.set(m_blu->getPosition().x + m_half_size_x, m_blu->getPosition().y);
            vertices.push_back(p0);
            vertices.push_back(p1);
            vertices.push_back(p2);
            vertices.push_back(p3);
            break;
            /*/////////||\\\\\\\\\\\
             //    1    ||    0    \\
             //  ○ | ●  ||  ● | ○  \\
             //    |    ||    |    \\
             //  ○ | ●  ||  ● | ○  \\
             //    0    ||    1    \\
             ///////////||\\\\\\\\\*/
        case 6:
        case 9:
//            vertices.push_back(ofVec3f(m_tlu->getPosition().x + m_half_size_x, m_tlu->getPosition().y));
//            vertices.push_back(ofVec3f(m_blu->getPosition().x + m_half_size_x, m_blu->getPosition().y));
            p0.set(m_blu->getPosition().x + m_half_size_x, m_blu->getPosition().y);
            p1.set(m_tlu->getPosition().x + m_half_size_x, m_tlu->getPosition().y);
            vertices.push_back(m_state == 6 ? p0 : p1);
            vertices.push_back(m_state == 6 ? p1 : p0);
            break;
            /*/////////||\\\\\\\\\\\
             //    1    ||    0    \\
             //  ○/  ●  ||  ●/  ○  \\
             //  /      ||  /      \\
             // 0●   ●  || 1○   ○  \\
             //         ||         \\
             ///////////||\\\\\\\\\*/
        case 7:
        case 8:
//            vertices.push_back(ofVec3f(m_tlu->getPosition().x, m_tlu->getPosition().y + m_half_size_y));
//            vertices.push_back(ofVec3f(m_tlu->getPosition().x + m_half_size_x, m_tlu->getPosition().y));
            p0.set(m_tlu->getPosition().x, m_tlu->getPosition().y + m_half_size_y);
            p1.set(m_tlu->getPosition().x + m_half_size_x, m_tlu->getPosition().y);
            vertices.push_back(m_state == 7 ? p0 : p1);
            vertices.push_back(m_state == 7 ? p1 : p0);
            break;
            /*////|\\\\\\
             //    2    \\
             // 1●  \○  \\
             //  \   \  \\
             //  ○\  ●3 \\
             //    0    \\
             //////|\\\\*/
        case 10: // saddle
//            vertices.push_back(ofVec3f(m_blu->getPosition().x, m_blu->getPosition().y - m_half_size_y));
//            vertices.push_back(ofVec3f(m_blu->getPosition().x + m_half_size_x, m_blu->getPosition().y));
//            vertices.push_back(ofVec3f(m_tru->getPosition().x - m_half_size_x, m_tru->getPosition().y));
//            vertices.push_back(ofVec3f(m_tru->getPosition().x, m_tru->getPosition().y + m_half_size_y));
            p0.set(m_blu->getPosition().x + m_half_size_x, m_blu->getPosition().y);
            p1.set(m_blu->getPosition().x, m_blu->getPosition().y - m_half_size_y);
            p2.set(m_tru->getPosition().x - m_half_size_x, m_tru->getPosition().y);
            p3.set(m_tru->getPosition().x, m_tru->getPosition().y + m_half_size_y);
            vertices.push_back(p0);
            vertices.push_back(p1);
            vertices.push_back(p2);
            vertices.push_back(p3);
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


void Cell::calculateInterpolatedLines(vector<ofVec3f>& vertices) {
    switch (m_state) {
            
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
                m_blu->getPosition().x,
                m_tlu->getPosition().y + m_size_y * ((1.f - m_tlu->getValue())/(m_blu->getValue() - m_tlu->getValue()))
            ));
            vertices.push_back(ofVec3f(
                m_bru->getPosition().x - m_size_x * ((1.f - m_bru->getValue())/(m_blu->getValue() - m_bru->getValue())),
                m_blu->getPosition().y
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
                m_blu->getPosition().x + m_size_x * ((1.f - m_blu->getValue())/(m_bru->getValue() - m_blu->getValue())),
                m_bru->getPosition().y
            ));
            vertices.push_back(ofVec3f(
                m_bru->getPosition().x,
                m_tru->getPosition().y + m_size_y * ((1.f - m_tru->getValue())/(m_bru->getValue() - m_tru->getValue()))
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
                m_blu->getPosition().x,
                m_tlu->getPosition().y + m_size_y * ((1.f - m_tlu->getValue())/(m_blu->getValue() - m_tlu->getValue()))
            ));
            vertices.push_back(ofVec3f(
                m_bru->getPosition().x,
                m_tru->getPosition().y + m_size_y * ((1.f - m_tru->getValue())/(m_bru->getValue() - m_tru->getValue()))
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
                m_tlu->getPosition().x + m_size_x * ((1.f - m_tlu->getValue())/(m_tru->getValue() - m_tlu->getValue())),
                m_tru->getPosition().y
            ));
            vertices.push_back(ofVec3f(
                m_tru->getPosition().x,
                m_bru->getPosition().y - m_size_y * ((1.f - m_bru->getValue())/(m_tru->getValue() - m_bru->getValue()))
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
                m_blu->getPosition().x,
                m_tlu->getPosition().y + m_size_y * ((1.f - m_tlu->getValue())/(m_blu->getValue() - m_tlu->getValue()))
            ));
            vertices.push_back(ofVec3f(
                m_tlu->getPosition().x + m_size_x * ((1.f - m_tlu->getValue())/(m_tru->getValue() - m_tlu->getValue())),
                m_tru->getPosition().y
            ));
            vertices.push_back(ofVec3f(
                m_bru->getPosition().x - m_size_x * ((1.f - m_bru->getValue())/(m_blu->getValue() - m_bru->getValue())),
                m_blu->getPosition().y
            ));
            vertices.push_back(ofVec3f(
                m_tru->getPosition().x,
                m_bru->getPosition().y - m_size_y * ((1.f - m_bru->getValue())/(m_tru->getValue() - m_bru->getValue()))
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
                m_tlu->getPosition().x + m_size_x * ((1.f - m_tlu->getValue())/(m_tru->getValue() - m_tlu->getValue())),
                m_tru->getPosition().y
            ));
            vertices.push_back(ofVec3f(
                m_blu->getPosition().x + m_size_x * ((1.f - m_blu->getValue())/(m_bru->getValue() - m_blu->getValue())),
                m_bru->getPosition().y
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
                m_tlu->getPosition().x,
                m_blu->getPosition().y - m_size_y * ((1.f - m_blu->getValue())/(m_tlu->getValue() - m_blu->getValue()))
            ));
            vertices.push_back(ofVec3f(
                m_tru->getPosition().x - m_size_x * ((1.f - m_tru->getValue())/(m_tlu->getValue() - m_tru->getValue())),
                m_tlu->getPosition().y
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
                m_tlu->getPosition().x,
                m_blu->getPosition().y - m_size_y * ((1.f - m_blu->getValue())/(m_tlu->getValue() - m_blu->getValue()))
            ));
            vertices.push_back(ofVec3f(
                m_blu->getPosition().x + m_size_x * ((1.f - m_blu->getValue())/(m_bru->getValue() - m_blu->getValue())),
                m_bru->getPosition().y
            ));
            vertices.push_back(ofVec3f(
                m_tru->getPosition().x - m_size_x * ((1.f - m_tru->getValue())/(m_tlu->getValue() - m_tru->getValue())),
                m_tlu->getPosition().y
            ));
            vertices.push_back(ofVec3f(
                m_bru->getPosition().x,
                m_tru->getPosition().y + m_size_y * ((1.f - m_tru->getValue())/(m_bru->getValue() - m_tru->getValue()))
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


void Cell::transformLinesToInfill(vector<ofVec3f>& vertices) {
    ofVec3f p1, p2, p3, p4;
    switch (m_state) {
            
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
            // complete line to m_truiangle
            vertices.push_back(m_blu->getPosition());
            break;
            
        /*////|\\\\\\
        //         \\
        //  ○   ○  \\
        //      /  \\
        //  ○  /●  \\
        //         \\
        //////|\\\\*/
        case 2:
            // complete line to m_truiangle
            vertices.push_back(m_bru->getPosition());
            break;
            
        /*////|\\\\\\
        //         \\
        //  ○   ○  \\
        //  -----  \\
        //  ●   ●  \\
        //         \\
        //////|\\\\*/
        case 3:
            // complete line to m_truiangle
            vertices.push_back(m_bru->getPosition());
            
            // add missing m_truiangle
            vertices.push_back(m_bru->getPosition());
            vertices.push_back(m_blu->getPosition());
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
            // complete line to m_truiangle
            vertices.push_back(m_tru->getPosition());
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
            
            // add m_truiangles
            vertices.push_back(m_blu->getPosition());
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
            vertices.push_back(m_tru->getPosition());
            break;
            
        /*////|\\\\\\
        //         \\
        //  ○ | ●  \\
        //    |    \\
        //  ○ | ●  \\
        //         \\
        //////|\\\\*/
        case 6:
            // complete line to m_truiangle
            vertices.push_back(m_bru->getPosition());
            
            // add missing m_truiangle
            vertices.push_back(m_bru->getPosition());
            vertices.push_back(m_tru->getPosition());
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
            // complete line to m_truiangle
            vertices.push_back(m_bru->getPosition());
            
            // add missing m_truiangle
            vertices.push_back(m_bru->getPosition());
            vertices.push_back(m_blu->getPosition());
            vertices.push_back(vertices.at(0));
            
            vertices.push_back(m_bru->getPosition());
            vertices.push_back(m_tru->getPosition());
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
            // complete line to m_truiangle
            vertices.push_back(m_tlu->getPosition());
            break;
            
        /*////|\\\\\\
        //         \\
        //  ● | ○  \\
        //    |    \\
        //  ● | ○  \\
        //         \\
        //////|\\\\*/
        case 9:
            // complete line to m_truiangle
            vertices.push_back(m_blu->getPosition());
            
            // add missing m_truiangle
            vertices.push_back(m_blu->getPosition());
            vertices.push_back(m_tlu->getPosition());
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
            
            // add m_truiangles
            vertices.push_back(m_tlu->getPosition());
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
            vertices.push_back(m_bru->getPosition());
            break;
            
        /*////|\\\\\\
        //         \\
        //  ●  \○  \\
        //      \  \\
        //  ●   ●  \\
        //         \\
        //////|\\\\*/
        case 11:
            // complete line to m_truiangle
            vertices.push_back(m_blu->getPosition());
            
            // add missing m_truiangles
            vertices.push_back(m_tlu->getPosition());
            vertices.push_back(m_blu->getPosition());
            vertices.push_back(vertices.at(0));
            
            vertices.push_back(m_blu->getPosition());
            vertices.push_back(m_bru->getPosition());
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
            // complete line to m_truiangle
            vertices.push_back(m_tlu->getPosition());
            
            // add missing m_truiangle
            vertices.push_back(m_tlu->getPosition());
            vertices.push_back(m_tru->getPosition());
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
            // complete line to m_truiangle
            vertices.push_back(m_tlu->getPosition());
            
            // add missing m_truiangles
            vertices.push_back(m_tlu->getPosition());
            vertices.push_back(m_blu->getPosition());
            vertices.push_back(vertices.at(0));
            
            vertices.push_back(m_tlu->getPosition());
            vertices.push_back(m_tru->getPosition());
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
            // complete line to m_truiangle
            vertices.push_back(m_tru->getPosition());
            
            // add missing m_truiangles
            vertices.push_back(m_tru->getPosition());
            vertices.push_back(m_bru->getPosition());
            vertices.push_back(vertices.at(1));
            
            vertices.push_back(vertices.at(0));
            vertices.push_back(m_tlu->getPosition());
            vertices.push_back(m_tru->getPosition());
            break;
            
        /*////|\\\\\\
        //         \\
        //  ●   ●  \\
        //         \\
        //  ●   ●  \\
        //         \\
        //////|\\\\*/
        case 15:
            vertices.push_back(m_tlu->getPosition());
            vertices.push_back(m_blu->getPosition());
            vertices.push_back(m_tru->getPosition());
            vertices.push_back(m_blu->getPosition());
            vertices.push_back(m_tru->getPosition());
            vertices.push_back(m_bru->getPosition());
            break;
    }
}

