#include "VisualComponent.h"
#include "ClickEvent.h"

VisualComponent::VisualComponent(const Component* pParent,const double& pX,const double& pY,const double& pR) :
  Component(pParent),
  x(pX),
  y(pY),
  r(pR)
{ 
  //parent constructor is automatic called before this
  //Serial.println(F("INIT VisualComponent::VisualComponent"));  
  circular = true;
  //Serial.println(F("END VisualComponent::VisualComponent"));
};

VisualComponent::~VisualComponent(){
  //Serial.println(F("INIT VisualComponent::~VisualComponent"));
  removeOnClick();
  //Serial.println(F("END VisualComponent::~VisualComponent"));
  //parent destructor is automatic called after this
};

void VisualComponent::setRoundedRadius(const double& pRoundedRadius){
  roundedRadius = pRoundedRadius;
  if (border != nullptr) {
    border->setRoundedRadius(roundedRadius);
  }
};

void VisualComponent::setBorder(const Border* pBorder){
  if (border != nullptr) {
    delete border;
  }
  border = pBorder;
};

void VisualComponent::removeOnClick() {
  //Serial.println(F("INIT VisualComponent::removeOnClick"));
  if (onClick != nullptr) {
    TouchScreenController::clickEvents->remove(onClick);    
    onClick = nullptr;
  }
  //Serial.println(F("END VisualComponent::removeOnClick"));
}

void VisualComponent::setOnClick(const void (*staticOnClick)()) {
  //Serial.println(F("INIT VisualComponent::setOnClick"));
  removeOnClick();
  onClick = new ClickEvent(this,staticOnClick);
  //Serial.println(F("END VisualComponent::setOnClick"));
}

void VisualComponent::setOnClick(const ICallback* onClickCallback) {
  //Serial.println(F("INIT VisualComponent::setOnClick"));
  removeOnClick();
  onClick = new ClickEvent(this,onClickCallback);
  //Serial.println(F("END VisualComponent::setOnClick"));
}

void VisualComponent::draw(){
  //Serial.println("INIT VisualComponent::draw");
  double borderSpace = 0;
  if (border != nullptr) {
    border->draw();    
    borderSpace = border->getBorderWidth() + border->getPadding();
  }
  if (backgroundColor != -1) {
    if (circular) {
      TouchScreenController::tft.fillCircle(x,y,r-borderSpace*2-margin,backgroundColor);
    } else {
      TouchScreenController::tft.fillRoundRect(x+margin+borderSpace,y+margin+borderSpace,width-margin-borderSpace*2,height-margin-borderSpace*2,roundedRadius,backgroundColor);
    }  
  }
  if (text != nullptr) {
    TouchScreenController::drawCenteredText(text,y+height/2,x+width/2);
  }
  //Serial.println("END VisualComponent::draw");
}

void VisualComponent::createBorder(const double& borderWidth, const int& borderColor) {
  if (border == nullptr) {
    if (circular) {
      border = new Border(this,x,y,r);
    } else {
      border = new Border(this,x,y,width,height);
    }
    border->setMargin(margin); 
  } 
  border->setBorderWidth(borderWidth);
  border->setColor(borderColor == -1 ? TFT_DARKGREY : borderColor);
}


/**
** BORDER
**/
void Border::draw(){
  //Serial.println("INIT Border::draw");
  if (color != -1 && borderWidth > 0) {
    if (circular) {
      for(int i = 0; i < borderWidth; i++) {
        TouchScreenController::tft.drawCircle(x,y,r-margin-i,color);
      }
    } else {
      for(int i = 0; i < borderWidth; i++) {
        TouchScreenController::tft.drawRoundRect(x+margin+i,y+margin+i,width-margin-i,height-margin-i,roundedRadius,backgroundColor);
      }
    }
  }
  //Serial.println("END Border::draw");
}


