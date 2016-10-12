#include "DebugView.h"
#include "Line.h"
#include "MarchingSquares.h"

DebugView::DebugView() {
    mFont.load("RobotoMono-Medium.ttf", 10);

    mGuiParameters.setName("Debug Options");
    mGuiParameters.add(mDebugMeterPoints.set("Show Meter Points", false));
    mGuiParameters.add(mDebugMarchingSquares.set("Show Marching Squares Results", false));
    mGuiParameters.add(mDebugIsoLines.set("Show Iso Lines", true));
    mGuiParameters.add(mDebugForces.set("Show Force Vectors", false));
}


void DebugView::draw(const vector<MeterGridPoint> &gridPoints, const vector<MeterGridUnit> &gridUnits) {

    if (mDebugMeterPoints.get()) {
        ofPushStyle();
        ofSetColor(ofColor(0.f, 255.f, 0.f));

        vector<MeterGridPoint>::const_iterator point;
        for (point = gridPoints.begin(); point != gridPoints.end(); ++point) {
            if (point->isAboveThreshold()) {
                ofFill();
            } else {
                ofNoFill();
            }
            ofPushMatrix();
            ofTranslate(point->x(), point->y());
            ofDrawCircle(0, 0, 3);
            ofPopMatrix();
        }

        ofPopStyle();
    }

    ofPushStyle();
    ofNoFill();

    if (mDebugMarchingSquares.get() || mDebugForces.get()) {
        ofSetColor(ofColor(0.f, 0.f, 255.f));

        vector<MeterGridUnit>::const_iterator unit;
        string value;
        float valueWidth, valueHeight;
        for (unit = gridUnits.begin(); unit != gridUnits.end(); ++unit) {
            if (mDebugMarchingSquares.get()) {
                value = to_string(unit->getWeight());
                valueWidth = mFont.stringWidth(value);
                valueHeight = mFont.stringHeight(value);
                mFont.drawString(value, unit->getCenter()->x - valueWidth * 0.5f, unit->getCenter()->y + valueHeight * 0.5f);
            }

            if (mDebugForces.get() && (unit->getForce().length() > 0)) {
                ofVec2f direction(unit->getForce());
                ofVec2f offset(unit->getForce());
                direction.x *= unit->getWidth() * 0.5f;
                direction.y *= unit->getHeight() * 0.5f;
                offset.x *= unit->getWidth() * 0.25f;
                offset.y *= unit->getHeight() * 0.25f;

                ofPushMatrix();
                ofTranslate(unit->getCenter()->x - offset.x, unit->getCenter()->y - offset.y);
                ofDrawArrow(ofVec2f(), direction, 5.f);
                ofPopMatrix();
            }
        }
    }

    if (mDebugIsoLines.get()) {
        ofSetColor(ofColor(255.f, 0.f, 0.f));

        vector<Line> lines;
        MarchingSquares::getUnitLines(gridUnits, lines);
        vector<Line>::iterator line;
        for (line = lines.begin(); line != lines.end(); ++line) {
            line->draw();
        }
    }

    ofPopStyle();
}


ofParameterGroup DebugView::getGuiParameters() {
    return mGuiParameters;
}





