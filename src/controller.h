/*******************************************************************************

    controller.h

    Copyright (c) 2025 Mooshwerks
    All Rights Reserved

    The Controller class contains the "business logic" of the app. It looks
    at the state of the world via the Model and does whatever the app needs
    to do. The controller may also modify the state of the app, via the Model's
    public function call interfaces.
    
*******************************************************************************/

// The following #pragma line of code makes sure the c++ preprocessor doesn't load this file more than once.
// In other files we may #include controller.h, but without this line, each time the preprocessor encounters
// the #include it would try to add the "Controller" class to it's view of the world. The first time would be
// OK but subsequent times it would think you're defining "Controller" all over again and will have a heart
// attack, spewing error messages along the way. So just include "Controller" once with this bit of code
#pragma once 

#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "model.h"

class Controller
{
// I like to separate constants from variables in the class definition. This is just
// a matter of choice. You can divvy up where variables, constants, functions, etc.
// go to your liking.
private:
    const int RELAY_1_PIN = D5;
    const int RELAY_2_PIN = D6;
    const int SERVER_PORT = 80;

private:
    // By convention class member variables are prefixed with an "_" character.
    // You may see alternative prefixes elsewhere, such as "m_" or simply "m".
    // Some (but thankfully not many) use NO prefix. This can make the code
    // confusing because you always have to check whether the variable is a
    // member variable of the class or a local variable in a function.
    Model* _model;
    AsyncWebServer* _server;

    // This is a bit subtle, and perhaps up for interpretation, but notice how the
    // following relay-related variables are NOT in the model. The model contains
    // the current state of the relay, but not how long it's waited, nor it's rate.
    // In my opinion these latter variables are part of the "business logic" of the
    // app. The model keeps track of the state, and the controller does what it wants
    // with the state. Maybe we don't want to toggle the relays after a timeout but
    // instead only when a user presses a button or something. The Controller is
    // the one to encapsulate how the app "works". Hence these values are defined here.
    int _relay1RateMS = 250;
    int _relay1TimeWaitedMS = 0;

    int _relay2RateMS = 600;
    int _relay2TimeWaitedMS = 0;

public:
    /*******************************************************************************

    *******************************************************************************/
    Controller()
    {
        // Constructor. Initialize variables here
        _server = nullptr;
        _model = nullptr;
    }

    /*******************************************************************************

    *******************************************************************************/
    ~Controller()
    {
        if (_server != nullptr)
        {
            delete _server;
            _server = nullptr; // good hygiene

            // Note we do NOT delete _model because we didn't create it, Recall
            // it was passed to us in init(). Just "forget" about it by setting
            // our variable to NULL.
            _model = nullptr; 
        }
    }

    /*******************************************************************************

    *******************************************************************************/
    void init(Model* inModel)
    {
        _model = inModel;

        pinMode(RELAY_1_PIN, OUTPUT);
        pinMode(RELAY_2_PIN, OUTPUT);    

        _server = new AsyncWebServer(SERVER_PORT);
        initServer();
    }

    /*******************************************************************************

    *******************************************************************************/
    void initServer()
    {
        if (_server == nullptr) return; // armor
        
        // Route for root / web page
        _server->on("/", HTTP_GET, [](AsyncWebServerRequest *request)
        {
            request->send(SPIFFS, "/index.html");
        });

        _server->on("/toggleRelay1", HTTP_GET, [this](AsyncWebServerRequest *request)
        {
            this->toggleRelay1();
            request->send_P(200, "text/plain", "OK");
        });

        _server->on("/toggleRelay2", HTTP_GET, [this](AsyncWebServerRequest *request)
        {
            this->toggleRelay2();
            request->send_P(200, "text/plain", "OK");
        });

        // Start server
        _server->begin();
    }

    /*******************************************************************************

    *******************************************************************************/
    void toggleRelay1()
    {
        bool currentState = _model->getRelay1State();
        digitalWrite(RELAY_1_PIN, currentState); 
        _model->setRelay1State(!currentState);
    }

    /*******************************************************************************

    *******************************************************************************/
    void toggleRelay2()
    {
        bool currentState = _model->getRelay2State();
        digitalWrite(RELAY_2_PIN, currentState); 
        _model->setRelay2State(!currentState);
    }

    /*******************************************************************************

    *******************************************************************************/
    void loop(int inDeltaMS)
    {
        // inDeltaMS is the number of milliseconds since this function was last called.
        _relay1TimeWaitedMS += inDeltaMS;
        if (_relay1TimeWaitedMS >= _relay1RateMS)
        {
            toggleRelay1();
            _relay1TimeWaitedMS = 0;
        }
    
        _relay2TimeWaitedMS += inDeltaMS;
        if (_relay2TimeWaitedMS >= _relay2RateMS)
        {
            toggleRelay2();
            _relay2TimeWaitedMS = 0;
        }
    }
};

