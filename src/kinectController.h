#ifndef _TEST_APP
#define _TEST_APP

//#define USE_IR // Uncomment this to use infra red instead of RGB cam...

#include "ofxOpenNI.h"
#include "ofMain.h"

class kinectController{

public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);

	void	setupRecording(string _filename = "");
	void	setupPlayback(string _filename);
	string	generateFileName();

    
    
	bool				isTracking, isRecording, isCloud, isCPBkgnd, isMasking;
	bool				isFiltering;

	ofxOpenNIContext	recordContext;
	ofxDepthGenerator	recordDepth;

#ifdef USE_IR
	ofxIRGenerator		recordImage;
#else
	ofxImageGenerator	recordImage;
#endif

	ofxUserGenerator	recordUser;

#if defined (TARGET_OSX) //|| defined(TARGET_LINUX) // only working on Mac/Linux at the moment (but on Linux you need to run as sudo...)
	ofxHardwareDriver	hardware;
#endif

	void				drawMasks();
	
	int					nearThreshold, farThreshold;
	int					pointCloudRotationY;

	ofImage				user1Mask;

	float				filterFactor;

    XnPoint3D position;
    bool tracking;
};

#endif
