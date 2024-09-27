#include "ClickEvent.h"

/**
* ClickEvent
*/
ClickEvent::ClickEvent(
  const VisualComponent* pComponent,
  const void (*pStaticOnClick)()
) :
  component(pComponent),
  staticOnClick(pStaticOnClick)
{
  //Serial.println(F("INIT ClickEvent::ClickEvent"));
  initEvent();
  //Serial.println(F("END ClickEvent::ClickEvent"));
};

ClickEvent::ClickEvent(
  const VisualComponent* pComponent,
  const ICallback* pOnClickCallback
) :
  component(pComponent),
  onClickCallback(pOnClickCallback)
{
  //Serial.println(F("INIT ClickEvent::ClickEvent"));
  initEvent();
  //Serial.println(F("END ClickEvent::ClickEvent"));
};

void ClickEvent::initEvent() {
  //Serial.println(F("INIT ClickEvent::initEvent"));
  id = TouchScreenController::getNextEventId();
  TouchScreenController::clickEvents->add(this);
  //Serial.println(F("END ClickEvent::initEvent"));
}

/*
* not call this directly, this is called on TouchScreenController::clickEvents->remove() because this is element of double lined list
*/
ClickEvent::~ClickEvent(){
  //Serial.println(F("INIT ClickEvent::~ClickEvent"));
  if (onClickCallback != nullptr) {
    delete onClickCallback;
  }
  //Serial.println(F("END ClickEvent::~ClickEvent"));
}

//verifica se o elemento foi clicado com base no ponto central e raio definido
bool ClickEvent::checkClickEvent(const DPoint& point) {
  //Serial.print(F("INIT ClickEvent::checkClickEvent "));
  //Serial.println(String(id));
  bool result = false;
  if (enabled) {  
    //Serial.println("enabled");
    if (component != nullptr) {
      //Serial.println("has component");
      if (component->isCircular()) {
        if (abs(component->getX() - point.x) <= component->getR() && abs(component->getY() - point.y) <= component->getR()) {
          result = true;
        }
      } else {
        if (point.x >= component->getX() && point.x <= component->getX() + component->getWidth()
          && point.y >= component->getY() && point.y <= component->getY() + component->getHeight()
        ) {
          result = true;
        }
      }
      if (result) {
        //Serial.println("clicked on conponent");
        if (onClickCallback != nullptr) {
          //Serial.println("calling lambda callback");
          onClickCallback->call();  // Chama a função encapsulada
        } else if (staticOnClick != nullptr) {
          //Serial.println("calling static callback");
          staticOnClick();
        }
      }
    }
  }
  //Serial.println(F("END ClickEvent::checkClickEvent"));
  return result;
};
