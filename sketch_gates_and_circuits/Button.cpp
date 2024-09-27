#include "Button.h"

Button::Button(const Component* pParent, const double& pX,const double& pY,const double& pR) :
  Container(pParent,pX,pY,pR)
{
  init();
};

Button::Button(const Component* pParent, const double& pX,const double& pY,const double& pWidth,const double& pHeight) : 
  Container(pParent,pX,pY,pWidth,pHeight)
{
  init();
};

void Button::init(){
  backgroundColor = DEFAULT_BUTTON_BACKGROUND_COLOR;
}