#pragma once

//#define USE_IR // Uncomment this to use infra red instead of RGB cam...

#include "ofxOpenNI.h"
#include "ofMain.h"
#include "kinectController.h"
#include "imageLayer.h"

class testAppLoad : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);

    kinectController kinect;
    ofImage img;
    
    int imgCurrWidth, imgCurrHeight;
    float imgCurrX, imgCurrY;
    float zoomPercentage;
    

};
