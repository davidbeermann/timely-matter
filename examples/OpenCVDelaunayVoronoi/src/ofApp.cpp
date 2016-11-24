#include "ofApp.h"


ofColor ofApp::averageColor(vector<ofColor>& colors) {
    unsigned int red = 0, green = 0, blue = 0, alpha = 0;
    vector<ofColor>::iterator it;
    for (it = colors.begin(); it != colors.end(); ++it) {
        red += it->r;
        green += it->g;
        blue += it->b;
        alpha += it->a;
    }
    return ofColor(red / colors.size(), green / colors.size(), blue / colors.size(), alpha / colors.size());
}


ofFloatColor ofApp::averageFloatColor(vector<ofColor>& colors) {
    float r = 0.f, g = 0.f, b = 0.f, a = 0.f;
    vector<ofColor>::iterator it;
    for (it = colors.begin(); it != colors.end(); ++it) {
        r += (float) it->r / 255.f;
        g += (float) it->g / 255.f;
        b += (float) it->b / 255.f;
        a += (float) it->a / 255.f;
    }
    float count = (float) colors.size();
    return ofFloatColor(r/count, g/count, b/count, a/count);
}


void ofApp::setup() {
    m_image.load("BarackObama.jpg");
    
//    cv::Rect rect(0.f, 0.f, m_image.getWidth(), m_image.getHeight());
    m_boundary.x = 0.f;
    m_boundary.y = 0.f;
    m_boundary.width = m_image.getWidth();
    m_boundary.height = m_image.getHeight();

    m_subdivision.initDelaunay(m_boundary);
    
//    m_points.push_back(cv::Point2f(0.f, 0.f));
////    ofLog() << m_boundary.contains(cv::Point2f(m_boundary.width, 0.f)); // false
////    ofLog() << m_boundary.contains(cv::Point2f(m_boundary.width-1, 0.f)); // true
//    m_points.push_back(cv::Point2f(m_boundary.width-1, 0.f));
//    m_points.push_back(cv::Point2f(m_boundary.width-1, m_boundary.height-1));
//    m_points.push_back(cv::Point2f(0.f, m_boundary.height-1));
    
//    for (int i = 0; i < 10; ++i) {
//        m_points.push_back(cv::Point2f(ofRandom(20.f, m_boundary.width-20.f), ofRandom(20.f, m_boundary.height-20.f)));
//    }
//    
//    ofLog() << "point count:" << m_points.size();
    
    m_subdivision.insert(m_points);
    
    windowResized(ofGetWidth(), ofGetHeight());
    
    m_delaunay_mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    m_delaunay_mesh.usingColors();
    
    m_voronoi_mesh.setMode(OF_PRIMITIVE_LINES);
}


