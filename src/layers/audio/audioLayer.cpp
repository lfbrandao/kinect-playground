#include "audioLayer.h"

//--------------------------------------------------------------
void audioLayer::setup(string videoURI, int width, int height, int x, int y, int startAt, int stopAt)
{    
	ofBackground(255,255,255);
	
	this->soundPlayer.loadSound(videoURI);
    this->width = width;
    this->height = height;
    
    this->x = x;
    this->y = y;
    
    printf("Width %i \n", width);
    printf("Height %i \n", height);
    printf("X %i \n", x);
    printf("Y %i \n", y);
}

void audioLayer::setup(string videoURI, int startAt, int stopAt)
{
    ofBackground(255,255,255);
    this->soundPlayer.loadSound(videoURI);
}

void audioLayer::play()
{
    soundPlayer.setVolume(1.0);
    this->soundPlayer.play();    
}

void audioLayer::pause()
{
    this->soundPlayer.setPaused(true);
}

void audioLayer::stop()
{
    this->soundPlayer.stop();
}


void audioLayer::update()
{
    ofSoundUpdate();
}

//--------------------------------------------------------------
void audioLayer::draw()
{
}

float audioLayer::getDuration()
{
    return 0.0;
}
