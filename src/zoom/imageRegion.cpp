#include "imageRegion.h"

imageRegion::imageRegion(){}
imageRegion::imageRegion(float x, float y, float width, float height, int zoomPercentage)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->zoomPercentage = zoomPercentage;
}

bool operator== (imageRegion &imr1, imageRegion &imr2)
{
    return (imr1.x == imr2.x &&
            imr1.y == imr2.y &&
            imr1.zoomPercentage == imr2.zoomPercentage &&
            imr1.width == imr2.width &&
            imr1.height == imr2.height
            );
}

float imageRegion::getX() {return x;}
float imageRegion::getY() {return y;}
float imageRegion::getWidth() {return width;}
float imageRegion::getHeight() {return height;}
float imageRegion::getZoomPercentage() {return zoomPercentage;}

void imageRegion::setX(float x) {this->x = x;}
void imageRegion::setY(float y) {this->y = y;}
void imageRegion::setWidth(float width) {this->width = width;}
void imageRegion::setHeight(float height) {this->height = height;}
void imageRegion::setZoomPercentage(float zoomP) {this->zoomPercentage = zoomP;}