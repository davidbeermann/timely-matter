#include "OutroView.hpp"
#include "AppEvents.hpp"



void OutroView::m_doSetup() {
    m_value = m_model.getValue();
}


void OutroView::m_doUpdate() {
}


void OutroView::m_doDraw() {
    ofDrawBitmapString("OUTRO: " + to_string(m_value), 30, 30);
}


OutroView::OutroView() {
    ofLog() << "OutroView()";
}


OutroView::~OutroView() {
    ofLog() << "~OutroView()";
}


