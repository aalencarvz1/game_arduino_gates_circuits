#include "Container.h"

void Container::draw(){
  if (isCircular) {

  } else {
    if (backgroundColor != -1) {
      TouchScreenController::tft.fillRoundRect(x,y,width,height,roundedRadius,backgroundColor);
    }
    TouchScreenController::tft.drawRoundRect(x,y,width,height,roundedRadius,lineColor);    
    if (text != nullptr) {
      TouchScreenController::drawCenteredText(text,y,x);
    }
  }
}

