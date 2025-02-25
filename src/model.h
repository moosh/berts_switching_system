/*******************************************************************************

    model.h

    Copyright (c) 2025 Mooshwerks
    All Rights Reserved

    The model class is a container for the application's state or view of the
    world. It does NOT include any sort of "business logic" that uses the state.
    Instead, it offers controlled access to state data for other classes (see Controller)
    to access and do what it pleases.
    
*******************************************************************************/

// The following #pragma line of code makes sure the c++ preprocessor doesn't load this file more than once.
// In other files we may #include model.h, but without this line, each time the preprocessor encounters
// the #include it would try to add the "Model" class to it's view of the world. The first time would be
// OK but subsequent times it would think you're defining "Model" all over again and will have a heart
// attack, spewing error messages along the way. So just include "Model" once with this bit of code
#pragma once

#include <Arduino.h>

class Model
{
private:
    bool _relay1State;
    bool _relay2State;

public:
    void init()
    {
        _relay1State = true;
        _relay2State = true;
    }

    bool getRelay1State() { return _relay1State; }
    void setRelay1State(bool inState) { _relay1State = inState; }

    bool getRelay2State() { return _relay2State; }
    void setRelay2State(bool inState) { _relay2State = inState; }
};

