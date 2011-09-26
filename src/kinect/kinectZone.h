#pragma once

#include "imageRegion.h"

class kinectZone
{
public:
    kinectZone(float xStart, float zStart);
    
private:
    float xStart, xEnd;
    float yStart, yEnd;
    float zStart, zEnd;
    imageRegion* imgRegion;
};