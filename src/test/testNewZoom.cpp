#include "testNewZoom.h"

//--------------------------------------------------------------
void testNewZoom::setup() 
{
    img.loadImage("/Users/luisbrandao/Desktop/walking for aclx/interfaceDSCF0041changed.png");
    
    imageRegion* reg0 = new imageRegion(0,0,ofGetWidth(),ofGetHeight(),100);
    imageRegion* reg1 = new imageRegion(0,-400,200,100,400);
    imageRegion* reg2 = new imageRegion(0,0,ofGetWidth(),ofGetHeight(),100);
    imageRegion* reg3 = new imageRegion(-1400,-400,200,100,400);
    imageRegion* reg4 = new imageRegion(-1800,-400,200,100,400);
    imageRegion* reg5 = new imageRegion(-2100,-400,200,100,400);
    
    regionsOfInterest.push_back(*reg0);
    regionsOfInterest.push_back(*reg1);
    regionsOfInterest.push_back(*reg2);
    regionsOfInterest.push_back(*reg3);
    regionsOfInterest.push_back(*reg4);
    regionsOfInterest.push_back(*reg5);
    
    this->currRegionOfInterest = &regionsOfInterest.front();
    this->visibleRegionOfInterest = new imageRegion(0,0,ofGetWidth(),ofGetHeight(),100);
    
    it = regionsOfInterest.begin();
    
    
    
    //kinect.setup();
    
    // init variables
    
    zoomStep = 1.0;
    moveStep = 1.5;
    
    this->defaultZoomStep = 1;
    this->defaultMoveStep = 1;
}

//--------------------------------------------------------------
void testNewZoom::update()
{
    if(currRegionOfInterest != visibleRegionOfInterest)
    {
        float targetX = currRegionOfInterest->getX();
        float targetY = currRegionOfInterest->getY();
        float targetZoom = currRegionOfInterest->getZoomPercentage();
        
        float visibleX = visibleRegionOfInterest->getX();
        float visibleY = visibleRegionOfInterest->getY();
        float visibleZoom = visibleRegionOfInterest->getZoomPercentage();
        
        float diffX = abs(targetX - visibleX);
        float diffY = abs(targetY - visibleY);
        
        float zoomDif = abs(visibleZoom - targetZoom);
        /*
        cout 
            << " targetX " << targetX
            << "; targetY " << targetY
            << "; targetZoom " << targetZoom
            << "; visibleX " << visibleX
            << "; visibleY " << visibleY
            << "; visibleZoom " << visibleZoom
            << "; diffX " << diffX
            << "; zoomDif " << zoomDif
            << "; diffY" << diffY << endl;
        */
        if(diffY > 0 || diffX > 0)
        {
            if(diffX >= diffY)
            {
                cout << "moveStep " << moveStep << endl;
                if(diffX >= moveStep)
                {
                    if(visibleX > targetX) visibleX = visibleX - moveStep;
                    if(visibleX < targetX) visibleX = visibleX + moveStep;
                }
                else
                {
                    if(visibleX > targetX) visibleX = visibleX - diffX;
                    if(visibleX < targetX) visibleX = visibleX + diffX;
                }
                
                if(diffY > 0) visibleY = targetY * visibleX / targetX;
            }
            else
            {
                if(diffY >= moveStep)
                {
                    if(visibleY > targetY) visibleY = visibleY - moveStep;
                    if(visibleY < targetY) visibleY = visibleY + moveStep;
                }
                else
                {
                    if(visibleY > targetY) visibleY = visibleY - diffY;
                    if(visibleY < targetY) visibleY = visibleY + diffY;
                }

                if(diffX > 0) visibleX = targetX * visibleY / targetY;
            }
        }
        
        if(isnan(visibleX)) visibleX = 0;
        if(isnan(visibleY)) visibleY = 0;
        
        visibleRegionOfInterest->setY(visibleY);
        visibleRegionOfInterest->setX(visibleX);

        // zoom
        if(visibleZoom != targetZoom)
        {
            if(visibleZoom < targetZoom)
            {
                visibleRegionOfInterest->setZoomPercentage(visibleZoom + zoomStep);
            }
            else
            {
                visibleRegionOfInterest->setZoomPercentage(visibleZoom - zoomStep);
            }
            
            visibleRegionOfInterest->setWidth(ofGetWidth() * visibleZoom / 100);
            visibleRegionOfInterest->setHeight(ofGetHeight() * visibleZoom / 100);
        }
    }
    
    //kinect.update();
    
}

