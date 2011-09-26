#include "videoLayer.h"

//--------------------------------------------------------------
void videoLayer::setup(string videoURI, int width, int height, int x, int y, int startAt, int stopAt)
{    
	ofBackground(255,255,255);
	frameByframe = false;
    
	this->videoPlayer.loadMovie(videoURI);
    this->originalWidth = width; 
    this->originalHeight = height; 
    this->width = width;
    this->height = height;
    this->x = x;
    this->y = y;
    
    printf("Width %i \n", width);
    printf("Height %i \n", height);
    printf("X %i \n", x);
    printf("Y %i \n", y);
}

void videoLayer::setup(string videoURI, int startAt, int stopAt)
{
    ofBackground(255,255,255);
    this->videoPlayer.loadMovie(videoURI);
}

void videoLayer::play()
{
    videoPlayer.setVolume(50);
    this->videoPlayer.play();    
}

void videoLayer::pause()
{
    this->videoPlayer.setPaused(true);
}

void videoLayer::stop()
{
    this->videoPlayer.stop();
}


void videoLayer::update()
{
    this->videoPlayer.idleMovie();
}

//--------------------------------------------------------------
void videoLayer::draw()
{
    ofSetHexColor(0xFFFFFF);
    cout << "Drawing video layer " << endl;
    printf("Width %i \n", width);
    printf("Height %i \n", height);
    printf("X %i \n", x);
    printf("Y %i \n", y);
    videoPlayer.draw(this->x,this->y, this->width, this->height);
    //videoPlayer.draw(0, 0, 500, 500);
}

float videoLayer::getDuration()
{
    return videoPlayer.getDuration() * 1000;
}
