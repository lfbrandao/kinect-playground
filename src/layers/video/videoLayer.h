#pragma once

#include "ofMain.h"
#include <stdio.h>
#include "layer.h"

class videoLayer : public layer
{
public:
    virtual void setup(string videoURI, int width, int height, int x, int y, int startAt, int stopAt);
    virtual void setup(string videoURI, int startAt, int stopAt);
    
    virtual void play();
    virtual void pause();
    virtual void stop();
    
    ofVideoPlayer 		videoPlayer;
    bool                frameByframe;
    
    // of methods
    virtual void update();
    virtual void draw();
    
    float getDuration();
};

