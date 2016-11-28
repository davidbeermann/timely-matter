#include "Cell.hpp"


void Cell::update(bool interpolated) {
    // update state of cell
    m_state = 0;
    m_state += m_blu->getValue() >= 1.f ? 1 : 0;
    m_state += m_bru->getValue() >= 1.f ? 2 : 0;
    m_state += m_tru->getValue() >= 1.f ? 4 : 0;
    m_state += m_tlu->getValue() >= 1.f ? 8 : 0;
    
    // clear vertices
    m_vertices.clear();
    
    // add appropriate line vertices
    if (interpolated) {
        calculateInterpolatedLines();
    } else {
        calculateStraightLines();
    }
}


void Cell::calculateStraightLines() {
    ofVec3f p0, p1;
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
            p0.set(m_blu->getPosition().x, m_blu->getPosition().y - m_half_size_y);
            p1.set(m_blu->getPosition().x + m_half_size_x, m_blu->getPosition().y);
            m_vertices.push_back(m_state == 1 ? p0 : p1);
            m_vertices.push_back(m_state == 1 ? p1 : p0);
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
            p0.set(m_bru->getPosition().x - m_half_size_x, m_bru->getPosition().y);
            p1.set(m_bru->getPosition().x, m_bru->getPosition().y - m_half_size_y);
            m_vertices.push_back(m_state == 2 ? p0 : p1);
            m_vertices.push_back(m_state == 2 ? p1 : p0);
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
            p0.set(m_blu->getPosition().x, m_blu->getPosition().y - m_half_size_y);
            p1.set(m_bru->getPosition().x, m_bru->getPosition().y - m_half_size_y);
            m_vertices.push_back(m_state == 3 ? p0 : p1);
            m_vertices.push_back(m_state == 3 ? p1 : p0);
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
            p0.set(m_tru->getPosition().x - m_half_size_x, m_tru->getPosition().y);
            p1.set(m_tru->getPosition().x, m_tru->getPosition().y + m_half_size_y);
            m_vertices.push_back(m_state == 4 ? p0 : p1);
            m_vertices.push_back(m_state == 4 ? p1 : p0);
            break;
            
        /*////|\\\\\\
        //    1    \\
        //  ○/  ●2 \\
        //  /   /  \\
        // 0●  /○  \\
        //    3    \\
        //////|\\\\*/
        case 5: // saddle
            m_vertices.push_back(ofVec3f(m_blu->getPosition().x, m_blu->getPosition().y - m_half_size_y));
            m_vertices.push_back(ofVec3f(m_tru->getPosition().x - m_half_size_x, m_tru->getPosition().y));
            m_vertices.push_back(ofVec3f(m_tru->getPosition().x, m_tru->getPosition().y + m_half_size_y));
            m_vertices.push_back(ofVec3f(m_blu->getPosition().x + m_half_size_x, m_blu->getPosition().y));
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
            p0.set(m_blu->getPosition().x + m_half_size_x, m_blu->getPosition().y);
            p1.set(m_tlu->getPosition().x + m_half_size_x, m_tlu->getPosition().y);
            m_vertices.push_back(m_state == 6 ? p0 : p1);
            m_vertices.push_back(m_state == 6 ? p1 : p0);
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
            p0.set(m_tlu->getPosition().x, m_tlu->getPosition().y + m_half_size_y);
            p1.set(m_tlu->getPosition().x + m_half_size_x, m_tlu->getPosition().y);
            m_vertices.push_back(m_state == 7 ? p0 : p1);
            m_vertices.push_back(m_state == 7 ? p1 : p0);
            break;
            
        /*////|\\\\\\
        //    2    \\
        // 1●  \○  \\
        //  \   \  \\
        //  ○\  ●3 \\
        //    0    \\
        //////|\\\\*/
        case 10: // saddle
            m_vertices.push_back(ofVec3f(m_blu->getPosition().x + m_half_size_x, m_blu->getPosition().y));
            m_vertices.push_back(ofVec3f(m_blu->getPosition().x, m_blu->getPosition().y - m_half_size_y));
            m_vertices.push_back(ofVec3f(m_tru->getPosition().x - m_half_size_x, m_tru->getPosition().y));
            m_vertices.push_back(ofVec3f(m_tru->getPosition().x, m_tru->getPosition().y + m_half_size_y));
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


void Cell::calculateInterpolatedLines() {
    ofVec3f p0, p1;
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
            p0.x = m_blu->getPosition().x;
            p0.y = m_tlu->getPosition().y + m_size_y * ((1.f - m_tlu->getValue())/(m_blu->getValue() - m_tlu->getValue()));
            p1.x = m_bru->getPosition().x - m_size_x * ((1.f - m_bru->getValue())/(m_blu->getValue() - m_bru->getValue()));
            p1.y = m_blu->getPosition().y;
            m_vertices.push_back(m_state == 1 ? p0 : p1);
            m_vertices.push_back(m_state == 1 ? p1 : p0);
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
            p0.x = m_blu->getPosition().x + m_size_x * ((1.f - m_blu->getValue())/(m_bru->getValue() - m_blu->getValue()));
            p0.y = m_bru->getPosition().y;
            p1.x = m_bru->getPosition().x;
            p1.y = m_tru->getPosition().y + m_size_y * ((1.f - m_tru->getValue())/(m_bru->getValue() - m_tru->getValue()));
            m_vertices.push_back(m_state == 2 ? p0 : p1);
            m_vertices.push_back(m_state == 2 ? p1 : p0);
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
            p0.x = m_blu->getPosition().x;
            p0.y = m_tlu->getPosition().y + m_size_y * ((1.f - m_tlu->getValue())/(m_blu->getValue() - m_tlu->getValue()));
            p1.x = m_bru->getPosition().x;
            p1.y = m_tru->getPosition().y + m_size_y * ((1.f - m_tru->getValue())/(m_bru->getValue() - m_tru->getValue()));
            m_vertices.push_back(m_state == 3 ? p0 : p1);
            m_vertices.push_back(m_state == 3 ? p1 : p0);
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
            p0.x = m_tlu->getPosition().x + m_size_x * ((1.f - m_tlu->getValue())/(m_tru->getValue() - m_tlu->getValue()));
            p0.y = m_tru->getPosition().y;
            p1.x = m_tru->getPosition().x;
            p1.y = m_bru->getPosition().y - m_size_y * ((1.f - m_bru->getValue())/(m_tru->getValue() - m_bru->getValue()));
            m_vertices.push_back(m_state == 4 ? p0 : p1);
            m_vertices.push_back(m_state == 4 ? p1 : p0);
            break;
            
        /*////|\\\\\\
        //    1    \\
        //  ○/  ●2 \\
        //  /   /  \\
        // 0●  /○  \\
        //    3    \\
        //////|\\\\*/
        case 5: // saddle
            m_vertices.push_back(ofVec3f(
                m_blu->getPosition().x,
                m_tlu->getPosition().y + m_size_y * ((1.f - m_tlu->getValue())/(m_blu->getValue() - m_tlu->getValue()))
            ));
            m_vertices.push_back(ofVec3f(
                m_tlu->getPosition().x + m_size_x * ((1.f - m_tlu->getValue())/(m_tru->getValue() - m_tlu->getValue())),
                m_tru->getPosition().y
            ));
            m_vertices.push_back(ofVec3f(
                m_tru->getPosition().x,
                m_bru->getPosition().y - m_size_y * ((1.f - m_bru->getValue())/(m_tru->getValue() - m_bru->getValue()))
            ));
            m_vertices.push_back(ofVec3f(
                m_bru->getPosition().x - m_size_x * ((1.f - m_bru->getValue())/(m_blu->getValue() - m_bru->getValue())),
                m_blu->getPosition().y
            ));
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
            p0.x = m_blu->getPosition().x + m_size_x * ((1.f - m_blu->getValue())/(m_bru->getValue() - m_blu->getValue()));
            p0.y = m_bru->getPosition().y;
            p1.x = m_tlu->getPosition().x + m_size_x * ((1.f - m_tlu->getValue())/(m_tru->getValue() - m_tlu->getValue()));
            p1.y = m_tru->getPosition().y;
            m_vertices.push_back(m_state == 6 ? p0 : p1);
            m_vertices.push_back(m_state == 6 ? p1 : p0);
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
            p0.x = m_tlu->getPosition().x;
            p0.y = m_blu->getPosition().y - m_size_y * ((1.f - m_blu->getValue())/(m_tlu->getValue() - m_blu->getValue()));
            p1.x = m_tru->getPosition().x - m_size_x * ((1.f - m_tru->getValue())/(m_tlu->getValue() - m_tru->getValue()));
            p1.y = m_tlu->getPosition().y;
            m_vertices.push_back(m_state == 7 ? p0 : p1);
            m_vertices.push_back(m_state == 7 ? p1 : p0);
            break;
            
        /*////|\\\\\\
        //    2    \\
        // 1●  \○  \\
        //  \   \  \\
        //  ○\  ●3 \\
        //    0    \\
        //////|\\\\*/
        case 10: // saddle
            m_vertices.push_back(ofVec3f(
                m_blu->getPosition().x + m_size_x * ((1.f - m_blu->getValue())/(m_bru->getValue() - m_blu->getValue())),
                m_bru->getPosition().y
            ));
            m_vertices.push_back(ofVec3f(
                m_tlu->getPosition().x,
                m_blu->getPosition().y - m_size_y * ((1.f - m_blu->getValue())/(m_tlu->getValue() - m_blu->getValue()))
            ));
            m_vertices.push_back(ofVec3f(
                m_tru->getPosition().x - m_size_x * ((1.f - m_tru->getValue())/(m_tlu->getValue() - m_tru->getValue())),
                m_tlu->getPosition().y
            ));
            m_vertices.push_back(ofVec3f(
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


void Cell::transformLinesToNaiveInfill() {
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
            
        /*////|\\\\\\
        //         \\
        // 0○   ○  \\
        //  \      \\
        //  ●\  ○  \\
        //    1    \\
        //////|\\\\*/
        case 1:
            // complete line to triangle
            m_vertices.push_back(m_blu->getPosition());
            break;
            
        /*////|\\\\\\
        //         \\
        //  ○   ○1 \\
        //      /  \\
        //  ○  /●  \\
        //    0    \\
        //////|\\\\*/
        case 2:
            // complete line to triangle
            m_vertices.push_back(m_bru->getPosition());
            break;
            
        /*////|\\\\\\
        //         \\
        //  ○   ○  \\
        // 0-----1 \\
        //  ●   ●  \\
        //         \\
        //////|\\\\*/
        case 3:
            // complete line to triangle
            m_vertices.push_back(m_bru->getPosition());
            
            // add missing triangle
            m_vertices.push_back(m_bru->getPosition());
            m_vertices.push_back(m_blu->getPosition());
            m_vertices.push_back(m_vertices.at(0));
            break;
            
        /*////|\\\\\\
        //    0    \\
        //  ○  \●  \\
        //      \  \\
        //  ○   ○1 \\
        //         \\
        //////|\\\\*/
        case 4:
            // complete line to triangle
            m_vertices.push_back(m_tru->getPosition());
            break;
            
        /*////|\\\\\\
        //    1    \\
        //  ○/  ●2 \\
        //  /   /  \\
        // 0●  /○  \\
        //    3    \\
        //////|\\\\*/
        case 5:
            // store vertices for reference
            p0 = ofVec3f(m_vertices.at(0));
            p1 = ofVec3f(m_vertices.at(1));
            p2 = ofVec3f(m_vertices.at(2));
            p3 = ofVec3f(m_vertices.at(3));
            
            // clear vector
            m_vertices.clear();
            
            // add triangles
            m_vertices.push_back(m_blu->getPosition());
            m_vertices.push_back(p0);
            m_vertices.push_back(p3);
            
            m_vertices.push_back(p0);
            m_vertices.push_back(p1);
            m_vertices.push_back(p3);
            
            m_vertices.push_back(p1);
            m_vertices.push_back(p2);
            m_vertices.push_back(p3);
            
            m_vertices.push_back(p1);
            m_vertices.push_back(p2);
            m_vertices.push_back(m_tru->getPosition());
            break;
            
        /*////|\\\\\\
        //    1    \\
        //  ○ | ●  \\
        //    |    \\
        //  ○ | ●  \\
        //    0    \\
        //////|\\\\*/
        case 6:
            // complete line to triangle
            m_vertices.push_back(m_tru->getPosition());
            
            // add missing triangle
            m_vertices.push_back(m_tru->getPosition());
            m_vertices.push_back(m_bru->getPosition());
            m_vertices.push_back(m_vertices.at(0));
            break;
            
        /*////|\\\\\\
        //    1    \\
        //  ○/  ●  \\
        //  /      \\
        // 0●   ●  \\
        //         \\
        //////|\\\\*/
        case 7:
            // complete line to triangle
            m_vertices.push_back(m_bru->getPosition());
            
            // add missing triangle
            m_vertices.push_back(m_bru->getPosition());
            m_vertices.push_back(m_blu->getPosition());
            m_vertices.push_back(m_vertices.at(0));
            
            m_vertices.push_back(m_bru->getPosition());
            m_vertices.push_back(m_tru->getPosition());
            m_vertices.push_back(m_vertices.at(1));
            break;
            
        /*////|\\\\\\
        //    0    \\
        //  ●/  ○  \\
        //  /      \\
        // 1○   ○  \\
        //         \\
        //////|\\\\*/
        case 8:
            // complete line to triangle
            m_vertices.push_back(m_tlu->getPosition());
            break;
            
        /*////|\\\\\\
        //    0    \\
        //  ● | ○  \\
        //    |    \\
        //  ● | ○  \\
        //    1    \\
        //////|\\\\*/
        case 9:
            // complete line to triangle
            m_vertices.push_back(m_blu->getPosition());
            
            // add missing triangle
            m_vertices.push_back(m_blu->getPosition());
            m_vertices.push_back(m_tlu->getPosition());
            m_vertices.push_back(m_vertices.at(0));
            break;
            
        /*////|\\\\\\
        //    2    \\
        // 1●  \○  \\
        //  \   \  \\
        //  ○\  ●3 \\
        //    0    \\
        //////|\\\\*/
        case 10:
            // store vertices for reference
            p0 = ofVec3f(m_vertices.at(0));
            p1 = ofVec3f(m_vertices.at(1));
            p2 = ofVec3f(m_vertices.at(2));
            p3 = ofVec3f(m_vertices.at(3));
            
            // clear vector
            m_vertices.clear();
            
            // add triangles
            m_vertices.push_back(m_tlu->getPosition());
            m_vertices.push_back(p1);
            m_vertices.push_back(p2);
            
            m_vertices.push_back(p0);
            m_vertices.push_back(p1);
            m_vertices.push_back(p2);
            
            m_vertices.push_back(p0);
            m_vertices.push_back(p2);
            m_vertices.push_back(p3);
            
            m_vertices.push_back(p0);
            m_vertices.push_back(p3);
            m_vertices.push_back(m_bru->getPosition());
            break;
            
        /*////|\\\\\\
        //    1    \\
        //  ●  \○  \\
        //      \  \\
        //  ●   ●0 \\
        //         \\
        //////|\\\\*/
        case 11:
            // complete line to triangle
            m_vertices.push_back(m_blu->getPosition());
            
            // add missing triangles
            m_vertices.push_back(m_tlu->getPosition());
            m_vertices.push_back(m_blu->getPosition());
            m_vertices.push_back(m_vertices.at(1));
            
            m_vertices.push_back(m_blu->getPosition());
            m_vertices.push_back(m_bru->getPosition());
            m_vertices.push_back(m_vertices.at(0));
            break;
            
        /*////|\\\\\\
        //         \\
        //  ●   ●  \\
        // 1-----0 \\
        //  ○   ○  \\
        //         \\
        //////|\\\\*/
        case 12:
            // complete line to triangle
            m_vertices.push_back(m_tlu->getPosition());
            
            // add missing triangle
            m_vertices.push_back(m_tlu->getPosition());
            m_vertices.push_back(m_tru->getPosition());
            m_vertices.push_back(m_vertices.at(0));
            break;
            
        /*////|\\\\\\
        //         \\
        //  ●   ●0 \\
        //      /  \\
        //  ●  /○  \\
        //    1    \\
        //////|\\\\*/
        case 13:
            // complete line to triangle
            m_vertices.push_back(m_tlu->getPosition());
            
            // add missing triangles
            m_vertices.push_back(m_tlu->getPosition());
            m_vertices.push_back(m_blu->getPosition());
            m_vertices.push_back(m_vertices.at(1));
            
            m_vertices.push_back(m_tlu->getPosition());
            m_vertices.push_back(m_tru->getPosition());
            m_vertices.push_back(m_vertices.at(0));
            break;
            
        /*////|\\\\\\
        //         \\
        // 1●   ●  \\
        //  \      \\
        //  ○\  ●  \\
        //    0    \\
        //////|\\\\*/
        case 14:
            // complete line to triangle
            m_vertices.push_back(m_tru->getPosition());
            
            // add missing triangles
            m_vertices.push_back(m_tru->getPosition());
            m_vertices.push_back(m_bru->getPosition());
            m_vertices.push_back(m_vertices.at(0));
            
            m_vertices.push_back(m_vertices.at(1));
            m_vertices.push_back(m_tlu->getPosition());
            m_vertices.push_back(m_tru->getPosition());
            break;
            
        /*////|\\\\\\
        //         \\
        //  ●   ●  \\
        //         \\
        //  ●   ●  \\
        //         \\
        //////|\\\\*/
        case 15:
            m_vertices.push_back(m_tlu->getPosition());
            m_vertices.push_back(m_blu->getPosition());
            m_vertices.push_back(m_tru->getPosition());
            m_vertices.push_back(m_blu->getPosition());
            m_vertices.push_back(m_tru->getPosition());
            m_vertices.push_back(m_bru->getPosition());
            break;
    }
}

