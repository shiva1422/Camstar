//
// Created by pspr1 on 7/7/2021.
//

#include "Commons.h"

void DisplayMetrics::print()
{
    Logi("\nDisplayParams:","screenWidth %d\nscreenHeight %d\ndensityDpi %d\ndeviceStableDensity %d\ndensity %f\nscaled density %f\nxdpi %f\nydpi %f",screenWidth,screenHeight,densityDpi,deviceStableDensity,density,scaledDensity,xdpi,ydpi);
}
void DisplayMetrics::onScreenRotation()
{
    float temp = screenWidth;
    screenWidth = screenHeight;
    screenHeight = temp;
}