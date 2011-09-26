#include "testAppLoad.h"

//--------------------------------------------------------------
void testAppLoad::setup() 
{
    img.loadImage("/Users/luisbrandao/Desktop/walking for aclx/interfaceDSCF0041changed.png");
    imageLayer image;
    
    kinect.setup();
    zoomPercentage = 100;
    imgCurrX = 0;
    imgCurrY = 0;
    imgCurrWidth = ofGetWidth();
    imgCurrHeight = ofGetHeight();
}

//--------------------------------------------------------------
void testAppLoad::update()
{
    kinect.update();
    
}

//--------------------------------------------------------------
void testAppLoad::draw()
{
    int screenW = ofGetWidth();
    int screenH = ofGetHeight();
    
    if(kinect.tracking)
    {
        int positionX = kinect.position.X;
        int positionZ = kinect.position.Z;
        
        
        
     
        if(positionZ > 2600)
        {
            if(zoomPercentage >= 100)
                zoomPercentage = zoomPercentage - 1;
        }
        else if(positionZ > 0)
        {
            if(zoomPercentage < 170)
                zoomPercentage = zoomPercentage + 1;
        }
        
        int maxOffset = (screenW - imgCurrWidth) / 2;
        if(zoomPercentage > 165)
        {    
            if(positionX < 250)
            {
                if(imgCurrX < 0)
                    imgCurrX = imgCurrX + 10;
            }
            else if(positionX > 450)
            {
                if(imgCurrX > -925)
                    imgCurrX = imgCurrX - 10;
            }
            else if(positionX != 0)
            {   
                cout << imgCurrX << "," << maxOffset << "," << imgCurrX - maxOffset <<  endl;
                if(imgCurrX > maxOffset)
                {
                    imgCurrX = imgCurrX - 10; 
                }
                else if((imgCurrX < maxOffset) & ((imgCurrX - maxOffset) > -1))
                {
                    imgCurrX = imgCurrX + 10; 
                }
            }
        }
        else
        {
            imgCurrX = ((screenW - imgCurrWidth) / 2);
            imgCurrY = ((screenH - imgCurrHeight) / 2);
        }
        
        
        imgCurrWidth = screenW * zoomPercentage / 100;
        imgCurrHeight = screenH * zoomPercentage / 100;
        
        float maxXoffSet = screenW * (zoomPercentage / 2) / 100;
        
        
        
        img.draw(imgCurrX, imgCurrY, imgCurrWidth,imgCurrHeight);
        
        
    }
    else
    {
        /*
        cout << "non tracking (" << screenW << "," << screenH << endl;        
        img.draw(0, 0, ofGetWidth(),ofGetHeight());
        imgCurrWidth = screenW;
        imgCurrHeight = screenH;
        imgCurrX = 0;
        imgCurrY = 0;
         */
        imgCurrWidth = screenW * zoomPercentage / 100;
        imgCurrHeight = screenH * zoomPercentage / 100;
        
        img.draw(imgCurrX, imgCurrY, imgCurrWidth,imgCurrHeight);
    }
    stringstream msg;
    msg
    << "zoom percentage: " << zoomPercentage << endl
    << "curr pos (X,Y): " << imgCurrX << "," << imgCurrY << endl
    << "curr size (W,H): " << imgCurrWidth << "," << imgCurrHeight << endl;
    ofDrawBitmapString(msg.str(), ofGetWidth()-300,30);
    kinect.draw();
}

//--------------------------------------------------------------
void testAppLoad::keyPressed(int key)
{
    switch(key)
    {
    case OF_KEY_UP:
        imgCurrY = imgCurrY + 5;
        break;
    case OF_KEY_DOWN:
        imgCurrY = imgCurrY - 5;
        break;
    case OF_KEY_LEFT:
        imgCurrX = imgCurrX + 5;            
        break;
    case OF_KEY_RIGHT:
        imgCurrX = imgCurrX - 5;
        break;
    case 'w':
        zoomPercentage = zoomPercentage + 5;
            break;    
        case 'e':
            zoomPercentage = zoomPercentage - 5;
            break;    

    default:
            break;
    }        
    //kinect.keyPressed(key);
}
