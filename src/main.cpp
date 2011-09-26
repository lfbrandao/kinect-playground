
#include "kinectController.h"
#include "testAppLoad.h"
#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "testNewZoom.h"

//========================================================================
int main( ){

    ofAppGlutWindow window;
    //
	ofSetupOpenGL(&window, 1280,800, OF_FULLSCREEN);			// <-------- setup the GL context
    //ofSetFrameRate(4);
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	//ofRunApp( new testAppLoad());
    ofRunApp( new testNewZoom());
}
