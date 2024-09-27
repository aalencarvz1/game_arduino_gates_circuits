#include "ScreenInitialMenu.h"
#include "TouchScreenController.h"
#include "Screens.h"
#include "ScreenTutorial.h"
/*#include "ScreenPoints.h"
#include "ScreenTime.h"
#include "ScreenMake.h"*/
#include "Colors.h"
#include "Button.h"

const byte ScreenInitialMenu::SCREEN_ID = 0;


void ScreenInitialMenu::drawOption(const double& pX,const double& pY, const double& pR, const int& pColor, const char* pText, const void (*pStaticOnClick)()){
  Button* b = new Button(this,pX, pY, pR);
  b->setBackgroundColor(pColor);
  b->createBorder(2,pColor);
  b->getBorder()->setPadding(2);
  if (pStaticOnClick != nullptr) {
    b->setOnClick(pStaticOnClick);
  }
  b->draw();
  TouchScreenController::drawRoundedPlay(pX, pY, pR*0.4,pR*0.05,pColor,TFT_BLACK);
  if (pText != nullptr) {
    TouchScreenController::drawCenteredText(pText,pY+pR+20,pX);
  }
}

void ScreenInitialMenu::draw(const char* params[]) {
  BaseScreen::draw(params);
  TouchScreenController::drawCenteredText("Modos de jogo",titleInfo.h+20);
  double _4Div = TouchScreenController::tft.width() / 4.0;
  double itemMenuXPos = _4Div / 2.0;
  double itemMenuYPos = TouchScreenController::tft.height() / 2.0;
  double itemR = itemMenuXPos * 0.6;  
  drawOption(itemMenuXPos, itemMenuYPos, itemR, TFT_YELLOW,"Tutorial",[](){    
    Screens::goTo(ScreenTutorial::SCREEN_ID);
  });
  drawOption(itemMenuXPos + _4Div , itemMenuYPos, itemR, Colors::BLUE,"Pontuacao",[](){    
    //Screens::goTo(ScreenPoints::SCREEN_ID);
  });
  drawOption(itemMenuXPos + _4Div * 2, itemMenuYPos, itemR, Colors::GREEN,"Tempo",[](){    
    //Screens::goTo(ScreenTime::SCREEN_ID);
  });
  drawOption(itemMenuXPos + _4Div * 3, itemMenuYPos, itemR, TFT_RED,"Construa",[](){    
    //Screens::goTo(ScreenMake::SCREEN_ID);
  });
};