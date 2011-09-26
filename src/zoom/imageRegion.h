#pragma once

class imageRegion
{
public:
    imageRegion();

    imageRegion(float x, float y, float width, float height, int zoomPercentage);

    
    float getX();
    float getY();
    float getWidth();
    float getHeight();
    float getZoomPercentage();
    
    void setX(float x);
    void setY(float y);
    void setWidth(float width);
    void setHeight(float height);
    void setZoomPercentage(float zoomP);
    
    friend bool operator== (imageRegion &imr1, imageRegion &imr2);
private:
    float width;
    float height;
    float x,y;
    int zoomPercentage;
};