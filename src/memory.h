/*******************************************************************************

    memory.h

    Copyright (c) 2023 Mooshwerks
    All Rights Reserved
    
*******************************************************************************/

#pragma once

#include <Arduino.h>

class Memory
{
public:
    static uint32_t getFree()
    {
        uint32_t MAX_BYTES = 51720;
        uint32_t MIN_BYTES = 1;
        uint32_t hiBytes = MAX_BYTES;
        uint32_t loBytes = MIN_BYTES;
        uint32_t curBytes = hiBytes;
        void *testbuf = nullptr;
        bool done = false;
        while (!done)
        {
            testbuf = malloc(curBytes);
            if (testbuf == nullptr)
            {
                hiBytes = curBytes;
            }
            else
            {
                loBytes = curBytes;
                free(testbuf);
            }

            curBytes = (loBytes + hiBytes) / 2;
            done = (curBytes == loBytes) || (curBytes == hiBytes);
        }

        return curBytes;
    }


};

