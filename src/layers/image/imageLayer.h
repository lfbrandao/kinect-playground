#pragma once

#include "ofMain.h"
#include <stdio.h>

class imageLayer
{
public:
    virtual void setup(string videoURI, int width, int height, int x, int y, int startAt, int stopAt);
    virtual void setup(string videoURI, int startAt, int stopAt);
    
    virtual void play();
    virtual void pause();
    virtual void stop();
    
    ofImage img;
    bool                frameByframe;
    
    // of methods
    virtual void update();
    virtual void draw();
    
    float getDuration();
private:
    int x;
    int y;
    int width;
    int height;
    int duration;
    float originalWidth, originalHeight;
};

