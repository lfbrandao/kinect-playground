#pragma once
#include <iostream>

class layer 
{
    public:
        virtual void setup(string videoURI, int startAt, int stopAt) = 0;
        virtual void setup(string videoURI, int width, int height, int x, int y, int startAt, int stopAt) = 0;
        
        // playback control
        virtual void play() = 0;
        virtual void pause() = 0;
        virtual void stop() = 0;
    
        // of methods
        virtual void update() = 0;
        virtual void draw() = 0;
    
        virtual ~layer(){}
        
        // setters & getters
        int getId(){return id;}
        float getX(){return x;}
        float getY(){return y;}
        float getHeight(){return height;}
        float getWidth(){return width;}
        float getVolume(){return volume;}
        float getInTime(){return inTime;}
        float getOutTime(){return outTime;}
        float getOpacity(){return opacity;}
        float getAspectRatio(){return aspectRatio;}
        
        void  setId(int id){this->id = id;}
        void  setX(float x){this->x = x;}
        void  setY(float y){this->y = y;}
        void  setHeight(float height){this->height = height;}
        void  setWidth(float width){this->width = width;}
        void  setVolume(float volume){this->volume = volume;}    
        void  setInTime(float inTime){this->inTime = inTime;}    
        void  setOutTime(float outTime){this->outTime = outTime;}    
        void  setOpacity(float opacity){this->opacity = opacity;}    
        void  setAspectRatio(float aspectRatio){this->aspectRatio = aspectRatio;}
        
        void  resize(int percentage) 
        {
            float newWidth = originalWidth * percentage / 100;
            float newHeight = originalHeight * percentage / 100;
            float xPosOffset = (width - newWidth) / 2;
            float yPosOffset = (height - newHeight) / 2;
            
            if(newWidth >= originalWidth)
            {
                this->width = originalWidth * percentage / 100;
                this->height = originalHeight * percentage / 100;
                this->x = x + xPosOffset;
                this->y = y + yPosOffset;
            }
        }
    protected:
        int id;
        float originalWidth;
        float originalHeight;
        float x;
        float y;
        float height;
        float width;
        float volume;
        float inTime;
        float outTime;
        float opacity;
        float aspectRatio;
};