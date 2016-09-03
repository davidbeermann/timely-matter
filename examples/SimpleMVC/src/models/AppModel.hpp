#pragma once

#include "ofMain.h"

// forward declaration to solve cyclical dependency
class AppEvents;


enum class AppState : uint8_t {
    INIT = 0,
    INTRO = 1,
    OUTRO = 2
};


class AppModel {
    // private constructor
    AppModel();
    AppEvents& m_events;
    AppState m_state;
    int m_value;
public:
    static AppModel& get();
    
    // remove copy constructor and and copy assingnment operator - C++ 11 style
    AppModel(AppModel const&) = delete;
    void operator=(AppModel const&) = delete;
    
    // model events
    ofEvent<AppState> state_updated;
    ofEvent<int> value_updated;
    
    // command interface
    const AppState& getState() const;
    void setState(AppState& state);
    const int& getValue() const;
    void setValue(const int value);
};