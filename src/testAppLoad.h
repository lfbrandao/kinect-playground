#ifndef _TEST_APP_LOAD
#define _TEST_APP_LOAD

//#define USE_IR // Uncomment this to use infra red instead of RGB cam...

#include "ofxOpenNI.h"
#include "ofMain.h"
#include "kinectController.h"

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

#endif
