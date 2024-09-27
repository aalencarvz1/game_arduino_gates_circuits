#include "BaseScreen.h"


#include "TouchScreenController.h"
#include "Screens.h"

BaseScreen::~BaseScreen(){
  //Serial.println("INIT BaseScreen::~BaseScreen");
  //Serial.println("END BaseScreen::~BaseScreen");
}

void BaseScreen::draw(const char* params[]) {
  //Serial.println("INIT BaseScreen::draw");
  TouchScreenController::tft.fillScreen(DEFAULT_BACKGROUND_COLOR);   
  if (title != nullptr) {
    titleInfo = TouchScreenController::drawCenteredText(title,DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN,TouchScreenController::tft.width()/2,DEFAULT_WINDOW_TITLE_TEXT_SIZE,DEFAULT_TEXT_COLOR);
  }
  if (hasBack) {
    if (backButton == nullptr) {
      backButton = new Button(this,DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN,DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN,30,20);         
      backButton->setOnClick([](){
        Screens::goBack();    
      });
      backButton->setText("<");
    }    
    backButton->draw();
  }
  if (contentContainer == nullptr) {
    contentContainer = new Container(
      this,
      DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN,
      titleInfo.h+DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN+5,
      TouchScreenController::tft.width() - DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN * 2,
      TouchScreenController::tft.height() - (titleInfo.h+DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN*2)
    );
    //Serial.println("xxxxxxxxxxxxxxxx antes");
    contentContainer->createBorder();
  }
  contentContainer->draw();  
  //Serial.println("END BaseScreen::draw");
};


