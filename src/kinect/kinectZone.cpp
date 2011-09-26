#include "kinectZone.h"

kinectZone::kinectZone(float xLow, float xHigh, float zLow, float zHigh)
{
    this->xLow = xLow;
    this->xHigh = xHigh;
    this->zLow = zLow;
    this->zHigh = zHigh;
}

void kinectZone::setImageRegion(imageRegion* imgRegion)
{
    this->imgRegion = imgRegion;
}

imageRegion* kinectZone::getImageRegion()
{
    return this->imgRegion;
}

float kinectZone::getXLow(){return this->xLow;}
float kinectZone::getXHigh(){return this->xHigh;}
float kinectZone::getZLow(){return this->zLow;}
float kinectZone::getZHigh(){return this->zHigh;}