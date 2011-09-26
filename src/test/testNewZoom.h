#pragma once

//#define USE_IR // Uncomment this to use infra red instead of RGB cam...

#include "ofxOpenNI.h"
#include "ofMain.h"
#include "kinectController.h"
#include "imageLayer.h"
#include "imageRegion.h"
#include <list.h>
#include "utils.h"
#include <math.h>
#include "kinectZone.h"

class testNewZoom : public ofBaseApp{
    
public:
	void setup();
	void update();
	void draw();
    
	void keyPressed  (int key);
    
    //kinectController kinect;
    ofImage img;
    
    
    list<imageRegion> regionsOfInterest;
    list<imageRegion>::iterator it;
    
    imageRegion* currRegionOfInterest;
    imageRegion* visibleRegionOfInterest;
    

    float zoomStep;
    float moveStep;
    
    float defaultZoomStep;
    float defaultMoveStep;
    
private:
    void changeRegionOfInterest(imageRegion* newImageRegion);
};