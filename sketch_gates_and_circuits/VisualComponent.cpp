#include "VisualComponent.h"

VisualComponent::VisualComponent(const double& pX,const double& pY,const double& pR) :
  x(pX),
  y(pY),
  r(pR)
{ 
  //parent constructor is automatic called before this
  Serial.println(F("INIT VisualComponent::VisualComponent"));  
  isCircular = true;
  Serial.println(F("END VisualComponent::VisualComponent"));
};

VisualComponent::~VisualComponent(){
  Serial.println(F("INIT VisualComponent::~VisualComponent"));
  if (onClick != nullptr) {
    delete onClick;
    onClick = nullptr;
  }
  Serial.println(F("END VisualComponent::~VisualComponent"));
  //parent destructor is automatic called after this
};

void VisualComponent::removeOnClick() {
  Serial.println(F("INIT VisualComponent::removeOnClick"));
  if (onClick != nullptr) {
    delete onClick;
    onClick = nullptr;
  }
}

void VisualComponent::setOnClick(const void (*&staticOnClick)()) {
  Serial.println(F("INIT VisualComponent::setOnClick"));
  removeOnClick();
  onClick = new TouchScreenClickEvent(this,staticOnClick);
  Serial.println(F("END VisualComponent::setOnClick"));
}

/*void VisualComponent::setOnClick(const ICallback*& onClickCallback) {
  Serial.println(F("INIT VisualComponent::setOnClick"));
  removeOnClick();
  onClick = new TouchScreenClickEvent(x,y,r,null,onClickCallback);
  Serial.println(F("END VisualComponent::setOnClick"));
}*/

void VisualComponent::draw(){
  //do implement
}


