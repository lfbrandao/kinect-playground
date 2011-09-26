#pragma once

#include "imageRegion.h"

class kinectZone
{
public:
    kinectZone(float xLow, float xHigh, float zLow, float zHigh);
    void setImageRegion(imageRegion* imgRegion);
    imageRegion* getImageRegion();
    
    float getXLow();
    float getXHigh();
    float getZLow();
    float getZHigh();
private:
    float xLow, xHigh;
    float yStart, yEnd;
    float zLow, zHigh;
    imageRegion* imgRegion;
};