void ofApp::update() {
    //  UPDATE DELAUNAY MESH
    // ----------------------
    m_delaunay_mesh.clear();
    
    m_subdivision.getTriangleList(m_triangles);

    vector<cv::Point2f> points(3);
    if (m_triangles.size() > 0) {
        for (size_t i = 0; i < m_triangles.size(); ++i) {
            cv::Vec6f& t = m_triangles[i];
            
            points[0] = cv::Point2f(t[0], t[1]);
            points[1] = cv::Point2f(t[2], t[3]);
            points[2] = cv::Point2f(t[4], t[5]);
            
            if (m_boundary.contains(points[0]) && m_boundary.contains(points[1]) && m_boundary.contains(points[2])) {
                vector<cv::Point2f>::iterator p;
                vector<ofColor> colors;
                for (p = points.begin(); p != points.end(); ++p) {
                    m_delaunay_mesh.addVertex(ofVec3f(p->x, p->y, 0.f));
//                    m_delaunay_mesh.addColor(ofFloatColor(m_image.getColor(round(p->x), round(p->y))));
                    colors.push_back(m_image.getColor(round(p->x), round(p->y)));
                }
                ofFloatColor c = averageFloatColor(colors);
                m_delaunay_mesh.addColor(c);
                m_delaunay_mesh.addColor(c);
                m_delaunay_mesh.addColor(c);
            }
        }
    }
    
    //  UPDATE VORONOI MESH
    // ---------------------
    m_voronoi_mesh.clear();
    
    vector<vector<cv::Point2f>> facets;
    vector<cv::Point2f> centers;
    
    m_subdivision.getVoronoiFacetList(vector<int>(), facets, centers);
    
    vector<cv::Point2f>::iterator it;
    for (size_t i = 0; i < facets.size(); i++) {
        vector<cv::Point2f> points = facets[i];
        cv::Point2f next;
        for(it = points.begin(); it != points.end(); ++it) {
            next = it+1 == points.end() ? *points.begin() : *(it+1);
            m_voronoi_mesh.addVertex(ofVec3f(it->x, it->y, 0.f));
            m_voronoi_mesh.addVertex(ofVec3f(next.x, next.y, 0.f));
        }
    }
    
    
//    vector<cv::Point> ifacet;
//    vector<vector<cv::Point>> ifacets(1);
//    
//    for( size_t i = 0; i < facets.size(); i++ )
//    {
//        ifacet.resize(facets[i].size());
//        for( size_t j = 0; j < facets[i].size(); j++ ) {
//            ifacet[j] = facets[i][j];
//        }
//        
//        cv::Scalar color;
//        color[0] = rand() & 255;
//        color[1] = rand() & 255;
//        color[2] = rand() & 255;
//        fillConvexPoly(img, ifacet, color, 8, 0);
//        
//        ifacets[0] = ifacet;
//        polylines(img, ifacets, true, Scalar(), 1, CV_AA, 0);
//        circle(img, centers[i], 3, Scalar(), CV_FILLED, CV_AA, 0);
//    }
}


void ofApp::draw() {
    
    ofPushMatrix();
    ofTranslate(m_image_pos);

    m_image.draw(0.f, 0.f);
    
    m_delaunay_mesh.draw();
    m_voronoi_mesh.draw();
    
//    ofPushStyle();
//    ofSetColor(0, 255, 0);
//    vector<cv::Point2f> points(3);
//    if (m_triangles.size() > 0) {
//        for (size_t i = 0; i < m_triangles.size(); ++i) {
//            cv::Vec6f& t = m_triangles[i];
//            ofLog() << t;
//            points[0] = cv::Point2f(t[0], t[1]);
//            points[1] = cv::Point2f(t[2], t[3]);
//            points[2] = cv::Point2f(t[4], t[5]);
//            
//            if (m_boundary.contains(points[0]) && m_boundary.contains(points[1]) && m_boundary.contains(points[2])) {
////            if (m_boundary.contains(points[0]) && m_boundary.contains(points[1])) {
//                ofDrawLine(points[0].x, points[0].y, points[1].x, points[1].y);
////            }
////            if (m_boundary.contains(points[1]) && m_boundary.contains(points[2])) {
//                ofDrawLine(points[1].x, points[1].y, points[2].x, points[2].y);
////            }
////            if (m_boundary.contains(points[2]) && m_boundary.contains(points[0])) {
//                ofDrawLine(points[2].x, points[2].y, points[0].x, points[0].y);
////            }
//            }
//        }
//    }
//    ofPopStyle();
    
    vector<cv::Point2f>::iterator p;
    for (p = m_points.begin(); p != m_points.end(); ++p) {
        ofPushStyle();
        ofSetColor(255, 0, 0);
        ofDrawCircle(p->x, p->y, 4.f);
        ofPopStyle();
    }
    
    ofPopMatrix();
}


void ofApp::mouseReleased(int x, int y, int button) {
    cv::Point2f new_point(x - m_image_pos.x, y - m_image_pos.y);
//    cv::Point2f new_point(x, y);
    ofLog() << "x:" << new_point.x << " - y:" << new_point.y;
    
    if (m_boundary.contains(new_point)) {
        m_points.push_back(new_point);
        m_subdivision.insert(new_point);
    }
}


void ofApp::windowResized(int w, int h) {
    m_image_pos.set((w - m_image.getWidth()) * 0.5f, (h - m_image.getHeight()) * 0.5f);
}

