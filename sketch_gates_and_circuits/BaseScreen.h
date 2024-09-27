#ifndef BASESCREEN_H
#define BASESCREEN_H

#include "TouchScreenController.h"
#include "VisualComponent.h"
#include "Container.h"
#include "Button.h"

#define DEFAULT_BACKGROUND_COLOR TFT_BLACK
#define DEFAULT_WINDOW_CONTENT_CONTAINER_BORDER_WIDTH 1
#define DEFAULT_WINDOW_CONTENT_CONTAINER_BORDER_COLOR TFT_WHITE
#define DEFAULT_WINDOW_CONTENT_CONTAINER_MARGIN 5
#define DEFAULT_WINDOW_TITLE_TEXT_SIZE 2
#define DEFAULT_TEXT_COLOR TFT_WHITE

class BaseScreen : public VisualComponent{
  protected:
    const char* title;
    TextInfo titleInfo;
    bool hasBack = true;
    Button* backButton = nullptr;
    Container* contentContainer = nullptr;  
    
  public: 
    using VisualComponent::VisualComponent;
    BaseScreen(const char* pTitle = nullptr, const bool& pHasBack = true) : title(pTitle), hasBack(pHasBack) {};
    virtual ~BaseScreen();
    virtual void draw(const char* params[] = nullptr);
};

#endif //BASESCREEN_H