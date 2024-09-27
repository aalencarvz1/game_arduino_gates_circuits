#ifndef SCREENINITIALMENU_H
#define SCREENINITIALMENU_H

#include <Arduino.h>
#include "BaseScreen.h"

class ScreenInitialMenu : public BaseScreen{
  public: 
    using BaseScreen::BaseScreen;
    static const byte SCREEN_ID; 
    void drawOption(const double& pX,const double& pY, const double& pR, const int& pColor, const char* pText = nullptr, const void (*pStaticOnClick)() = nullptr);   
    void draw(const char* params[] = nullptr) override;
};

#endif // SCREENINITIALMENU_H