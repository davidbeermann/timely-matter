#include "IntroView.hpp"
#include "AppEvents.hpp"


void IntroView::m_doSetup() {
    ofAddListener(m_model.value_updated, this, &IntroView::onValueUpdated);
}


void IntroView::m_doUpdate() {
    if (ofGetFrameNum() % 15) {
        IntroViewArgs args;
        args.value = (int) ofRandom(10000);

        ofNotifyEvent(update_value, args, this);
    }
}


void IntroView::m_doDraw() {
    ofDrawBitmapString("INTRO: " + to_string(m_value) + "\nPress 'Return' to continue.", 30, 30);
}


IntroView::IntroView() {
    ofLog() << "IntroView()";
    ofRegisterKeyEvents(this);
}


IntroView::~IntroView() {
    ofLog() << "~IntroView()";
    ofUnregisterKeyEvents(this);
}


void IntroView::onValueUpdated(int& value) {
    m_value = value;
}


void IntroView::keyPressed(ofKeyEventArgs& args) {
    if (args.key == OF_KEY_RETURN) {
        AppState state = AppState::OUTRO;
        ofNotifyEvent(AppEvents::get().change_state, state, this);
    }
}