//--------------------------------------------------------------
void testNewZoom::draw()
{
    img.draw(visibleRegionOfInterest->getX(), 
             visibleRegionOfInterest->getY(), 
             visibleRegionOfInterest->getWidth(), 
             visibleRegionOfInterest->getHeight());
    
    stringstream msg;
    msg
        << "zoom percentage: " << visibleRegionOfInterest->getZoomPercentage() << endl
        << "curr pos (X,Y): " << visibleRegionOfInterest->getX() << "," << visibleRegionOfInterest->getY() << endl
        << "width: " << visibleRegionOfInterest->getWidth() << endl
        << "height " << visibleRegionOfInterest->getHeight() << endl
        << "zoomStep " << zoomStep << endl;
    
    ofDrawBitmapString(msg.str(), ofGetWidth()-300,30);
    /*
    cout
    << "drawing: "
    << " x: " << visibleRegionOfInterest->getX()
    << " y: " << visibleRegionOfInterest->getY()
    << " width,height: " << visibleRegionOfInterest->getWidth() << "," 
    << visibleRegionOfInterest->getHeight() << endl;
     */
    //kinect.draw();
}

void testNewZoom::changeRegionOfInterest(imageRegion* newImageRegion)
{
    this->currRegionOfInterest = &(*newImageRegion);
    
    float targetX = currRegionOfInterest->getX();
    float targetY = currRegionOfInterest->getY();
    float targetZoom = currRegionOfInterest->getZoomPercentage();
    
    float visibleX = visibleRegionOfInterest->getX();
    float visibleY = visibleRegionOfInterest->getY();
    float visibleZoom = visibleRegionOfInterest->getZoomPercentage();
    
    float diffX = abs(targetX - visibleX);
    float diffY = abs(targetY - visibleY);
    
    float zoomDif = abs(visibleZoom - targetZoom);

    /*
    cout 
    << " targetX " << targetX
    << "; targetY " << targetY
    << "; targetZoom " << targetZoom
    << "; visibleX " << visibleX
    << "; visibleY " << visibleY
    << "; visibleZoom " << visibleZoom
    << "; diffX " << diffX
    << "; zoomDif " << zoomDif
    << "; diffY" << diffY << endl;
    */
    
    // reset zoom and move steps
    moveStep = defaultMoveStep;
    zoomStep = defaultMoveStep;
    
    // if there's no position change: zoom only
    if((diffX == 0) && (diffY == 0))
    {
        moveStep = 0;
        zoomStep = defaultZoomStep;
        return;
    }
    
    // if there's no zoom change: move only
    if(zoomDif == 0)
    {
        zoomStep = 0;
        moveStep = defaultMoveStep;
        return;
    }
   
    // both zoom and position need to be uptdated
    // get the longest distance (vertical vs horizontal)
    float longestDistance;
    
    if(diffX >= diffY)  longestDistance = diffX;
    else                longestDistance = diffY;
    
    // make moveStep proportional to zoomStep
    if(zoomDif > longestDistance)
    {
        moveStep = zoomDif / longestDistance;
    }
    else
    {
        moveStep = longestDistance / zoomDif;
    }
}

//--------------------------------------------------------------
void testNewZoom::keyPressed(int key)
{
    switch(key)
    {
        case OF_KEY_UP:
            visibleRegionOfInterest->setY(visibleRegionOfInterest->getY() + 5);
            break;
        case OF_KEY_DOWN:
            visibleRegionOfInterest->setY(visibleRegionOfInterest->getY() - 5);
            break;
        case OF_KEY_LEFT:
            visibleRegionOfInterest->setX(visibleRegionOfInterest->getX() + 5);
            break;
        case OF_KEY_RIGHT:
            visibleRegionOfInterest->setX(visibleRegionOfInterest->getX() - 5);
            break;
        case 'w':
            visibleRegionOfInterest->setZoomPercentage(visibleRegionOfInterest->getZoomPercentage() + 5);
            break;    
        case 'e':
            visibleRegionOfInterest->setZoomPercentage(visibleRegionOfInterest->getZoomPercentage() - 5);
            break;    
        case 'n':
            it--;
            changeRegionOfInterest(&*it);
            //this->currRegionOfInterest = &(*it);
            break;
        case 'm':
            it++;
            changeRegionOfInterest(&*it);
            //this->currRegionOfInterest = &(*it);
            break;
        default:
            break;
    }        
    //kinect.keyPressed(key);
}
