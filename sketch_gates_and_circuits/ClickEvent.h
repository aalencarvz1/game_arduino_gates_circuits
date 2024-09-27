#ifndef CLICKEVENT_H
#define CLICKEVENT_H

#include "VisualComponent.h"
#include "LambdaCallback.h"

class ClickEvent {  
  protected: 
    int id = -1;
    VisualComponent* component = nullptr;
    bool enabled = true;
    void (*staticOnClick)() = nullptr;
    ICallback* onClickCallback = nullptr;  // Ponteiro para o callback
    void initEvent();
  public:
    ClickEvent(
      const VisualComponent* pComponent,
      const void (*pStaticOnClick)() = nullptr
    );  
    ClickEvent(
      const VisualComponent* pComponent,
      const ICallback* pOnClickCallback = nullptr
    );  

    ~ClickEvent();
    bool checkClickEvent(const DPoint& point);
    const int& getId() const {return id;};
};

#endif //CLICKEVENT_H