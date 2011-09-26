#include "kinectController.h"

//--------------------------------------------------------------
void kinectController::setup() {

	isTracking		= false;
	isFiltering		= false;
	isRecording		= false;
	isCloud			= false;
	isCPBkgnd		= true;
	isMasking		= true;

	nearThreshold = 500;
	farThreshold  = 1000;

	filterFactor = 0.1f;

	setupRecording();

	ofBackground(0, 0, 0);
    
    myFont.loadFont("frabk.ttf", 32);
}

void kinectController::setupRecording(string _filename) {

#if defined (TARGET_OSX) //|| defined(TARGET_LINUX) // only working on Mac/Linux at the moment (but on Linux you need to run as sudo...)
	hardware.setup();				// libusb direct control of motor, LED and accelerometers
	hardware.setLedOption(LED_OFF); // turn off the led just for yacks (or for live installation/performances ;-)
#endif

	recordContext.setup();	// all nodes created by code -> NOT using the xml config file at all
	recordDepth.setup(&recordContext);
	recordImage.setup(&recordContext);

    
	recordUser.setup(&recordContext);
	recordUser.setSmoothing(filterFactor);				// built in openni skeleton smoothing...
	recordUser.setUseMaskPixels(isMasking);
	recordUser.setMaxNumberOfUsers(1);
    
	recordContext.toggleRegisterViewport();
	recordContext.toggleMirror();
}

void kinectController::setupPlayback(string _filename) {

}

//--------------------------------------------------------------
void kinectController::update(){

#ifdef TARGET_OSX // only working on Mac at the moment
	hardware.update();
#endif
		// update all nodes
		recordContext.update();
		recordDepth.update();
		recordImage.update();

		// update tracking/recording nodes
		if (isTracking) recordUser.update();

		// demo getting pixels from user gen
    if (isTracking && isMasking) 
    {
        user1Mask.setFromPixels(recordUser.getUserPixels(1), recordUser.getWidth(), recordUser.getHeight(), OF_IMAGE_GRAYSCALE);
    }
}

//--------------------------------------------------------------
void kinectController::draw(){
    glPushMatrix();
	
    //recordDepth.draw(0,0,640,480);
    //recordImage.draw(640, 0, 640, 480);

		if (isTracking) 
        {
			//recordUser.draw();
			if (isMasking) drawMasks();
		}
	glPopMatrix();

	//ofSetColor(255, 255, 0);

	string statusRec		= (string)(!isRecording ? "READY" : "RECORDING");
	string statusFilter		= (string)(isFiltering ? "FILTERING" : "NOT FILTERING");
	string statusFilterLvl	= ofToString(filterFactor);
	string statusMask		= (string)(!isMasking ? "HIDE" : (isTracking ? "SHOW" : "YOU NEED TO TURN ON TRACKING!!"));
	string statusCloud		= (string)(isCloud ? "ON" : "OFF");
	string statusCloudData	= (string)(isCPBkgnd ? "SHOW BACKGROUND" : (isTracking ? "SHOW USER" : "YOU NEED TO TURN ON TRACKING!!"));

	string statusHardware;

	stringstream msg;
    
    int i = recordUser.getNumberOfTrackedUsers();
    if(i > 0)
    {
        ofxTrackedUser * tracked = recordUser.getTrackedUser(i);
        
        if(tracked != NULL) 
        {  
            if(tracked->neck.found)
            {  
                msg << "tracking neck " << (int)tracked->neck.position[1].X 
                << "," << (int)tracked->neck.position[1].Y 
                << "," << (int)tracked->neck.position[1].Z
                << endl;
                /*msg << "tracking neck " << (int)tracked->neck.position[0].X 
                << "," << (int)tracked->neck.position[0].Y 
                << "," << (int)tracked->neck.position[0].Z
                << endl;
                 
                tracked->neck.position[1].X;
                */
                
                position = tracked->neck.position[1];
                tracking = true;
            }
        }
        else
            tracking = false;
    }
    else
    {
        msg << "not tracking" << endl; 
        tracking = false;
    }

    ofSetColor(255, 255, 255);
	myFont.drawString(msg.str(), 30, 50);
}

void kinectController:: drawMasks() 
{
	glPushMatrix();
	user1Mask.draw(ofGetWidth()-250,ofGetHeight()-170, 240, 160);
	glPopMatrix();
}

//--------------------------------------------------------------
void kinectController::keyPressed(int key){

	float smooth;

	switch (key) {            
#ifdef TARGET_OSX // only working on Mac at the moment
		case 357: // up key
			hardware.setTiltAngle(hardware.tilt_angle++);
			break;
		case 359: // down key
			hardware.setTiltAngle(hardware.tilt_angle--);
			break;
#endif
                    
		case 't':
		case 'T':
			isTracking = !isTracking;
			break;
		case 'f':
		case 'F':
			isFiltering = !isFiltering;
			break;
		case 'm':
		case 'M':
			isMasking = !isMasking;
			recordUser.setUseMaskPixels(isMasking);
			break;
		case 'c':
		case 'C':
			isCloud = !isCloud;
			recordUser.setUseCloudPoints(isCloud);
			break;
		case 'b':
		case 'B':
			isCPBkgnd = !isCPBkgnd;
			break;
		case '9':
		case '(':
			smooth = recordUser.getSmoothing();
			if (smooth - 0.1f > 0.0f) {
				recordUser.setSmoothing(smooth - 0.1f);
			}
			break;
		case '0':
		case ')':
			smooth = recordUser.getSmoothing();
			if (smooth + 0.1f <= 1.0f) {
				recordUser.setSmoothing(smooth + 0.1f);
			}
			break;
		case '[':
		//case '{':
			if (filterFactor - 0.1f > 0.0f) {
				filterFactor = filterFactor - 0.1f;
			}
			break;
		case ']':
		//case '}':
			if (filterFactor + 0.1f <= 1.0f) {
				filterFactor = filterFactor + 0.1f;
			}
			break;
		case '>':
		case '.':
			farThreshold += 50;
			if (farThreshold > recordDepth.getMaxDepth()) farThreshold = recordDepth.getMaxDepth();
			break;
		case '<':
		case ',':
			farThreshold -= 50;
			if (farThreshold < 0) farThreshold = 0;
			break;

		case '+':
		case '=':
			nearThreshold += 50;
			if (nearThreshold > recordDepth.getMaxDepth()) nearThreshold = recordDepth.getMaxDepth();
			break;

		case '-':
		case '_':
			nearThreshold -= 50;
			if (nearThreshold < 0) nearThreshold = 0;
			break;
		case 'r':
			recordContext.toggleRegisterViewport();
			break;
		default:
			break;
	}
}

string kinectController::generateFileName() {

	string _root = "kinectRecord";

	string _timestamp = ofToString(ofGetDay()) +
	ofToString(ofGetMonth()) +
	ofToString(ofGetYear()) +
	ofToString(ofGetHours()) +
	ofToString(ofGetMinutes()) +
	ofToString(ofGetSeconds());

	string _filename = (_root + _timestamp + ".oni");

	return _filename;

}