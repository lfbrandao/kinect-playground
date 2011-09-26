#pragma once

#include "ofMain.h"
#include <stdio.h>
#include "layer.h"

class audioLayer : public layer
{
public:
    void setup(string videoURI, int width, int height, int x, int y, int startAt, int stopAt);
    virtual void setup(string videoURI, int startAt, int stopAt);
    
    virtual void play();
    virtual void pause();
    virtual void stop();
    
    ofSoundPlayer 		soundPlayer;
    
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
};

