/*******************************************************************************

    main.ino

    Copyright (c) 2024 Mooshwerks
    All Rights Reserved

*******************************************************************************/

#include <FS.h>
#include "wifi_credentials.h"
#include "stopwatch.h"
#include "model.h"
#include "controller.h"

bool gFilesystemActive = false;
Stopwatch sw;

void initFilesystem();
void initServer();
void initWifiStation();
void toggleRelay1();
void toggleRelay2();

Model _model;
Controller _controller;

/*******************************************************************************

*******************************************************************************/
void setup()
{
    Serial.begin(9600);
    Serial.println(" ");
    Serial.println(" ");

    initFilesystem();
    initWifiStation();

    _model.init();
    _controller.init(&_model);
}

/*******************************************************************************

*******************************************************************************/
void initFilesystem()
{
    if(SPIFFS.begin())
    {
        gFilesystemActive = true;
        Serial.println("\n\n");
        Serial.println("SPIFFS filesystem active.");

        // This is just for debugging or general info.
        FSInfo fs_info;
        SPIFFS.info(fs_info);
        Serial.println("File system info...");
        Serial.println("   totalBytes   : " + String(fs_info.totalBytes));
        Serial.println("   usedBytes    : " + String(fs_info.usedBytes));
        Serial.println("   blockSize    : " + String(fs_info.blockSize));
        Serial.println("   pageSize     : " + String(fs_info.pageSize));
        Serial.println("   maxOpenFiles : " + String(fs_info.maxOpenFiles));
        Serial.println("   maxPathLength: " + String(fs_info.maxPathLength));
    }
    else
    {
        Serial.println("An error has occurred while mounting SPIFFS");
        return;
    }
}
 
/*******************************************************************************

*******************************************************************************/
void initWifiStation()
{
    Serial.print("Connecting to " + String(WIFI_NAME) + "...");

    if (true)
    {
        WiFi.mode(WIFI_STA);
        WiFi.setPhyMode(WIFI_PHY_MODE_11G); // tried both WIFI_PHY_MODE_11G and WIFI_PHY_MODE_11N
        WiFi.begin(WIFI_NAME, WIFI_PASSWORD);

        while (WiFi.status() != WL_CONNECTED) 
        {
            digitalWrite(LED_BUILTIN, HIGH);
            delay(250);
            digitalWrite(LED_BUILTIN, LOW);
            delay(250);
            Serial.print(".");
        }
    }

    Serial.println("");
    Serial.println("CONNECTED!");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}     
 
/*******************************************************************************

*******************************************************************************/
long oldTime = 0;
long CalculateDeltaTime()
{
    long currentTime = millis();
    long deltaTime = currentTime - oldTime;
    oldTime = currentTime;
    return deltaTime;
}

/*******************************************************************************

*******************************************************************************/
void loop()
{
    if (!gFilesystemActive) return; // Bad news...fail silently
    long deltaTimeMS = CalculateDeltaTime(); // milliseconds

    _controller.loop(deltaTimeMS);
}

/*******************************************************************************

*******************************************************************************/
/*******************************************************************************

*******************************************************************************/
/*******************************************************************************

*******************************************************************************/
/*******************************************************************************

*******************************************************************************/
/*******************************************************************************

*******************************************************************************/
