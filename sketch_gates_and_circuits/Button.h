#ifndef BUTTON_H
#define BUTTON_H

#include "Container.h"

#define DEFAULT_BUTTON_BACKGROUND_COLOR TFT_DARKGREY

class Button : public Container{
  protected:
    void init();
  public:
    using Container::Container;
    Button(const Component* pParent, const double& pX,const double& pY,const double& pR);
    Button(const Component* pParent, const double& pX,const double& pY,const double& pWidth,const double& pHeight);
};

#endif //BUTTON_H