#pragma once

#include <string>
#include <set>
using std::set;
using std::string;

namespace Utils
{
    imageRegion scaleImageToScreen(float originalWidth, float originalHeight, float screenWidth, float screenHeight);
};